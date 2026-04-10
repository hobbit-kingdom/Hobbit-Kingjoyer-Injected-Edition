#define _CRT_SECURE_NO_WARNINGS

#include "PathNavigator.h"
#include "byte_functions.h"
#include "gui.h"

#include <algorithm>
#include <array>
#include <chrono>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <limits>
#include <queue>
#include <regex>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

namespace
{
	using Clock = std::chrono::steady_clock;

	constexpr float kPi = 3.14159265358979323846f;
	constexpr float kTwoPi = kPi * 2.0f;

	constexpr DWORD kPlayerPointerAddress = 0x0075BA3C;
	constexpr DWORD kPlayerPosXOffset = 0x7C4;
	constexpr DWORD kPlayerPosYOffset = 0x7C8;
	constexpr DWORD kPlayerPosZOffset = 0x7CC;
	constexpr DWORD kPlayerRotYOffset = 0x7AC;
	constexpr char kRuntimeGraphFileName[] = "nav_runtime_graph.txt";
	constexpr char kLegacyPathFileName[] = "nav_path_result.json";

	constexpr float kDefaultGridCellSize = 50.0f;
	constexpr float kGraphSnapVerticalWeight = 4.0f;
	constexpr float kFinalTargetAppendDistance = 24.0f;
	constexpr float kFinalTargetAppendVerticalDistance = 36.0f;
	constexpr float kJumpLinkCostPenalty = 140.0f;
	constexpr float kWaypointArrivalRadius = 30.0f;
	constexpr float kWaypointVerticalTolerance = 90.0f;
	constexpr float kWaypointOvershootProgress = 1.03f;
	constexpr float kWaypointResyncDistanceGain = 40.0f;
	constexpr size_t kWaypointResyncLookahead = 4;
	constexpr float kStuckWaypointTimeoutSeconds = 2.40f;
	constexpr float kStuckProgressEpsilon = 10.0f;
	constexpr size_t kStuckRebuildThreshold = 3;
	constexpr float kStuckReverseDurationSeconds = 0.42f;
	constexpr float kStuckRecoveryCooldownSeconds = 1.25f;
	constexpr float kTurnDeadzone = 0.12f;
	constexpr float kMoveWhileTurningThreshold = 0.38f;
	constexpr float kTurnPulseMinDurationSeconds = 0.008f;
	constexpr float kTurnPulseMaxDurationSeconds = 0.035f;
	constexpr float kTurnPulseCooldownSeconds = 0.030f;
	constexpr float kTurnPulseFullScaleError = 1.10f;
	constexpr float kJumpTurnThreshold = 0.16f;
	constexpr float kJumpStartTolerance = 55.0f;
	constexpr float kJumpSegmentHorizontalMultiplier = 2.4f;
	constexpr float kJumpSegmentVerticalThreshold = 22.0f;
	constexpr float kJumpTapDurationSeconds = 0.08f;
	constexpr float kJumpCooldownSeconds = 0.75f;
	constexpr float kJumpSteerLockSeconds = 0.55f;
	constexpr float kTurnProbeDurationSeconds = 0.10f;
	constexpr float kTurnRestoreTimeoutSeconds = 0.60f;
	constexpr float kForwardProbeDurationSeconds = 0.16f;
	constexpr float kForwardProbeMinDistance = 6.0f;

	struct Vec3
	{
		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;
	};

	struct PlayerState
	{
		Vec3 position;
		float rotation = 0.0f;
		bool valid = false;
	};

	enum class LinkKind
	{
		Walk,
		Jump,
	};

	struct GraphLink
	{
		int to = -1;
		LinkKind kind = LinkKind::Walk;
	};

	struct GraphNode
	{
		int id = -1;
		Vec3 position;
		std::vector<GraphLink> links;
		bool valid = false;
	};

	struct RuntimeGraph
	{
		bool loaded = false;
		float cellSize = kDefaultGridCellSize;
		std::vector<GraphNode> nodes;
		std::filesystem::path sourcePath;
		std::filesystem::file_time_type sourceWriteTime{};
	};

	enum class SimulatedKey
	{
		Forward,
		Backward,
		StrafeLeft,
		StrafeRight,
		Jump,
		TurnLeft,
		TurnRight,
	};

	enum class CalibrationStage
	{
		None,
		ProbingForwardInitial,
		ProbingTurn,
		ProbingForwardTurned,
		Done,
		Failed,
	};

	struct NavigatorState
	{
		bool active = false;
		bool calibrated = false;
		bool rightArrowIncreasesYaw = false;
		float yawWorldSign = 1.0f;
		float yawWorldOffset = 0.0f;
		float gridCellSize = kDefaultGridCellSize;
		std::vector<Vec3> pathPoints;
		std::vector<bool> segmentRequiresJump;
		size_t targetIndex = 0;
		bool hasRuntimeGoal = false;
		Vec3 runtimeGoal;
		bool jumpIssuedForSegment = false;
		std::string status = "Idle";
		size_t monitoredWaypointIndex = std::numeric_limits<size_t>::max();
		float monitoredWaypointBestScore = std::numeric_limits<float>::max();
		Clock::time_point lastWaypointImprovement = Clock::now();
		bool recoveryBackingUp = false;
		size_t recoveryAttemptCount = 0;
		size_t recoveryClearTargetIndex = std::numeric_limits<size_t>::max();
		Clock::time_point recoveryUntil = Clock::now();
		Clock::time_point lastRecoveryStart = Clock::now() - std::chrono::seconds(5);
		CalibrationStage calibrationStage = CalibrationStage::None;
		PlayerState calibrationPlayerStart;
		float calibrationYawStart = 0.0f;
		float calibrationWorldAngleSample = 0.0f;
		float calibrationRotationSample = 0.0f;
		Clock::time_point calibrationStageStart = Clock::now();
		Clock::time_point lastJumpTap = Clock::now() - std::chrono::seconds(5);
		Clock::time_point lastTurnTap = Clock::now() - std::chrono::seconds(5);
		std::unordered_map<SimulatedKey, bool> keyDownStates;
		std::unordered_map<SimulatedKey, Clock::time_point> keyTapReleaseTimes;
	};

	NavigatorState g_state;
	RuntimeGraph g_runtimeGraph;

