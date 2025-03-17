#pragma once
#include <unordered_map>
#include <string>

inline std::unordered_map<const char*, int> settings = {
		{"devMode", 0},
		{"fps60", 0},
		{"renderVolumes", 0},
		{"polyCache", 0},
		{"renderLoadTriggers", 0},
		{"renderTriggers", 0},
		{"renderWater", 0},
		{"renderWeb", 0},
		{"renderRopes", 0},
		{"renderLeaves", 0},
		{"renderChests", 0},
		{"renderLevers", 0},
		{"renderBilbo", 0},
		{"renderLights", 0},
		{"renderEffects", 0},
		{"breakway", 0},
		{"boulderRun", 0},
		{"renderSkybox", 0},
		{"renderSavePedestal", 0},
		{"renderPushBoxes", 0},
		{"renderRigidInstances", 0},
		{"renderPlaySurface", 0},
		{"renderGeometry", 0}
};

namespace functions
{
	void developerMode() noexcept;
	void fps60() noexcept;
	void renderVolumes() noexcept;
	void polyCache() noexcept;
	void renderLoadTriggers() noexcept;
	void renderTriggers() noexcept;
	void renderWater() noexcept;
	void renderWeb() noexcept;
	void renderRopes() noexcept;
	void renderLeaves() noexcept;
	void renderChests() noexcept;
	void renderLevers() noexcept;
	void renderBilbo() noexcept;
	void renderLights() noexcept;
	void renderEffects() noexcept;
	void breakway() noexcept;
	void boulderRun() noexcept;
	void renderSkybox() noexcept;
	void renderSavePedestal() noexcept;
	void renderPushBoxes() noexcept;
	void renderRigidInstances() noexcept;
	void renderPlaySurface() noexcept;
	void renderGeometry() noexcept;
	void renderHud() noexcept;
	void increaseFOV() noexcept;
	void decreaseFOV() noexcept;
}