	float normalizeAngle(float angle)
	{
		while (angle < 0.0f)
		{
			angle += kTwoPi;
		}
		while (angle >= kTwoPi)
		{
			angle -= kTwoPi;
		}
		return angle;
	}

	float normalizeSignedAngle(float angle)
	{
		angle = std::fmod(angle + kPi, kTwoPi);
		if (angle < 0.0f)
		{
			angle += kTwoPi;
		}
		return angle - kPi;
	}

	float horizontalDistance(const Vec3& a, const Vec3& b)
	{
		const float dx = b.x - a.x;
		const float dz = b.z - a.z;
		return std::sqrt((dx * dx) + (dz * dz));
	}

	float horizontalDot(const Vec3& a, const Vec3& b)
	{
		return (a.x * b.x) + (a.z * b.z);
	}

	float weightedDistanceToPoint(const Vec3& from, const Vec3& to)
	{
		return horizontalDistance(from, to) + (std::abs(to.y - from.y) * 4.0f);
	}

	float durationSecondsSince(const Clock::time_point& start)
	{
		return std::chrono::duration<float>(Clock::now() - start).count();
	}

	float distance3D(const Vec3& a, const Vec3& b)
	{
		const float dx = b.x - a.x;
		const float dy = b.y - a.y;
		const float dz = b.z - a.z;
		return std::sqrt((dx * dx) + (dy * dy) + (dz * dz));
	}

	float graphLinkTravelCost(const GraphNode& fromNode, const GraphNode& toNode, const LinkKind kind)
	{
		float cost = distance3D(fromNode.position, toNode.position);
		if (kind == LinkKind::Jump)
		{
			cost += kJumpLinkCostPenalty;
		}
		return cost;
	}

	std::filesystem::path moduleDirectory()
	{
		HMODULE moduleHandle = nullptr;
		if (!GetModuleHandleExA(
			GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
			reinterpret_cast<LPCSTR>(&moduleDirectory),
			&moduleHandle))
		{
			return std::filesystem::current_path();
		}

		char buffer[MAX_PATH] = {};
		GetModuleFileNameA(moduleHandle, buffer, MAX_PATH);
		return std::filesystem::path(buffer).parent_path();
	}

	std::filesystem::path executableDirectory()
	{
		char buffer[MAX_PATH] = {};
		GetModuleFileNameA(nullptr, buffer, MAX_PATH);
		return std::filesystem::path(buffer).parent_path();
	}

	std::filesystem::path resolveWorkspaceFile(const char* fileName)
	{
		const auto current = std::filesystem::current_path();
		const auto exeDir = executableDirectory();
		const auto moduleDir = moduleDirectory();

		std::vector<std::filesystem::path> roots = {
			current,
			exeDir,
			moduleDir,
			moduleDir.parent_path(),
			moduleDir.parent_path().parent_path(),
			moduleDir.parent_path().parent_path().parent_path(),
		};

		for (const auto& root : roots)
		{
			if (root.empty())
			{
				continue;
			}

			const auto candidate = root / fileName;
			if (std::filesystem::exists(candidate))
			{
				return candidate;
			}
		}

		if (!exeDir.empty())
		{
			return exeDir / fileName;
		}

		return moduleDir / fileName;
	}

	std::filesystem::path resolvePathResultFile()
	{
		return resolveWorkspaceFile(kLegacyPathFileName);
	}

	std::filesystem::path resolveRuntimeGraphFile()
	{
		return resolveWorkspaceFile(kRuntimeGraphFileName);
	}

	PlayerState readPlayerState()
	{
		PlayerState player;
		const DWORD playerPtr = read_value_hobbit<DWORD>((LPVOID)kPlayerPointerAddress);
		if (playerPtr == 0)
		{
			return player;
		}

		player.position.x = read_value_hobbit<float>((LPVOID)(playerPtr + kPlayerPosXOffset));
		player.position.y = read_value_hobbit<float>((LPVOID)(playerPtr + kPlayerPosYOffset));
		player.position.z = read_value_hobbit<float>((LPVOID)(playerPtr + kPlayerPosZOffset));
		player.rotation = normalizeAngle(read_value_hobbit<float>((LPVOID)(playerPtr + kPlayerRotYOffset)));
		player.valid = true;
		return player;
	}

	std::string readFileText(const std::filesystem::path& path)
	{
		std::ifstream file(path, std::ios::binary);
		if (!file)
		{
			return {};
		}

		return std::string(
			(std::istreambuf_iterator<char>(file)),
			std::istreambuf_iterator<char>()
		);
	}

	LinkKind parseLinkKind(const std::string& value)
	{
		return value == "jump" ? LinkKind::Jump : LinkKind::Walk;
	}

	bool isValidGraphNodeId(const int nodeId)
	{
		return nodeId >= 0 &&
			nodeId < static_cast<int>(g_runtimeGraph.nodes.size()) &&
			g_runtimeGraph.nodes[nodeId].valid;
	}

	bool loadRuntimeGraph(std::string& errorMessage)
	{
		const auto graphPath = resolveRuntimeGraphFile();
		if (!std::filesystem::exists(graphPath))
		{
			errorMessage = "Runtime graph missing: " + graphPath.string();
			return false;
		}

		std::error_code timeError;
		const auto writeTime = std::filesystem::last_write_time(graphPath, timeError);
		if (g_runtimeGraph.loaded &&
			g_runtimeGraph.sourcePath == graphPath &&
			(timeError || g_runtimeGraph.sourceWriteTime == writeTime))
		{
			return true;
		}

		std::ifstream file(graphPath);
		if (!file)
		{
			errorMessage = "Could not open runtime graph: " + graphPath.string();
			return false;
		}

		RuntimeGraph parsedGraph;
		parsedGraph.loaded = true;
		parsedGraph.sourcePath = graphPath;
		if (!timeError)
		{
			parsedGraph.sourceWriteTime = writeTime;
		}

		bool headerSeen = false;
		int expectedNodeCount = -1;
		std::string line;
		while (std::getline(file, line))
		{
			if (line.empty())
			{
				continue;
			}

			std::istringstream lineStream(line);
			std::string tag;
			lineStream >> tag;
			if (tag.empty() || tag[0] == '#')
			{
				continue;
			}

			if (tag == "nav_runtime_graph_v1")
			{
				headerSeen = true;
				continue;
			}

			if (tag == "config")
			{
				std::string key;
				std::string value;
				while (lineStream >> key >> value)
				{
					if (key == "cell_size")
					{
						parsedGraph.cellSize = std::stof(value);
					}
				}
				continue;
			}

			if (tag == "stats")
			{
				std::string key;
				std::string value;
				while (lineStream >> key >> value)
				{
					if (key == "node_count")
					{
						expectedNodeCount = std::stoi(value);
					}
				}
				continue;
			}

			if (tag == "node")
			{
				int nodeId = -1;
				float x = 0.0f;
				float y = 0.0f;
				float z = 0.0f;
				if (!(lineStream >> nodeId >> x >> y >> z) || nodeId < 0)
				{
					errorMessage = "Invalid node line in runtime graph";
					return false;
				}

				if (nodeId >= static_cast<int>(parsedGraph.nodes.size()))
				{
					parsedGraph.nodes.resize(nodeId + 1);
				}

				auto& node = parsedGraph.nodes[nodeId];
				node.id = nodeId;
				node.position = { x, y, z };
				node.valid = true;
				continue;
			}

			if (tag == "link")
			{
				int fromId = -1;
				int toId = -1;
				std::string kindValue;
				if (!(lineStream >> fromId >> toId >> kindValue) || fromId < 0 || toId < 0)
				{
					errorMessage = "Invalid link line in runtime graph";
					return false;
				}

				const int maxNodeId = std::max(fromId, toId);
				if (maxNodeId >= static_cast<int>(parsedGraph.nodes.size()))
				{
					parsedGraph.nodes.resize(maxNodeId + 1);
				}

				auto& fromNode = parsedGraph.nodes[fromId];
				fromNode.id = fromId;
				fromNode.links.push_back({ toId, parseLinkKind(kindValue) });
				continue;
			}
		}

		if (!headerSeen)
		{
			errorMessage = "Runtime graph header missing";
			return false;
		}

		int actualNodeCount = 0;
		for (const auto& node : parsedGraph.nodes)
		{
			if (node.valid)
			{
				++actualNodeCount;
			}
		}

		if (actualNodeCount == 0)
		{
			errorMessage = "Runtime graph has no nodes";
			return false;
		}

		if (expectedNodeCount > 0 && actualNodeCount != expectedNodeCount)
		{
			errorMessage = "Runtime graph node count mismatch";
			return false;
		}

		g_runtimeGraph = std::move(parsedGraph);
		return true;
	}

	int nearestGraphNodeId(const Vec3& targetPosition)
	{
		float bestScore = std::numeric_limits<float>::max();
		int bestNodeId = -1;

		for (const auto& node : g_runtimeGraph.nodes)
		{
			if (!node.valid)
			{
				continue;
			}

			const float score = weightedDistanceToPoint(targetPosition, node.position);
			if (score < bestScore)
			{
				bestScore = score;
				bestNodeId = node.id;
			}
		}

		return bestNodeId;
	}

	bool buildPathFromRuntimeGraph(const PlayerState& player, const Vec3& targetPosition, std::string& errorMessage)
	{
		if (!loadRuntimeGraph(errorMessage))
		{
			return false;
		}

		const int startNodeId = nearestGraphNodeId(player.position);
		const int goalNodeId = nearestGraphNodeId(targetPosition);
		if (!isValidGraphNodeId(startNodeId) || !isValidGraphNodeId(goalNodeId))
		{
			errorMessage = "Could not snap player or target to runtime graph";
			return false;
		}

		struct OpenEntry
		{
			float estimatedTotalCost = 0.0f;
			float pathCost = 0.0f;
			int nodeId = -1;
			bool operator<(const OpenEntry& other) const
			{
				return estimatedTotalCost > other.estimatedTotalCost;
			}
		};

		std::priority_queue<OpenEntry> openQueue;
		std::vector<float> bestCosts(g_runtimeGraph.nodes.size(), std::numeric_limits<float>::max());
		std::vector<int> cameFrom(g_runtimeGraph.nodes.size(), -1);
		std::vector<LinkKind> cameByKind(g_runtimeGraph.nodes.size(), LinkKind::Walk);

		bestCosts[startNodeId] = 0.0f;
		openQueue.push(
			{
				distance3D(g_runtimeGraph.nodes[startNodeId].position, g_runtimeGraph.nodes[goalNodeId].position),
				0.0f,
				startNodeId,
			}
		);

		while (!openQueue.empty())
		{
			const OpenEntry current = openQueue.top();
			openQueue.pop();

			if (current.pathCost != bestCosts[current.nodeId])
			{
				continue;
			}

			if (current.nodeId == goalNodeId)
			{
				break;
			}

			const auto& currentNode = g_runtimeGraph.nodes[current.nodeId];
			for (const auto& link : currentNode.links)
			{
				if (!isValidGraphNodeId(link.to))
				{
					continue;
				}

				const auto& targetNode = g_runtimeGraph.nodes[link.to];
				const float nextCost = current.pathCost + graphLinkTravelCost(currentNode, targetNode, link.kind);
				if (nextCost >= bestCosts[link.to])
				{
					continue;
				}

				bestCosts[link.to] = nextCost;
				cameFrom[link.to] = current.nodeId;
				cameByKind[link.to] = link.kind;
				openQueue.push(
					{
						nextCost + distance3D(targetNode.position, g_runtimeGraph.nodes[goalNodeId].position),
						nextCost,
						link.to,
					}
				);
			}
		}

		if (startNodeId != goalNodeId && cameFrom[goalNodeId] < 0)
		{
			errorMessage = "No baked path found to target";
			return false;
		}

		std::vector<int> nodePath;
		for (int currentId = goalNodeId; currentId >= 0; currentId = cameFrom[currentId])
		{
			nodePath.push_back(currentId);
			if (currentId == startNodeId)
			{
				break;
			}
		}
		std::reverse(nodePath.begin(), nodePath.end());

		g_state.pathPoints.clear();
		g_state.segmentRequiresJump.clear();
		g_state.gridCellSize = g_runtimeGraph.cellSize;

		for (size_t index = 0; index < nodePath.size(); ++index)
		{
			g_state.pathPoints.push_back(g_runtimeGraph.nodes[nodePath[index]].position);
			g_state.segmentRequiresJump.push_back(
				index > 0 && cameByKind[nodePath[index]] == LinkKind::Jump
			);
		}

		const Vec3& goalNodePosition = g_runtimeGraph.nodes[goalNodeId].position;
		if (horizontalDistance(goalNodePosition, targetPosition) > kFinalTargetAppendDistance ||
			std::abs(goalNodePosition.y - targetPosition.y) > kFinalTargetAppendVerticalDistance)
		{
			g_state.pathPoints.push_back(targetPosition);
			g_state.segmentRequiresJump.push_back(false);
		}

		return !g_state.pathPoints.empty();
	}

	bool parsePathFound(const std::string& jsonText)
	{
		const auto marker = jsonText.find("\"path_found\"");
		if (marker == std::string::npos)
		{
			return false;
		}

		const auto truePos = jsonText.find("true", marker);
		const auto falsePos = jsonText.find("false", marker);
		if (truePos == std::string::npos)
		{
			return false;
		}
		return falsePos == std::string::npos || truePos < falsePos;
	}

	float parseGridCellSize(const std::string& jsonText)
	{
		static const std::regex sizeRegex(R"("grid_cell_size"\s*:\s*([-+]?\d*\.?\d+(?:[eE][-+]?\d+)?))");
		std::smatch match;
		if (std::regex_search(jsonText, match, sizeRegex) && match.size() >= 2)
		{
			return std::stof(match[1].str());
		}
		return kDefaultGridCellSize;
	}

	Vec3 blenderPointToGamePoint(const Vec3& blenderPoint)
	{
		// import_level.py places Blender points as (game.x, -game.z, game.y)
		return Vec3{
			blenderPoint.x,
			blenderPoint.z,
			-blenderPoint.y,
		};
	}

	std::vector<Vec3> parsePathPoints(const std::string& jsonText)
	{
		std::vector<Vec3> points;

		const auto pathSectionPos = jsonText.find("\"path\"");
		if (pathSectionPos == std::string::npos)
		{
			return points;
		}

		const std::string pathSection = jsonText.substr(pathSectionPos);
		static const std::regex blenderRegex(
			R"("blender"\s*:\s*\[\s*([-+]?\d*\.?\d+(?:[eE][-+]?\d+)?)\s*,\s*([-+]?\d*\.?\d+(?:[eE][-+]?\d+)?)\s*,\s*([-+]?\d*\.?\d+(?:[eE][-+]?\d+)?)\s*\])"
		);
		static const std::regex gameRegex(
			R"("game"\s*:\s*\[\s*([-+]?\d*\.?\d+(?:[eE][-+]?\d+)?)\s*,\s*([-+]?\d*\.?\d+(?:[eE][-+]?\d+)?)\s*,\s*([-+]?\d*\.?\d+(?:[eE][-+]?\d+)?)\s*\])"
		);

		for (std::sregex_iterator it(pathSection.begin(), pathSection.end(), blenderRegex), end; it != end; ++it)
		{
			const auto& match = *it;
			const Vec3 blenderPoint = {
				std::stof(match[1].str()),
				std::stof(match[2].str()),
				std::stof(match[3].str()),
			};
			points.push_back(blenderPointToGamePoint(blenderPoint));
		}

		if (!points.empty())
		{
			return points;
		}

		for (std::sregex_iterator it(pathSection.begin(), pathSection.end(), gameRegex), end; it != end; ++it)
		{
			const auto& match = *it;
			Vec3 point;
			point.x = std::stof(match[1].str());
			point.y = std::stof(match[2].str());
			point.z = std::stof(match[3].str());
			points.push_back(point);
		}

		return points;
	}

	void clearLoadedPath()
	{
		g_state.pathPoints.clear();
		g_state.segmentRequiresJump.clear();
		g_state.gridCellSize = kDefaultGridCellSize;
	}

	bool loadPathFromFile(std::string& errorMessage)
	{
		const auto pathFile = resolvePathResultFile();
		const auto jsonText = readFileText(pathFile);
		if (jsonText.empty())
		{
			clearLoadedPath();
			errorMessage = "Path file missing: " + pathFile.string();
			return false;
		}

		if (!parsePathFound(jsonText))
		{
			clearLoadedPath();
			errorMessage = "Path file says no path found";
			return false;
		}

		auto parsedPoints = parsePathPoints(jsonText);
		if (parsedPoints.size() < 2)
		{
			clearLoadedPath();
			errorMessage = "Path file has too few points";
			return false;
		}

		g_state.pathPoints = std::move(parsedPoints);
		g_state.gridCellSize = parseGridCellSize(jsonText);
		g_state.segmentRequiresJump.assign(g_state.pathPoints.size(), false);

		for (size_t index = 1; index < g_state.pathPoints.size(); ++index)
		{
			const float horizontal = horizontalDistance(g_state.pathPoints[index - 1], g_state.pathPoints[index]);
			const float vertical = g_state.pathPoints[index].y - g_state.pathPoints[index - 1].y;
			g_state.segmentRequiresJump[index] =
				(horizontal >= (g_state.gridCellSize * kJumpSegmentHorizontalMultiplier)) ||
				(std::abs(vertical) >= kJumpSegmentVerticalThreshold);
		}

		return true;
	}

	size_t findNearestPathIndex(const PlayerState& player)
	{
		size_t bestIndex = 0;
		float bestScore = std::numeric_limits<float>::max();

		for (size_t index = 0; index < g_state.pathPoints.size(); ++index)
		{
			const float score = weightedDistanceToPoint(player.position, g_state.pathPoints[index]);
			if (score < bestScore)
			{
				bestScore = score;
				bestIndex = index;
			}
		}

		return bestIndex;
	}

	WORD keyToVirtualKey(const SimulatedKey key)
	{
		switch (key)
		{
		case SimulatedKey::Forward: return 'W';
		case SimulatedKey::Backward: return 'S';
		case SimulatedKey::StrafeLeft: return 'A';
		case SimulatedKey::StrafeRight: return 'D';
		case SimulatedKey::Jump: return VK_SPACE;
		case SimulatedKey::TurnLeft: return VK_LEFT;
		case SimulatedKey::TurnRight: return VK_RIGHT;
		default: return 0;
		}
	}

	bool isExtendedKey(const SimulatedKey key)
	{
		return key == SimulatedKey::TurnLeft || key == SimulatedKey::TurnRight;
	}

	void sendVirtualKey(const SimulatedKey key, const bool pressed)
	{
		const WORD vk = keyToVirtualKey(key);
		if (vk == 0)
		{
			return;
		}

		INPUT input = {};
		input.type = INPUT_KEYBOARD;
		input.ki.wVk = vk;
		input.ki.wScan = static_cast<WORD>(MapVirtualKeyW(vk, MAPVK_VK_TO_VSC));
		if (!pressed)
		{
			input.ki.dwFlags |= KEYEVENTF_KEYUP;
		}
		if (isExtendedKey(key))
		{
			input.ki.dwFlags |= KEYEVENTF_EXTENDEDKEY;
		}

		SendInput(1, &input, sizeof(INPUT));
	}

	void setKeyState(const SimulatedKey key, const bool shouldBeDown)
	{
		const bool currentlyDown = g_state.keyDownStates[key];
		if (currentlyDown == shouldBeDown)
		{
			return;
		}

		sendVirtualKey(key, shouldBeDown);
		g_state.keyDownStates[key] = shouldBeDown;
	}

	void releaseAllKeys()
	{
		for (const auto key : {
			SimulatedKey::Forward,
			SimulatedKey::Backward,
			SimulatedKey::StrafeLeft,
			SimulatedKey::StrafeRight,
			SimulatedKey::Jump,
			SimulatedKey::TurnLeft,
			SimulatedKey::TurnRight,
		})
		{
			setKeyState(key, false);
		}
		g_state.keyTapReleaseTimes.clear();
	}

	void tapKey(const SimulatedKey key, const float durationSeconds)
	{
		setKeyState(key, true);
		g_state.keyTapReleaseTimes[key] = Clock::now() + std::chrono::duration_cast<Clock::duration>(
			std::chrono::duration<float>(durationSeconds)
		);
	}

	void cancelTapKey(const SimulatedKey key)
	{
		g_state.keyTapReleaseTimes.erase(key);
		setKeyState(key, false);
	}

	bool isTapActive(const SimulatedKey key)
	{
		const auto it = g_state.keyTapReleaseTimes.find(key);
		return it != g_state.keyTapReleaseTimes.end() && Clock::now() < it->second;
	}

	void updateTapKeys()
	{
		const auto now = Clock::now();
		for (auto it = g_state.keyTapReleaseTimes.begin(); it != g_state.keyTapReleaseTimes.end();)
		{
			if (now >= it->second)
			{
				setKeyState(it->first, false);
				it = g_state.keyTapReleaseTimes.erase(it);
			}
			else
			{
				++it;
			}
		}
	}

	void stopNavigation(const std::string& reason)
	{
		releaseAllKeys();
		g_state.active = false;
		g_state.hasRuntimeGoal = false;
		g_state.jumpIssuedForSegment = false;
		g_state.recoveryBackingUp = false;
		g_state.recoveryAttemptCount = 0;
		g_state.recoveryClearTargetIndex = std::numeric_limits<size_t>::max();
		g_state.monitoredWaypointIndex = std::numeric_limits<size_t>::max();
		g_state.monitoredWaypointBestScore = std::numeric_limits<float>::max();
		g_state.targetIndex = 0;
		g_state.status = reason;
	}

	void resetRecoveryAttempts()
	{
		g_state.recoveryAttemptCount = 0;
		g_state.recoveryClearTargetIndex = std::numeric_limits<size_t>::max();
	}

	void maybeResetRecoveryAttemptsForProgress()
	{
		if (g_state.recoveryAttemptCount == 0)
		{
			return;
		}

		if (g_state.recoveryClearTargetIndex == std::numeric_limits<size_t>::max())
		{
			return;
		}

		if (g_state.targetIndex > g_state.recoveryClearTargetIndex)
		{
			resetRecoveryAttempts();
		}
	}

	void alignPathToPlayer(const PlayerState& player)
	{
		g_state.targetIndex = 0;
		if (!g_state.pathPoints.empty())
		{
			g_state.targetIndex = findNearestPathIndex(player);
		}

		if (g_state.targetIndex + 1 < g_state.pathPoints.size())
		{
			const float nearestDistance = horizontalDistance(player.position, g_state.pathPoints[g_state.targetIndex]);
			if (nearestDistance <= kWaypointArrivalRadius)
			{
				++g_state.targetIndex;
			}
		}
	}

	bool rebuildRuntimePathFromCurrentPosition(const PlayerState& player, std::string& errorMessage)
	{
		if (!g_state.hasRuntimeGoal)
		{
			errorMessage = "No runtime goal to rebuild";
			return false;
		}

		if (!buildPathFromRuntimeGraph(player, g_state.runtimeGoal, errorMessage))
		{
			return false;
		}

		alignPathToPlayer(player);
		g_state.jumpIssuedForSegment = false;
		g_state.recoveryBackingUp = false;
		resetRecoveryAttempts();
		g_state.monitoredWaypointIndex = std::numeric_limits<size_t>::max();
		g_state.monitoredWaypointBestScore = std::numeric_limits<float>::max();
		g_state.lastWaypointImprovement = Clock::now();
		return true;
	}

	void resetWaypointMonitor(const PlayerState& player)
	{
		if (g_state.targetIndex >= g_state.pathPoints.size())
		{
			g_state.monitoredWaypointIndex = std::numeric_limits<size_t>::max();
			g_state.monitoredWaypointBestScore = std::numeric_limits<float>::max();
			g_state.lastWaypointImprovement = Clock::now();
			return;
		}

		g_state.monitoredWaypointIndex = g_state.targetIndex;
		g_state.monitoredWaypointBestScore = weightedDistanceToPoint(
			player.position,
			g_state.pathPoints[g_state.targetIndex]
		);
		g_state.lastWaypointImprovement = Clock::now();
	}

	void updateWaypointMonitor(const PlayerState& player)
	{
		if (g_state.targetIndex >= g_state.pathPoints.size())
		{
			return;
		}

		const float currentScore = weightedDistanceToPoint(player.position, g_state.pathPoints[g_state.targetIndex]);
		if (g_state.monitoredWaypointIndex != g_state.targetIndex)
		{
			g_state.monitoredWaypointIndex = g_state.targetIndex;
			g_state.monitoredWaypointBestScore = currentScore;
			g_state.lastWaypointImprovement = Clock::now();
			return;
		}

		if ((g_state.monitoredWaypointBestScore - currentScore) >= kStuckProgressEpsilon)
		{
			g_state.monitoredWaypointBestScore = currentScore;
			g_state.lastWaypointImprovement = Clock::now();
			return;
		}

		if (currentScore < g_state.monitoredWaypointBestScore)
		{
			g_state.monitoredWaypointBestScore = currentScore;
		}
	}

	bool maybeBeginStuckRecovery(const PlayerState& player)
	{
		if (g_state.targetIndex >= g_state.pathPoints.size() || g_state.recoveryBackingUp)
		{
			return false;
		}

		updateWaypointMonitor(player);

		if (durationSecondsSince(g_state.lastRecoveryStart) < kStuckRecoveryCooldownSeconds)
		{
			return false;
		}

		if (durationSecondsSince(g_state.lastJumpTap) < (kJumpSteerLockSeconds + 0.20f))
		{
			return false;
		}

		if (durationSecondsSince(g_state.lastWaypointImprovement) < kStuckWaypointTimeoutSeconds)
		{
			return false;
		}

		if (g_state.hasRuntimeGoal && (g_state.recoveryAttemptCount + 1) >= kStuckRebuildThreshold)
		{
			std::string errorMessage;
			if (rebuildRuntimePathFromCurrentPosition(player, errorMessage))
			{
				g_state.lastRecoveryStart = Clock::now();
				g_state.status = "Stuck: rebuilt path";
				return true;
			}
		}

		const size_t currentTargetIndex = g_state.targetIndex;
		const size_t backtrackCount = g_state.recoveryAttemptCount + 1;
		g_state.recoveryAttemptCount = backtrackCount;
		if (g_state.recoveryClearTargetIndex == std::numeric_limits<size_t>::max())
		{
			g_state.recoveryClearTargetIndex = currentTargetIndex;
		}
		else
		{
			g_state.recoveryClearTargetIndex = std::max(g_state.recoveryClearTargetIndex, currentTargetIndex);
		}

		if (currentTargetIndex > 0)
		{
			g_state.targetIndex = currentTargetIndex > backtrackCount
				? currentTargetIndex - backtrackCount
				: 0;
		}

		g_state.jumpIssuedForSegment = false;
		g_state.recoveryBackingUp = true;
		g_state.recoveryUntil = Clock::now() + std::chrono::duration_cast<Clock::duration>(
			std::chrono::duration<float>(kStuckReverseDurationSeconds * static_cast<float>(backtrackCount))
		);
		g_state.lastRecoveryStart = Clock::now();
		resetWaypointMonitor(player);
		g_state.status = "Stuck: backing up " + std::to_string(static_cast<int>(backtrackCount)) + " waypoint(s)";
		return true;
	}

	void beginCalibration(const PlayerState& player)
	{
		g_state.calibrationStage = CalibrationStage::ProbingForwardInitial;
		g_state.calibrationYawStart = player.rotation;
		g_state.calibrationStageStart = Clock::now();
		g_state.calibrationPlayerStart = player;
		g_state.status = "Calibrating forward";
	}

	bool updateCalibration(const HWND gameWindow, const PlayerState& player)
	{
		(void)gameWindow;

		switch (g_state.calibrationStage)
		{
		case CalibrationStage::None:
			beginCalibration(player);
			return false;

		case CalibrationStage::ProbingForwardInitial:
		{
			setKeyState(SimulatedKey::Forward, true);
			if (durationSecondsSince(g_state.calibrationStageStart) < kForwardProbeDurationSeconds)
			{
				return false;
			}

			setKeyState(SimulatedKey::Forward, false);
			const Vec3 delta = {
				player.position.x - g_state.calibrationPlayerStart.position.x,
				player.position.y - g_state.calibrationPlayerStart.position.y,
				player.position.z - g_state.calibrationPlayerStart.position.z,
			};

			const float horizontal = std::sqrt((delta.x * delta.x) + (delta.z * delta.z));
			if (horizontal < kForwardProbeMinDistance)
			{
				g_state.calibrationStage = CalibrationStage::Failed;
				g_state.status = "Calibration failed: move forward";
				return false;
			}

			g_state.calibrationWorldAngleSample = std::atan2(delta.z, delta.x);
			g_state.calibrationRotationSample = g_state.calibrationPlayerStart.rotation;
			g_state.calibrationYawStart = player.rotation;
			g_state.calibrationStage = CalibrationStage::ProbingTurn;
			g_state.calibrationStageStart = Clock::now();
			g_state.status = "Calibrating turn";
			return false;
		}

		case CalibrationStage::ProbingTurn:
		{
			setKeyState(SimulatedKey::TurnRight, true);
			if (durationSecondsSince(g_state.calibrationStageStart) < kTurnProbeDurationSeconds)
			{
				return false;
			}

			setKeyState(SimulatedKey::TurnRight, false);
			const float yawDelta = normalizeSignedAngle(player.rotation - g_state.calibrationYawStart);
			if (std::abs(yawDelta) < 0.01f)
			{
				g_state.calibrationStage = CalibrationStage::Failed;
				g_state.status = "Calibration failed: turn probe";
				return false;
			}

			// Game-specific behavior is known: right arrow decreases yaw, left arrow increases it.
			g_state.rightArrowIncreasesYaw = false;
			g_state.calibrationStage = CalibrationStage::ProbingForwardTurned;
			g_state.calibrationStageStart = Clock::now();
			g_state.calibrationPlayerStart = player;
			g_state.status = "Calibrating turned forward";
			return false;
		}

		case CalibrationStage::ProbingForwardTurned:
		{
			setKeyState(SimulatedKey::Forward, true);
			if (durationSecondsSince(g_state.calibrationStageStart) < kForwardProbeDurationSeconds)
			{
				return false;
			}

			setKeyState(SimulatedKey::Forward, false);
			const Vec3 delta = {
				player.position.x - g_state.calibrationPlayerStart.position.x,
				player.position.y - g_state.calibrationPlayerStart.position.y,
				player.position.z - g_state.calibrationPlayerStart.position.z,
			};

			const float horizontal = std::sqrt((delta.x * delta.x) + (delta.z * delta.z));
			if (horizontal < kForwardProbeMinDistance)
			{
				g_state.calibrationStage = CalibrationStage::Failed;
				g_state.status = "Calibration failed: move forward";
				return false;
			}

			const float worldForwardAngle = std::atan2(delta.z, delta.x);
			const float rotationDelta = normalizeSignedAngle(
				g_state.calibrationPlayerStart.rotation - g_state.calibrationRotationSample
			);
			const float worldDelta = normalizeSignedAngle(
				worldForwardAngle - g_state.calibrationWorldAngleSample
			);

			if (std::abs(rotationDelta) < 0.01f || std::abs(worldDelta) < 0.01f)
			{
				g_state.calibrationStage = CalibrationStage::Failed;
				g_state.status = "Calibration failed: yaw mapping";
				return false;
			}

			g_state.yawWorldSign = ((rotationDelta * worldDelta) >= 0.0f) ? 1.0f : -1.0f;
			g_state.yawWorldOffset = normalizeAngle(
				g_state.calibrationWorldAngleSample - (g_state.yawWorldSign * g_state.calibrationRotationSample)
			);
			g_state.calibrationStage = CalibrationStage::Done;
			g_state.calibrated = true;
			g_state.status = g_state.yawWorldSign > 0.0f ? "Calibrated" : "Calibrated (reversed yaw)";
			return true;
		}

		case CalibrationStage::Done:
			return true;

		case CalibrationStage::Failed:
			return false;
		}

		return false;
	}

	float desiredYawForTarget(const Vec3& from, const Vec3& target)
	{
		const float worldAngle = std::atan2(target.z - from.z, target.x - from.x);
		if (g_state.yawWorldSign < 0.0f)
		{
			return normalizeAngle(g_state.yawWorldOffset - worldAngle);
		}

		return normalizeAngle(worldAngle - g_state.yawWorldOffset);
	}

	void advanceWaypointIfNeeded(const PlayerState& player)
	{
		while (g_state.targetIndex < g_state.pathPoints.size())
		{
			const auto& target = g_state.pathPoints[g_state.targetIndex];
			const float horizontal = horizontalDistance(player.position, target);
			const float vertical = std::abs(player.position.y - target.y);
			bool shouldAdvance = horizontal <= kWaypointArrivalRadius && vertical <= kWaypointVerticalTolerance;

			if (!shouldAdvance && g_state.targetIndex > 0)
			{
				const auto& previous = g_state.pathPoints[g_state.targetIndex - 1];
				const Vec3 segment = {
					target.x - previous.x,
					0.0f,
					target.z - previous.z,
				};
				const Vec3 toPlayer = {
					player.position.x - previous.x,
					0.0f,
					player.position.z - previous.z,
				};
				const float segmentLengthSq = horizontalDot(segment, segment);
				if (segmentLengthSq > 1.0f)
				{
					const float progress = horizontalDot(toPlayer, segment) / segmentLengthSq;
					shouldAdvance = progress >= kWaypointOvershootProgress;
				}
			}

			if (!shouldAdvance)
			{
				break;
			}

			++g_state.targetIndex;
			g_state.jumpIssuedForSegment = false;
			maybeResetRecoveryAttemptsForProgress();
		}
	}

	void resyncWaypointAhead(const PlayerState& player)
	{
		if (g_state.targetIndex >= g_state.pathPoints.size())
		{
			return;
		}

		const float currentScore = weightedDistanceToPoint(player.position, g_state.pathPoints[g_state.targetIndex]);
		size_t bestIndex = g_state.targetIndex;
		float bestScore = currentScore;
		const size_t lookaheadEnd = std::min(g_state.pathPoints.size(), g_state.targetIndex + kWaypointResyncLookahead + 1);

		for (size_t index = g_state.targetIndex + 1; index < lookaheadEnd; ++index)
		{
			const float score = weightedDistanceToPoint(player.position, g_state.pathPoints[index]);
			if (score < bestScore)
			{
				bestScore = score;
				bestIndex = index;
			}
		}

		if (bestIndex > g_state.targetIndex && (bestScore + kWaypointResyncDistanceGain) < currentScore)
		{
			g_state.targetIndex = bestIndex;
			g_state.jumpIssuedForSegment = false;
			maybeResetRecoveryAttemptsForProgress();
		}
	}

	void updateMovement(const PlayerState& player)
	{
		if (g_state.targetIndex >= g_state.pathPoints.size())
		{
			stopNavigation("Path complete");
			return;
		}

		if (g_state.recoveryBackingUp)
		{
			cancelTapKey(SimulatedKey::TurnLeft);
			cancelTapKey(SimulatedKey::TurnRight);
			cancelTapKey(SimulatedKey::Jump);
			setKeyState(SimulatedKey::Forward, false);
			setKeyState(SimulatedKey::StrafeLeft, false);
			setKeyState(SimulatedKey::StrafeRight, false);

			if (Clock::now() < g_state.recoveryUntil)
			{
				setKeyState(SimulatedKey::Backward, true);
				g_state.status = "Recovering: backing up";
				return;
			}

			setKeyState(SimulatedKey::Backward, false);
			g_state.recoveryBackingUp = false;
			resetWaypointMonitor(player);
		}

		if (maybeBeginStuckRecovery(player))
		{
			setKeyState(SimulatedKey::Forward, false);
			setKeyState(SimulatedKey::StrafeLeft, false);
			setKeyState(SimulatedKey::StrafeRight, false);
			setKeyState(SimulatedKey::Backward, g_state.recoveryBackingUp);
			return;
		}

		const Vec3& target = g_state.pathPoints[g_state.targetIndex];
		const float desiredYaw = desiredYawForTarget(player.position, target);
		const float yawError = normalizeSignedAngle(desiredYaw - player.rotation);
		const float absYawError = std::abs(yawError);
		const bool jumpSteerLocked = g_state.jumpIssuedForSegment &&
			(durationSecondsSince(g_state.lastJumpTap) < kJumpSteerLockSeconds);

		const bool needIncrease = yawError > 0.0f;
		const bool pressRight = g_state.rightArrowIncreasesYaw ? needIncrease : !needIncrease;
		const bool turning = absYawError > kTurnDeadzone;
		const SimulatedKey desiredTurnKey = pressRight ? SimulatedKey::TurnRight : SimulatedKey::TurnLeft;
		const SimulatedKey oppositeTurnKey = pressRight ? SimulatedKey::TurnLeft : SimulatedKey::TurnRight;

		cancelTapKey(oppositeTurnKey);
		if (jumpSteerLocked)
		{
			cancelTapKey(desiredTurnKey);
		}
		else if (!turning)
		{
			cancelTapKey(desiredTurnKey);
		}
		else if (!isTapActive(desiredTurnKey) && durationSecondsSince(g_state.lastTurnTap) >= kTurnPulseCooldownSeconds)
		{
			const float normalizedError = std::clamp(absYawError / kTurnPulseFullScaleError, 0.0f, 1.0f);
			const float pulseDuration = kTurnPulseMinDurationSeconds +
				((kTurnPulseMaxDurationSeconds - kTurnPulseMinDurationSeconds) * normalizedError);
			tapKey(desiredTurnKey, pulseDuration);
			g_state.lastTurnTap = Clock::now();
		}

		setKeyState(SimulatedKey::Backward, false);
		setKeyState(SimulatedKey::StrafeLeft, false);
		setKeyState(SimulatedKey::StrafeRight, false);

		const bool canMoveForward = jumpSteerLocked || absYawError <= kMoveWhileTurningThreshold;
		setKeyState(SimulatedKey::Forward, canMoveForward);

		const size_t segmentIndex = g_state.targetIndex;
		if (segmentIndex < g_state.segmentRequiresJump.size() && g_state.segmentRequiresJump[segmentIndex] && !g_state.jumpIssuedForSegment)
		{
			const Vec3& segmentStart = g_state.pathPoints[segmentIndex - 1];
			const float distanceFromSegmentStart = horizontalDistance(player.position, segmentStart);
			const float timeSinceLastJump = durationSecondsSince(g_state.lastJumpTap);
			if (distanceFromSegmentStart <= kJumpStartTolerance &&
				std::abs(yawError) <= kJumpTurnThreshold &&
				timeSinceLastJump >= kJumpCooldownSeconds)
			{
				tapKey(SimulatedKey::Jump, kJumpTapDurationSeconds);
				g_state.lastJumpTap = Clock::now();
				g_state.jumpIssuedForSegment = true;
			}
		}

		g_state.status = std::string(jumpSteerLocked ? "Jumping to waypoint " : "Moving to waypoint ") +
			std::to_string(static_cast<int>(g_state.targetIndex + 1)) +
			"/" + std::to_string(static_cast<int>(g_state.pathPoints.size()));
	}
}

void path_navigator::Toggle(HWND gameWindow) noexcept
{
	if (g_state.active)
	{
		stopNavigation("Stopped");
		return;
	}

	const PlayerState player = readPlayerState();
	if (!player.valid)
	{
		g_state.status = "Player not available";
		return;
	}

	std::string errorMessage;
	float targetX = 0.0f;
	float targetY = 0.0f;
	float targetZ = 0.0f;
	g_state.hasRuntimeGoal = false;
	if (gui::GetTeleportPoint(targetX, targetY, targetZ))
	{
		g_state.hasRuntimeGoal = true;
		g_state.runtimeGoal = { targetX, targetY, targetZ };
		if (!buildPathFromRuntimeGraph(player, g_state.runtimeGoal, errorMessage))
		{
			g_state.hasRuntimeGoal = false;
			g_state.status = errorMessage;
			return;
		}
	}
	else if (!loadPathFromFile(errorMessage))
	{
		g_state.status = "Set target with Y first. " + errorMessage;
		return;
	}
	else
	{
		g_state.hasRuntimeGoal = false;
	}

	alignPathToPlayer(player);

	g_state.active = true;
	g_state.jumpIssuedForSegment = false;
	g_state.recoveryBackingUp = false;
	g_state.recoveryAttemptCount = 0;
	g_state.recoveryClearTargetIndex = std::numeric_limits<size_t>::max();
	g_state.lastJumpTap = Clock::now() - std::chrono::seconds(5);
	g_state.lastTurnTap = Clock::now() - std::chrono::seconds(5);
	g_state.lastRecoveryStart = Clock::now() - std::chrono::seconds(5);
	releaseAllKeys();
	resetWaypointMonitor(player);

	if (!g_state.calibrated)
	{
		g_state.calibrationStage = CalibrationStage::None;
		g_state.status = "Starting calibration";
	}
	else
	{
		g_state.status = gui::HasTeleportPoint() ? "Computed graph path" : "Loaded legacy path";
	}

	if (GetForegroundWindow() != gameWindow)
	{
		g_state.status = "Waiting for game focus";
	}
}

void path_navigator::Update(HWND gameWindow) noexcept
{
	updateTapKeys();

	if (!g_state.active)
	{
		return;
	}

	if (gameWindow == nullptr || GetForegroundWindow() != gameWindow)
	{
		releaseAllKeys();
		g_state.status = "Paused: game not focused";
		return;
	}

	const PlayerState player = readPlayerState();
	if (!player.valid)
	{
		stopNavigation("Player not available");
		return;
	}

	if (!g_state.calibrated)
	{
		if (!updateCalibration(gameWindow, player))
		{
			if (g_state.calibrationStage == CalibrationStage::Failed)
			{
				stopNavigation(g_state.status);
			}
			return;
		}
	}

	advanceWaypointIfNeeded(player);
	resyncWaypointAhead(player);
	if (!g_state.active)
	{
		return;
	}

	updateMovement(player);
}

void path_navigator::Shutdown() noexcept
{
	stopNavigation("Idle");
}

bool path_navigator::IsActive() noexcept
{
	return g_state.active;
}

bool path_navigator::IsCalibrated() noexcept
{
	return g_state.calibrated;
}

int path_navigator::GetCurrentWaypointIndex() noexcept
{
	return static_cast<int>(g_state.targetIndex);
}

int path_navigator::GetPathPointCount() noexcept
{
	return static_cast<int>(g_state.pathPoints.size());
}

const char* path_navigator::GetStatusText() noexcept
{
	return g_state.status.c_str();
}
