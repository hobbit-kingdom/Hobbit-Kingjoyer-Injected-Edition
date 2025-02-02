#include "gui.h"
#include "byte_functions.h"
#include "Randommod.h"
#include "PickupAll.h"
#include "functions.h"

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_dx9.h"
#include "../imgui/imgui_impl_win32.h"

#include <iostream>
#include "string"
#include <chrono>
#include <random>
#include <thread>
#include <filesystem>

using namespace std::chrono;
using namespace std;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(
	HWND window,
	UINT message,
	WPARAM wideParameter,
	LPARAM longParameter
);

long __stdcall WindowProcess(
	HWND window,
	UINT message,
	WPARAM wideParameter,
	LPARAM longParameter)
{
	if (ImGui_ImplWin32_WndProcHandler(window, message, wideParameter, longParameter))
		return true;

	switch (message)
	{
	case WM_SIZE: {
		if (gui::device && wideParameter != SIZE_MINIMIZED)
		{
			gui::presentParameters.BackBufferWidth = LOWORD(longParameter);
			gui::presentParameters.BackBufferHeight = HIWORD(longParameter);
			gui::ResetDevice();
		}
	}return 0;

	case WM_SYSCOMMAND: {
		if ((wideParameter & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
			return 0;
	}break;

	case WM_DESTROY: {
		PostQuitMessage(0);
	}return 0;

	case WM_LBUTTONDOWN: {
		gui::position = MAKEPOINTS(longParameter); // set click points
	}return 0;

	case WM_MOUSEMOVE: {
		if (wideParameter == MK_LBUTTON)
		{
			const auto points = MAKEPOINTS(longParameter);
			auto rect = ::RECT{ };

			GetWindowRect(gui::window, &rect);

			rect.left += points.x - gui::position.x;
			rect.top += points.y - gui::position.y;

			if (gui::position.x >= 0 &&
				gui::position.x <= gui::WIDTH &&
				gui::position.y >= 0 && gui::position.y <= 19)
				SetWindowPos(
					gui::window,
					HWND_TOPMOST,
					rect.left,
					rect.top,
					0, 0,
					SWP_SHOWWINDOW | SWP_NOSIZE | SWP_NOZORDER
				);
		}

	}return 0;

	}

	return DefWindowProc(window, message, wideParameter, longParameter);
}

void gui::CreateHWindow(LPCWSTR windowName) noexcept
{
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_CLASSDC;
	windowClass.lpfnWndProc = WindowProcess;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = GetModuleHandleA(0);
	windowClass.hIcon = 0;
	windowClass.hCursor = 0;
	windowClass.hbrBackground = 0;
	windowClass.lpszMenuName = 0;
	windowClass.lpszClassName = L"class001";
	windowClass.hIconSm = 0;

	RegisterClassEx(&windowClass);

	window = CreateWindowEx(
		0,
		L"class001",
		windowName,
		WS_POPUP,
		100,
		100,
		WIDTH,
		HEIGHT,
		0,
		0,
		windowClass.hInstance,
		0
	);

	ShowWindow(window, SW_SHOWDEFAULT);
	UpdateWindow(window);
}

void gui::DestroyHWindow() noexcept
{
	DestroyWindow(window);
	UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
}

bool gui::CreateDevice() noexcept
{
	d3d = Direct3DCreate9(D3D_SDK_VERSION);

	if (!d3d)
		return false;

	ZeroMemory(&presentParameters, sizeof(presentParameters));

	presentParameters.Windowed = TRUE;
	presentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	presentParameters.BackBufferFormat = D3DFMT_UNKNOWN;
	presentParameters.EnableAutoDepthStencil = TRUE;
	presentParameters.AutoDepthStencilFormat = D3DFMT_D16;
	presentParameters.PresentationInterval = D3DPRESENT_INTERVAL_ONE;

	if (d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		window,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&presentParameters,
		&device) < 0)
		return false;

	return true;
}

void gui::ResetDevice() noexcept
{
	ImGui_ImplDX9_InvalidateDeviceObjects();

	const auto result = device->Reset(&presentParameters);

	if (result == D3DERR_INVALIDCALL)
		IM_ASSERT(0);

	ImGui_ImplDX9_CreateDeviceObjects();
}

void gui::DestroyDevice() noexcept
{
	if (device)
	{
		device->Release();
		device = nullptr;
	}

	if (d3d)
	{
		d3d->Release();
		d3d = nullptr;
	}
}

void gui::CreateImGui() noexcept
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui::GetIO().Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Arial.ttf", 16.5f, NULL, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
	io.IniFilename = NULL;

	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX9_Init(device);
}

void gui::DestroyImGui() noexcept
{
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void gui::BeginRender() noexcept
{
	MSG message;
	while (PeekMessage(&message, 0, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);

		if (message.message == WM_QUIT)
		{
			isRunning = !isRunning;
			return;
		}
	}

	// Start the Dear ImGui frame
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void gui::EndRender() noexcept
{
	ImGui::EndFrame();

	device->SetRenderState(D3DRS_ZENABLE, FALSE);
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	device->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);

	device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(0, 0, 0, 255), 1.0f, 0);

	if (device->BeginScene() >= 0)
	{
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
		device->EndScene();
	}

	const auto result = device->Present(0, 0, 0, 0);

	// Handle loss of D3D9 device
	if (result == D3DERR_DEVICELOST && device->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
		ResetDevice();
}

namespace fs = std::filesystem;
bool copyAndRenameFile(const std::string& sourceFile) {
	try {
		fs::path sourcePath = "./SKINS/" + sourceFile;
		fs::path destDir = "./Common/Bilbo/";

		if (!fs::exists(sourcePath)) {
			std::cerr << "Source file does not exist: " << sourcePath << std::endl;
			return false;
		}

		std::string fileExtension = sourcePath.extension().string();
		fs::path destFilePath = destDir / ("BILBO[D]" + fileExtension);

		fs::create_directories(destDir);

		if (fs::exists(destFilePath)) {
			fs::remove(destFilePath);
			std::cout << "Existing file deleted: " << destFilePath << std::endl;
		}

		fs::copy_file(sourcePath, destFilePath, fs::copy_options::overwrite_existing);
		std::cout << "File copied and renamed to: " << destFilePath << std::endl;
		return true;
	}
	catch (const fs::filesystem_error& e) {
		std::cerr << "Filesystem error: " << e.what() << std::endl;
		return false;
	}
}

void displaySkinButtons(bool lang)
{
	fs::path skinsDir = "./SKINS";

	if (!fs::exists(skinsDir)) {
		ImGui::Text(lang ? "SKINS directory does not exist." : (const char*)u8"����� SKINS �� �������");
		return;
	}

	if (fs::is_empty(skinsDir)) {
		ImGui::Text(lang ? "SKINS directory is empty." : (const char*)u8"����� SKINS �����.");
		return;
	}

	for (const auto& entry : fs::directory_iterator(skinsDir))
	{
		if (entry.is_regular_file())
		{
			fs::path filePath = entry.path();

			if (filePath.extension() == ".xbmp" || filePath.extension() == ".XBMP")
			{
				std::string fileName = filePath.stem().string();

				ImGui::Text("%s", fileName.c_str());
				ImGui::SameLine();

				if (ImGui::Button(("Apply##" + fileName).c_str()))
					copyAndRenameFile(filePath.filename().string());

			}
		}
	}
}

bool developerMode = false;
bool fps60 = false;

bool renderVolumes = false;
bool renderLoadTriggers = false;
bool renderTriggers = false;
bool renderWater = true;
bool renderWeb = true;
bool renderRopes = true;
bool renderLeaves = true;
bool renderChests = true;
bool renderLevers = true;
bool renderBilbo = true;
bool renderLights = false;
bool renderEffects = true;
bool renderSkybox = true;
bool renderSavePedestal = true;
bool renderPushBoxes = true;
bool breakway = true;
bool boulderRun = true;
bool polyCache = false;
bool bilboPos = false;
bool cutsceneInfo = false;
bool objInfo = false;
bool maxobjInfo = false;
bool objInView = false;
bool trianglesInView = false;
bool randommod = false;
bool pickupall = false;
bool renderRigidInstances = true;
bool renderPlaySurface = true;
bool renderGeometry = false;

bool invulBilbo = false;
bool stamina = false;
bool stones = false;
bool face1 = false;
bool face2 = false;
bool poison_chance = false;
bool sliding_wall = false;
bool finish_game = false;
bool finish_demo = false;
bool slide = false;
bool lock_animation = false;
bool chesttimer = false;
float chesttimer2 = false;
struct Point {
	float x = 0;
	float y = 0;
	float z = 0;
	float frame_animation = 0;
	LPDWORD ukazatel = 0x00;
	LPDWORD ukazatel_stamina = 0x00;
	LPDWORD ukazatel_animation = 0x00;
	LPDWORD ukazatel_chesttime = 0x00;
};
Point savedPoint;
float x, y, z;
float frame_animation;
LPDWORD ukazatel;
LPDWORD ukazatel_stamina;
LPDWORD ukazatel_animation;
LPDWORD ukazatel_chesttime;

bool debug = false;
int lang = 0; // 0 - RUS , 1 - ENG

Point currentBilboPos;

auto start = high_resolution_clock::now();
auto startChest = high_resolution_clock::now();

LPDWORD xPointer = 0x00;
float xPos = 0;
float yPos = 0;
float zPos = 0;
float timer_animation = 0;

float numberOfAttacks = 0;
float numberOfJumps = 0;
float distanceTraveled = 0;
float damageTakenFromPoison = 0;
float timeSpentHiding = 0;
float numberOfStonesThrown = 0;
float missedJumps = 0;
float numberOfPoleJumps = 0;
float damageTaken = 0;
float vigorHealthUsed = 0;
float swingsFromMineCart = 0;
float ridesInMinecart = 0;
float spSpentInVendor = 0;
float healthPotionsBought = 0;
float jumpsAlmostMissed = 0;
float distanceInMineCart = 0;
float enemiesKilled = 0;
float deathsDueToSting = 0;
float deathDueToStuff = 0;
float deathsDueToStones = 0;
float missedCourageFromKills = 0;
float totalSpMissed = 0;
float totalCouragePointsMissed = 0;
float totalChestsMissed = 0;
float totalQuestsMissed = 0;
float amountOfBlocks = 0;
float timer = 0;
float vremaeffectof = 10;

int HUD_HP = 98615574 - 22 + 6;

void gui::Render() noexcept
{
	//ImGui::SetNextWindowPos({ 0, 0 });

	ImGui::Begin(
		"The KingJoyer v2.0 by king174rus and Mr_Kliff",
		&isRunning,
		ImGuiWindowFlags_NoSavedSettings |
		ImGuiWindowFlags_NoCollapse
	);

	ImGui::Text("The Hobbit KingJoyer");
	ImGui::Text("");

	if (ImGui::Button(!lang ? "Change Language" : (const char*)u8"�������� ����")) lang = !lang;

	ImGui::Separator();
	ImGui::Text("");

	if (ImGui::Checkbox(lang ? "Developer mode" : (const char*)u8"����� ������������", &developerMode)) {
		functions::developerMode();
	}
	if (ImGui::Checkbox(lang ? "60 FPS" : (const char*)u8"60 ���", &fps60)) {
		functions::fps60();
	}
	if (ImGui::Checkbox(lang ? "Hotkeys" : (const char*)u8"������� �������", &enableKeybinds)) {

	}

	if (ImGui::CollapsingHeader(lang ? "Renders" : (const char*)u8"�������"))
	{
		ImGui::Indent();

		ImGui::Text(lang ? "Renders" : (const char*)u8"�������");
		ImGui::Separator();

		if (ImGui::BeginTable("split", 3))
		{
			ImGui::TableNextColumn(); if (ImGui::Checkbox(lang ? "Volumes" : (const char*)u8"������", &renderVolumes)) {
				functions::renderVolumes();
			}
			ImGui::TableNextColumn(); if (ImGui::Checkbox(lang ? "PolyCache" : (const char*)u8"��������", &polyCache)) {
				functions::polyCache();
			}
			ImGui::TableNextColumn(); if (ImGui::Checkbox(lang ? "Load Triggers" : (const char*)u8"�������� ��������", &renderLoadTriggers)) {
				functions::renderLoadTriggers();
			}
			ImGui::TableNextColumn(); if (ImGui::Checkbox(lang ? "Triggers" : (const char*)u8"��������", &renderTriggers)) {
				functions::renderTriggers();
			}
			ImGui::TableNextColumn(); if (ImGui::Checkbox(lang ? "Water" : (const char*)u8"����", &renderWater)) {
				functions::renderWater();
			}
			ImGui::TableNextColumn(); if (ImGui::Checkbox(lang ? "Web" : (const char*)u8"�������", &renderWeb)) {
				functions::renderWeb();
			}
			ImGui::TableNextColumn(); if (ImGui::Checkbox(lang ? "Ropes" : (const char*)u8"�������", &renderRopes)) {
				functions::renderRopes();
			}
			ImGui::TableNextColumn(); if (ImGui::Checkbox(lang ? "Leaves" : (const char*)u8"������", &renderLeaves)) {
				functions::renderLeaves();
			}
			ImGui::TableNextColumn(); if (ImGui::Checkbox(lang ? "Chests" : (const char*)u8"�������", &renderChests)) {
				functions::renderChests();
			}
			ImGui::TableNextColumn(); if (ImGui::Checkbox(lang ? "Levers" : (const char*)u8"������", &renderLevers)) {
				functions::renderLevers();
			}
			ImGui::TableNextColumn(); if (ImGui::Checkbox(lang ? "Bilbo" : (const char*)u8"������", &renderBilbo)) {
				functions::renderBilbo();
			}
			ImGui::TableNextColumn(); if (ImGui::Checkbox(lang ? "Lights" : (const char*)u8"����", &renderLights)) {
				functions::renderLights();
			}
			ImGui::TableNextColumn(); if (ImGui::Checkbox(lang ? "Effects" : (const char*)u8"�������", &renderEffects)) {
				functions::renderEffects();
			}
			ImGui::TableNextColumn(); if (ImGui::Checkbox(lang ? "Breakway" : (const char*)u8"�������� ����", &breakway)) {
				functions::breakway();
			}
			ImGui::TableNextColumn(); if (ImGui::Checkbox(lang ? "Falling boulders" : (const char*)u8"�������� ���������", &boulderRun)) {
				functions::boulderRun();
			}
			ImGui::TableNextColumn(); if (ImGui::Checkbox(lang ? "Skybox" : (const char*)u8"����", &renderSkybox)) {
				functions::renderSkybox();
			}
			ImGui::TableNextColumn(); if (ImGui::Checkbox(lang ? "Save Pedestal" : (const char*)u8"��������� ����������", &renderSavePedestal)) {
				functions::renderSavePedestal();
			}
			ImGui::TableNextColumn(); if (ImGui::Checkbox(lang ? "Push boxes" : (const char*)u8"����������� �������", &renderPushBoxes)) {
				functions::renderPushBoxes();
			}
			ImGui::TableNextColumn(); if (ImGui::Checkbox(lang ? "Rigid Instances" : (const char*)u8"�������", &renderRigidInstances)) {
				functions::renderRigidInstances();
			}
			ImGui::TableNextColumn(); if (ImGui::Checkbox(lang ? "Play surfaces" : (const char*)u8"��������", &renderPlaySurface)) {
				functions::renderPlaySurface();
			}
			ImGui::TableNextColumn(); if (ImGui::Checkbox(lang ? "Geometry" : (const char*)u8"���������", &renderGeometry)) {
				functions::renderGeometry();
			}
			ImGui::EndTable();
		}

		ImGui::Unindent();
	}

	if (ImGui::CollapsingHeader(lang ? "Cheats" : (const char*)u8"����"))
	{
		ImGui::Indent();

		ImGui::Text(lang ? "Teleportation" : (const char*)u8"������������");
		ImGui::Separator();

		if (ImGui::Button(lang ? "Set Teleportation Waypoint" : (const char*)u8"���������� ����� ������������")) {
			gui::SetTeleportPoint();
		}

		ImGui::SameLine();
		ImGui::Text("");
		ImGui::SameLine();

		if (ImGui::Button(lang ? "Teleport!" : (const char*)u8"�����������������!")) {
			gui::Teleport();
		}

		ImGui::Text("X: %g", savedPoint.x); ImGui::SameLine();
		ImGui::Text("Y: %g", savedPoint.y); ImGui::SameLine();
		ImGui::Text("Z: %g", savedPoint.z);

		ImGui::Text("");
		ImGui::Text(lang ? "Cheats" : (const char*)u8"����");
		ImGui::Separator();

		if (ImGui::Checkbox(lang ? "Full stamina" : (const char*)u8"����������� ������������", &stamina)) {
			savedPoint.ukazatel_stamina = ukazatel_hobbit((LPDWORD)0x0075BA3C);
			ukazatel_stamina = savedPoint.ukazatel_stamina; //������� ���������� �������
		}
		if (ImGui::Checkbox(lang ? "Full chest time" : (const char*)u8"����������� ������ �������", &chesttimer)) {

			change_4Byte_hobbit((LPDWORD)0x005299E9, 0x90909090, 0xFA5025D8);
			change_2Byte_hobbit((LPDWORD)0x005299ED, 0x9090, 0x006E); //��� ������ ���� 6 ������ ��������, ��-����� ��� 2 �������
		}
		if (ImGui::Checkbox(lang ? "Full stones" : (const char*)u8"����������� �����", &stones)) { //����������� �����
		}
		if (ImGui::Checkbox(lang ? "Invulnerability" : (const char*)u8"����������", &invulBilbo)) {
			change_1Byte_hobbit((LPVOID)0x0075FBF4, 0x01, 0x00); //������� ����������
		}

		if (ImGui::Button(lang ? "Upgrade staff" : (const char*)u8"�������� �����")) {
			for (int item = 28; item < 37; item++)
				plusA_float_hobbit((LPBYTE)0x0075BDB0 + item * 4, 1); //������� ������ ���� ��������� �� �����
		}
		if (ImGui::Button(lang ? "Upgrade 1 sting" : (const char*)u8"�������� ���")) {
			for (int item = 37; item < 43; item++)
				plusA_float_hobbit((LPBYTE)0x0075BDB0 + item * 4, 1); //������� ������ ���� ��������� �� ����
		}
		if (ImGui::Button(lang ? "Upgrade 1 stone" : (const char*)u8"�������� �����")) {
			for (int item = 43; item < 46; item++)
				plusA_float_hobbit((LPBYTE)0x0075BDB0 + item * 4, 1); //������� ������ ���� ��������� �� �����
		}

		if (ImGui::Button(lang ? "Add 1 stone" : (const char*)u8"������ 1 ������")) {
			plusA_float_hobbit((LPVOID)0x0075BDB4, 1); //������� �������� �� 1 ������
		}
		if (ImGui::Button(lang ? "Add 5 stones" : (const char*)u8"������ 5 �������")) {
			plusA_float_hobbit((LPVOID)0x0075BDB4, 5); //������� �������� �� 5 ������
		}
		if (ImGui::Button(lang ? "Add 1 extra HP" : (const char*)u8"1 ��� ��")) {
			plusA_float_hobbit((LPVOID)0x0075BDC4, 1); //������� �������� �� 1 ��� ��
		}
		if (ImGui::Button(lang ? "Add 10 extra HP" : (const char*)u8"10 ��� ��")) {
			plusA_float_hobbit((LPVOID)0x0075BDC4, 10); //������� �������� �� 10 ��� ��
		}
		if (ImGui::Button(lang ? "Add 1 Max HP" : (const char*)u8"1 ���� ��")) {
			plusA_float_hobbit((LPVOID)0x0075BE14, 1); //������� �������� �� 1 ���� ��
		}
		if (ImGui::Button(lang ? "Add 10 Max HP" : (const char*)u8"10 ���� ��")) {
			plusA_float_hobbit((LPVOID)0x0075BE14, 10); //������� �������� �� 10 ���� ��
		}

		ImGui::Text("");
		ImGui::Text(lang ? "Speed" : (const char*)u8"��������");
		ImGui::Separator();

		ImGui::Text(lang ? "Bilbos' speed" : (const char*)u8"�������� ������");
		static int speed = 300;
		ImGui::PushItemWidth(300);
		ImGui::InputInt("", &speed, 50);
		ImGui::PopItemWidth();

		if (ImGui::Button(lang ? "Apply speed" : (const char*)u8"��������� ��������")) {
			change_float_hobbit((LPVOID)0x0075B850, speed); //������� ��������� �������� ������
		}

		ImGui::Text("");
		ImGui::Text(lang ? "Jump" : (const char*)u8"������");
		ImGui::Separator();

		ImGui::Text(lang ? "Jump power (lower = better)" : (const char*)u8"���� ������ (������ = �����)");
		static int jumpPower = 3000;
		ImGui::PushItemWidth(300);
		ImGui::InputInt(" ", &jumpPower, 500);
		ImGui::PopItemWidth();

		if (ImGui::Button(lang ? "Apply power" : (const char*)u8"��������� ������")) {
			change_float_hobbit((LPVOID)0x0075B888, jumpPower);
		}
		ImGui::Text("");
		ImGui::Text(lang ? "Speed in jump" : (const char*)u8"�������� � ������");

		static int speedInJump = 350;
		ImGui::PushItemWidth(300);
		ImGui::InputInt("  ", &speedInJump, 100);
		ImGui::PopItemWidth();

		if (ImGui::Button(lang ? "Apply speed in jump" : (const char*)u8"��������� �������� � ������")) {
			change_float_hobbit((LPVOID)0x0075B868, speedInJump);
		}

		ImGui::Unindent();
	}

	if (ImGui::CollapsingHeader(lang ? "Camera" : (const char*)u8"������"))
	{
		ImGui::Indent();
		ImGui::Text(lang ? "Camera" : (const char*)u8"������");
		ImGui::Separator();

		if (ImGui::Button(lang ? "Decrease FOV" : (const char*)u8"��������� FOV")) {
			plusA_float_hobbit((LPVOID)0x00772BF0, -0.1); //������� ����������� ������ �� 0.1
		}
		if (ImGui::Button(lang ? "Increase FOV" : (const char*)u8"��������� FOV")) {
			plusA_float_hobbit((LPVOID)0x00772BF0, +0.1); //������� ��������� ������ �� 0.1
		}

		static float fovValue = 1.27;
		ImGui::Text(lang ? "Set FOV manually" : (const char*)u8"��������� ���� ������ �������");
		ImGui::PushItemWidth(300);
		ImGui::InputFloat(". ", &fovValue, 0.1);
		ImGui::PopItemWidth();

		if (ImGui::Button(lang ? "Apply manual FOV" : (const char*)u8"��������� ������ ���� ������")) {
			change_float_hobbit((LPVOID)0x00772BF0, fovValue);
		}

		static int cameraDistance = 100;
		ImGui::Text(lang ? "Camera Distance" : (const char*)u8"��������� ������");
		ImGui::PushItemWidth(300);
		ImGui::InputInt("   ", &cameraDistance, 50);
		ImGui::PopItemWidth();

		if (ImGui::Button(lang ? "Apply Distance" : (const char*)u8"��������� ����������")) {
			change_float_hobbit((LPVOID)0x00772A70, cameraDistance);
			change_float_hobbit((LPVOID)0x00772B38, cameraDistance);
		}

		static int maxCameraDistance = 300;
		ImGui::Text(lang ? "Max Camera Distance" : (const char*)u8"������������ ��������� ������");
		ImGui::PushItemWidth(300);
		ImGui::InputInt("    ", &maxCameraDistance, 50);
		ImGui::PopItemWidth();

		if (ImGui::Button(lang ? "Apply Max Distance" : (const char*)u8"��������� ����. ����������")) {
			change_float_hobbit((LPVOID)0x00772B3C, maxCameraDistance);
		}

		if (ImGui::Button(lang ? "Flip camera" : (const char*)u8"����������� ������")) {
			change_4Byte_hobbit((LPVOID)0x00772BF0, 0x3FA0D97C, 0x408CCCCD);
		}

		if (ImGui::Button(lang ? "First person" : (const char*)u8"������ ����")) {
			change_float_hobbit((LPVOID)0x00772A70, 1);
			change_float_hobbit((LPVOID)0x00772B38, 1);  //������ ����
			change_float_hobbit((LPVOID)0x00772B3C, 1);
			change_1Byte_hobbit((LPVOID)0x00777AA0, 0x00, 0x00);
		}
		if (ImGui::Button(lang ? "Second person" : (const char*)u8"������ ����")) {
			change_float_hobbit((LPVOID)0x00772A70, -300);
			change_float_hobbit((LPVOID)0x00772B38, -300);  //������ ����
			change_float_hobbit((LPVOID)0x00772B3C, -300);
			change_1Byte_hobbit((LPVOID)0x00777AA0, 0x01, 0x01);
		}
		if (ImGui::Button(lang ? "Third person" : (const char*)u8"������ ����")) {
			change_float_hobbit((LPVOID)0x00772A70, 100);
			change_float_hobbit((LPVOID)0x00772B38, 100);  //������ ����
			change_float_hobbit((LPVOID)0x00772B3C, 300);
			change_1Byte_hobbit((LPVOID)0x00777AA0, 0x01, 0x01);
		}
		ImGui::Unindent();
	}

	if (ImGui::CollapsingHeader(lang ? "Statistics" : (const char*)u8"����������"))
	{
		ImGui::Indent();

		ImGui::Text(lang ? "Statistics" : (const char*)u8"����������");
		ImGui::Separator();
		if (ImGui::Checkbox(lang ? "Bilbo Positon" : (const char*)u8"������� ������", &bilboPos)) {
			change_1Byte_hobbit((LPVOID)0x0075FBD4, 0x01, 0x00);
		}

		if (ImGui::Checkbox(lang ? "Cinema Debug" : (const char*)u8"���������� � ���������", &cutsceneInfo)) {
			change_1Byte_hobbit((LPVOID)0x0075FBF8, 0x01, 0x00);
		}

		if (ImGui::Checkbox(lang ? "Objects stats" : (const char*)u8"���������� �� ��������", &objInfo)) {
			change_1Byte_hobbit((LPVOID)0x0075FBC4, 0x01, 0x00);
		}

		if (ImGui::Checkbox(lang ? "Big Objects stats" : (const char*)u8"����� ���������� �� ��������", &maxobjInfo)) {
			change_1Byte_hobbit((LPVOID)0x00778054, 0x01, 0x00);
		}

		if (ImGui::Checkbox(lang ? "Objects in view" : (const char*)u8"������� � ���� ���������", &objInView)) {
			change_1Byte_hobbit((LPVOID)0x00778070, 0x01, 0x00);
		}

		if (ImGui::Checkbox(lang ? "Triangles in view" : (const char*)u8"������������ � ���� ���������", &trianglesInView)) {
			change_1Byte_hobbit((LPVOID)0x00778058, 0x01, 0x00);
		}

		auto tim = duration_cast<seconds>(high_resolution_clock::now() - start).count();

		if (tim > 2)
		{
			start = high_resolution_clock::now();

			numberOfAttacks = read_float_value((LPVOID)(0x0075C034));
			numberOfJumps = read_float_value((LPVOID)(0x0075C034 + 4));
			distanceTraveled = read_float_value((LPVOID)(0x0075C034 + 8));
			damageTakenFromPoison = read_float_value((LPVOID)(0x0075C034 + 12));
			timeSpentHiding = read_float_value((LPVOID)(0x0075C034 + 16));
			numberOfStonesThrown = read_float_value((LPVOID)(0x0075C034 + 20));
			missedJumps = read_float_value((LPVOID)(0x0075C034 + 24));
			numberOfPoleJumps = read_float_value((LPVOID)(0x0075C034 + 28));
			damageTaken = read_float_value((LPVOID)(0x0075C034 + 32));
			vigorHealthUsed = read_float_value((LPVOID)(0x0075C034 + 36));
			swingsFromMineCart = read_float_value((LPVOID)(0x0075C034 + 40));
			ridesInMinecart = read_float_value((LPVOID)(0x0075C034 + 44));
			spSpentInVendor = read_float_value((LPVOID)(0x0075C034 + 48));
			healthPotionsBought = read_float_value((LPVOID)(0x0075C034 + 52));
			jumpsAlmostMissed = read_float_value((LPVOID)(0x0075C034 + 56));
			distanceInMineCart = read_float_value((LPVOID)(0x0075C034 + 60));
			enemiesKilled = read_float_value((LPVOID)(0x0075C034 + 64));
			deathsDueToSting = read_float_value((LPVOID)(0x0075C034 + 68));
			deathDueToStuff = read_float_value((LPVOID)(0x0075C034 + 72));
			deathsDueToStones = read_float_value((LPVOID)(0x0075C034 + 76));
			missedCourageFromKills = read_float_value((LPVOID)(0x0075C034 + 80));
			totalSpMissed = read_float_value((LPVOID)(0x0075C034 + 84));
			totalCouragePointsMissed = read_float_value((LPVOID)(0x0075C034 + 88));
			totalChestsMissed = read_float_value((LPVOID)(0x0075C034 + 92));
			totalQuestsMissed = read_float_value((LPVOID)(0x0075C034 + 96));
			amountOfBlocks = read_float_value((LPVOID)(0x0075C034 + 100));

			xPointer = ukazatel_hobbit((LPVOID)0x0075BA3C);
			xPos = read_float_value((LPVOID)(xPointer + 497));
			yPos = read_float_value((LPVOID)(xPointer + 498));
			zPos = read_float_value((LPVOID)(xPointer + 499));
		}

		ImGui::Text("X: %g", xPos); ImGui::SameLine();
		ImGui::Text("Y: %g", yPos); ImGui::SameLine();
		ImGui::Text("Z: %g", zPos);

		ImGui::Text(lang ? "Number Of Attacks: %g" : (const char*)u8"���������� ������: %g", numberOfAttacks);
		ImGui::Text(lang ? "Number Of Jumps: %g" : (const char*)u8"���������� �������: %g", numberOfJumps);
		ImGui::Text(lang ? "Distance Traveled: %g" : (const char*)u8"���������� ����������: %g", distanceTraveled);
		ImGui::Text(lang ? "Missed Jumps: %g" : (const char*)u8"��������� ������: %g", missedJumps);
		ImGui::Text(lang ? "Damage Taken: %g" : (const char*)u8"���������� ����: %g", damageTaken);
		ImGui::Text(lang ? "Number Of Pole Jumps: %g" : (const char*)u8"���������� ������� � �������: %g", numberOfPoleJumps);
		ImGui::Text(lang ? "Jumps Almost Missed: %g" : (const char*)u8"���������� ����������� �������: %g", jumpsAlmostMissed);
		ImGui::Text(lang ? "Deaths Due to Sting: %g" : (const char*)u8"����� �����: %g", deathsDueToSting);
		ImGui::Text(lang ? "Deaths Due to Staff: %g" : (const char*)u8"����� �������: %g", deathDueToStuff);
		ImGui::Text(lang ? "Deaths Due to Stones: %g" : (const char*)u8"����� �������: %g", deathsDueToStones);
		ImGui::Text(lang ? "Damage Taken From Poison: %g" : (const char*)u8"���� �� ���: %g", damageTakenFromPoison);
		ImGui::Text(lang ? "Time Spent Hiding: %g" : (const char*)u8"����� �����������: %g", timeSpentHiding);
		ImGui::Text(lang ? "Number Of Stones Thrown: %g" : (const char*)u8"���������� ��������� ������: %g", numberOfStonesThrown);
		ImGui::Text(lang ? "Vigor Health Used: %g" : (const char*)u8"�������������� �������� �����: %g", vigorHealthUsed);
		ImGui::Text(lang ? "Swings from Mine Cart: %g" : (const char*)u8"���������� ������ � ���������: %g", swingsFromMineCart);
		ImGui::Text(lang ? "Rides In Mine Cart: %g" : (const char*)u8"���������� ������� � ���������: %g", ridesInMinecart);
		ImGui::Text(lang ? "SP Spent in Vendor: %g" : (const char*)u8"����� ����������: %g", spSpentInVendor);
		ImGui::Text(lang ? "Health Potions Purchased: %g" : (const char*)u8"����� �������: %g", healthPotionsBought);
		ImGui::Text(lang ? "Distance in Mine Cart: %g" : (const char*)u8"���������� �� ���������: %g", distanceInMineCart);
		ImGui::Text(lang ? "Enemies Killed: %g" : (const char*)u8"������ �����: %g", enemiesKilled);
		ImGui::Text(lang ? "Missed Courage from Kills: %g" : (const char*)u8"���������� ��������: %g", missedCourageFromKills);
		ImGui::Text(lang ? "Total SP Missed: %g" : (const char*)u8"��������� �����: %g", totalSpMissed);
		ImGui::Text(lang ? "Total Courage Missed: %g" : (const char*)u8"��������� ����������: %g", totalCouragePointsMissed);
		ImGui::Text(lang ? "Total Chests Missed: %g" : (const char*)u8"��������� ��������: %g", totalChestsMissed);
		ImGui::Text(lang ? "Total Quests Missed: %g" : (const char*)u8"��������� �������: %g", totalQuestsMissed);
		ImGui::Text(lang ? "Blocks: %g" : (const char*)u8"���������� ������: %g", amountOfBlocks);

		const char* Stats[] = { lang ? "Number Of Attacks" : (const char*)u8"���������� ������",
			lang ? "Number Of Jumps" : (const char*)u8"���������� �������",
		lang ? "Distance Traveled" : (const char*)u8"���������� ����������",
		lang ? "Damage Taken From Poison" : (const char*)u8"���� �� ���",
		lang ? "Time Spent Hiding" : (const char*)u8"����� �����������",
		lang ? "Number Of Stones Thrown" : (const char*)u8"���������� ��������� ������",
		lang ? "Missed Jumps" : (const char*)u8"��������� ������",
		lang ? "Number Of Pole Jumps" : (const char*)u8"���������� ������� � �������",
		lang ? "Damage Taken" : (const char*)u8"���������� ����",
		lang ? "Vigor Health Used" : (const char*)u8"�������������� �������� �����",
		lang ? "Swings from Mine Cart" : (const char*)u8"���������� ������ � ���������",
		lang ? "Rides In Mine Cart" : (const char*)u8"���������� ������� � ���������",
		lang ? "SP Spent in Vendor" : (const char*)u8"����� ����������",
		lang ? "Health Potions Purchased" : (const char*)u8"����� �������",
		lang ? "Jumps Almost Missed" : (const char*)u8"���������� ����������� �������",
		lang ? "Distance in Mine Cart" : (const char*)u8"���������� �� ���������",
		lang ? "Enemies Killed" : (const char*)u8"������ �����",
		lang ? "Deaths Due to Sting" : (const char*)u8"����� �����",
		lang ? "Deaths Due to Staff" : (const char*)u8"����� �������",
		lang ? "Deaths Due to Stones" : (const char*)u8"����� �������",
		lang ? "Missed Courage from Kills" : (const char*)u8"���������� ��������",
		lang ? "Total SP Missed" : (const char*)u8"��������� �����",
		lang ? "Total Courage Missed" : (const char*)u8"��������� ����������",
		lang ? "Total Chests Missed" : (const char*)u8"��������� ��������",
		lang ? "Total Quests Missed" : (const char*)u8"��������� �������",
		lang ? "Blocks" : (const char*)u8"���������� ������" };

		static int NumberStat = -1;
		ImGui::Text(lang ? "Select Statistics" : (const char*)u8"������� ����������");
		ImGui::Combo(" ", &NumberStat, Stats, IM_ARRAYSIZE(Stats));
		static int Stat = 0;
		ImGui::PushItemWidth(300);
		ImGui::InputInt("     ", &Stat);
		ImGui::PopItemWidth();
		if (ImGui::Button(lang ? "Change Statistics" : (const char*)u8"�������� ����������")) {
			change_float_hobbit((LPDWORD)0x0075C034 + NumberStat, Stat);
		}

		ImGui::Unindent();
	}

	if (ImGui::CollapsingHeader(lang ? "Quest Items" : (const char*)u8"��������� ��������"))
	{
		ImGui::Indent();
		const char* questItems[] = { lang ? "Troll key(OHUH)" : (const char*)u8"���� ������",
		lang ? "Witch King Crystal" : (const char*)u8"������ ������-�������",
		lang ? "Burberry plant" : (const char*)u8"��������",
		lang ? "Blue urn" : (const char*)u8"����� ����",
		lang ? "Red urn" : (const char*)u8"������� ����",
		lang ? "Yellow urn" : (const char*)u8"������ ����",
		lang ? "Unlit torch" : (const char*)u8"���������� �����",
		lang ? "Lit torch" : (const char*)u8"������� �����",
		lang ? "Bellows" : (const char*)u8"����",
		lang ? "Signet ring" : (const char*)u8"��������",
		lang ? "Can of oil" : (const char*)u8"�����",
		lang ? "Small iron gear" : (const char*)u8"�������� ���������",
		lang ? "Small silver gear" : (const char*)u8"���������� ���������",
		lang ? "Small golden gear" : (const char*)u8"������� ���������",
		lang ? "Small copper gear" : (const char*)u8"������ ���������",
		lang ? "Small metallic" : (const char*)u8"�������� ���������",
		lang ? "Iron gear" : (const char*)u8"�������� ����������",
		lang ? "Silver gear" : (const char*)u8"���������� ����������",
		lang ? "Golden gear" : (const char*)u8"������� ����������",
		lang ? "Copper gear" : (const char*)u8"������ ����������",
		lang ? "Metallic gear" : (const char*)u8"�������� ����������",
		lang ? "Large iron gear" : (const char*)u8"�������� ��������",
		lang ? "Large silver gear" : (const char*)u8"���������� ��������",
		lang ? "Large golden gear" : (const char*)u8"������� ��������",
		lang ? "Large copper gear" : (const char*)u8"������ ��������",
		lang ? "Large metallic gear" : (const char*)u8"�������� ��������",
		lang ? "Iron shank head" : (const char*)u8"�������� ���������",
		lang ? "Silver shank head" : (const char*)u8"���������� ���������",
		lang ? "Golden shank head" : (const char*)u8"������� ���������",
		lang ? "Copper shank head" : (const char*)u8"������ ���������",
		lang ? "Metallic shank head" : (const char*)u8"�������� ���������",
		lang ? "Iron shank arm" : (const char*)u8"�������� �����",
		lang ? "Silver shank arm" : (const char*)u8"���������� �����",
		lang ? "Golden shank arm" : (const char*)u8"������� �����",
		lang ? "Copper shank arm" : (const char*)u8"������ �����",
		lang ? "Metallic shank arm" : (const char*)u8"�������� �����",
		lang ? "Firewood" : (const char*)u8"�����",
		lang ? "Grit-lift key" : (const char*)u8"���� ����",
		lang ? "Dim-lift key" : (const char*)u8"���� ���",
		lang ? "Mugg-lift key" : (const char*)u8"���� ����",
		lang ? "Jail Exit Key" : (const char*)u8"���� �� ������",
		lang ? "Final Bridge Key" : (const char*)u8"���� �� ���������� �����",
		lang ? "Gandola gear 1" : (const char*)u8"���������� ������� �1",
		lang ? "Gandola gear 2" : (const char*)u8"���������� ������� �2",
		lang ? "Wart-lift lever" : (const char*)u8"����� ����",
		lang ? "Wart-stone" : (const char*)u8"������ ����",
		lang ? "Thror`s golden cup" : (const char*)u8"������� ���� �����",
		lang ? "Necklace of Girion" : (const char*)u8"�������� �������",
		lang ? "Groin`s ruby" : (const char*)u8"����� ������",
		lang ? "King Bladorthin`s spears" : (const char*)u8"����� ������ �������",
		lang ? "Golden serving dish" : (const char*)u8"������� �����",
		lang ? "Tea-cakes" : (const char*)u8"�����",
		lang ? "Tea-cakes ingredients" : (const char*)u8"����������� ��� ������",
		lang ? "Shed key" : (const char*)u8"���� �� �����",
		lang ? "Apple" : (const char*)u8"������",
		lang ? "Hammer" : (const char*)u8"�������",
		lang ? "Nails" : (const char*)u8"������",
		lang ? "Walking stick" : (const char*)u8"�����",
		lang ? "Egg" : (const char*)u8"����",
		lang ? "Berries" : (const char*)u8"�����",
		lang ? "Sack of Wheat" : (const char*)u8"����� �������",
		lang ? "Sugar" : (const char*)u8"�����",
		lang ? "Spice" : (const char*)u8"������",
		lang ? "Sausage" : (const char*)u8"��������",
		lang ? "Wheat" : (const char*)u8"�������",
		lang ? "Quilt" : (const char*)u8"������",
		lang ? "Quilting needle" : (const char*)u8"������",
		lang ? "Elvish opening crystal 1" : (const char*)u8"1 ����-��������",
		lang ? "Elvish opening crystal 2" : (const char*)u8"2 ����-��������",
		lang ? "Elvish opening crystal 3" : (const char*)u8"3 ����-��������",
		lang ? "Elvish opening crystal 4" : (const char*)u8"4 ����-��������",
		lang ? "Elvish healing potion" : (const char*)u8"���������� ����� ���������",
		lang ? "Deep cellar key 1" : (const char*)u8"1 ���� �� ����������",
		lang ? "Deep cellar key 2" : (const char*)u8"2 ���� �� ����������",
		lang ? "Deep cellar key 3" : (const char*)u8"3 ���� �� ����������",
		lang ? "Deep cellar key 4" : (const char*)u8"4 ���� �� ����������",
		lang ? "Cavern crystal" : (const char*)u8"�������� ��������",
		lang ? "Wilowweed" : (const char*)u8"���-�����",
		lang ? "Moonleaf" : (const char*)u8"���������",
		lang ? "Spidersbane" : (const char*)u8"���������",
		lang ? "Web potion" : (const char*)u8"��������� �����",
		lang ? "Gear belt" : (const char*)u8"��������� ������",
		lang ? "Treasury Chain" : (const char*)u8"���� �� ������������",
		lang ? "Treasury key mold" : (const char*)u8"����� ��� �����",
		lang ? "Throne key mold 1" : (const char*)u8"1 ����� ��� �����",
		lang ? "Throne key mold 2" : (const char*)u8"2 ����� ��� �����",
		lang ? "Treasury key" : (const char*)u8"���� �� ������������",
		lang ? "Throne key 1" : (const char*)u8"1 ���� �� �������� ����",
		lang ? "Throne key 2" : (const char*)u8"2 ���� �� �������� ����",
		lang ? "Arkenstone" : (const char*)u8"���������",
		lang ? "City warehouse key" : (const char*)u8"���� �� ���������� ������",
		lang ? "Black arrow" : (const char*)u8"������ ������",
		lang ? "Malloc`s golden dagger" : (const char*)u8"������� ������ �������",
		lang ? "Black wine bottle" : (const char*)u8"������ �������",
		lang ? "Blue wine bottle" : (const char*)u8"����� �������",
		lang ? "Purple wine bottle" : (const char*)u8"���������� �������",
		lang ? "Red wine bottle" : (const char*)u8"������� �������",
		lang ? "Yellow wine bottle" : (const char*)u8"������ �������",
		lang ? "Gandalf`s Message" : (const char*)u8"�������� ���������",
		lang ? "Healing Draught" : (const char*)u8"���������",
		lang ? "Troll key(TH)" : (const char*)u8"���� �������",
		lang ? "Ladder switch lever" : (const char*)u8"�������� ��� ��������",
		lang ? "Rennar`s key" : (const char*)u8"���� �������" };


		ImGui::Text(lang ? "Quest Items" : (const char*)u8"��������� ��������");
		ImGui::Separator();

		static int questItem = -1;
		ImGui::Combo("   ", &questItem, questItems, IM_ARRAYSIZE(questItems));

		if (ImGui::Button(lang ? "Give quest item" : (const char*)u8"������ ��������� �������")) {
			plusA_float_hobbit((LPBYTE)0x0075BE98 + questItem * 4, 1); //������� ������ ���������� ��������
		}
		if (ImGui::Button(lang ? "Delete quest item" : (const char*)u8"������� ��������� �������")) {
			change_2Byte_hobbit((LPBYTE)0x0075BE9A + questItem * 4, 0x00, 0x00); //������� ������ ���������� ��������
		}
		ImGui::Unindent();
	}

	if (ImGui::CollapsingHeader(lang ? "Items" : (const char*)u8"��������"))
	{
		ImGui::Indent();
		const char* items[] = { lang ? "Coin" : (const char*)u8"������",
			lang ? "Stones" : (const char*)u8"������",
			(const char*)u8"Ihavehadstones",
			lang ? "Health" : (const char*)u8"��������",
			(const char*)u8"GreaterHealth",
			lang ? "Vigor Health" : (const char*)u8"������������",
			(const char*)u8"CPTOTAL",
			(const char*)u8"LevelingCP",
			lang ? "Courage" : (const char*)u8"����� ��������",
			lang ? "Courage1" : (const char*)u8"������� ��������",
			lang ? "Courage5" : (const char*)u8"������� ��������",
			lang ? "Courage10" : (const char*)u8"�������� ��������",
			lang ? "Courage25" : (const char*)u8"���������� ��������",
			lang ? "Courage50" : (const char*)u8"����� ��������",
			(const char*)u8"Coinbag",
			(const char*)u8"Coinbag5",
			(const char*)u8"Coinbag10",
			(const char*)u8"Coinbag25",
			(const char*)u8"Coinbag50",
			(const char*)u8"Coinbag100",
			lang ? "Rock Bag" : (const char*)u8"����� ��� ������",
			lang ? "Med Bag" : (const char*)u8"����� ��� �����",
			lang ? "Skeleton key" : (const char*)u8"�������",
			(const char*)u8"CLevelCP",
			(const char*)u8"ChestCount",
			(const char*)u8"BilboLevel",
			(const char*)u8"BilbosPoisoned",
			(const char*)u8"BilboPoisonTimer",
			(const char*)u8"Bilbo_Staff_Swing",
			(const char*)u8"Bilbo_Staff_Swing2",
			(const char*)u8"Bilbo_Staff_Swing3",
			(const char*)u8"Bilbo_Staff_Jump",
			(const char*)u8"Bilbo_Staff_Jump2",
			(const char*)u8"Bilbo_Staff_Jump3",
			(const char*)u8"Bilbo_Staff_AE_Jump",
			(const char*)u8"Bilbo_Staff_AE_Jump2",
			(const char*)u8"Bilbo_Staff_AE_Jump3",
			(const char*)u8"Bilbo_Sting_Swing",
			(const char*)u8"Bilbo_Sting_Swing2",
			(const char*)u8"Bilbo_Sting_Swing3",
			(const char*)u8"Bilbo_Sting_Jump",
			(const char*)u8"Bilbo_Sting_Jump2",
			(const char*)u8"Bilbo_Sting_Jump3",
			(const char*)u8"Bilbo_Stone_Throw",
			(const char*)u8"Bilbo_Stone_Throw2",
			(const char*)u8"Bilbo_Stone_Throw3",
			lang ? "Level Potion" : (const char*)u8"����� ������",
			lang ? "Health Potion" : (const char*)u8"�������� �����",
			lang ? "Antidote" : (const char*)u8"�����������",
			lang ? "Water of Vigor" : (const char*)u8"����� ����",
			lang ? "Sword Sting" : (const char*)u8"����",
			lang ? "Ring" : (const char*)u8"������",
			lang ? "Staff" : (const char*)u8"�����",
			lang ? "Explosive Stone" : (const char*)u8"�������� �����",
			lang ? "Fire Stone" : (const char*)u8"�������� �����",
			lang ? "Freeze Stone" : (const char*)u8"������������ �����",
			lang ? "Poison Stone" : (const char*)u8"�������� �����",
			lang ? "Magic Stone" : (const char*)u8"���������� �����" };
		static int item = -1;

		ImGui::Text(lang ? "Items" : (const char*)u8"��������");
		ImGui::Separator();

		ImGui::Combo("     ", &item, items, IM_ARRAYSIZE(items));

		if (ImGui::Button(lang ? "Give item" : (const char*)u8"������ �������")) {
			plusA_float_hobbit((LPBYTE)0x0075BDB0 + item * 4, 1); //������� ������ ��������
		}
		if (ImGui::Button(lang ? "Remove item" : (const char*)u8"������� �������")) {
			change_2Byte_hobbit((LPBYTE)0x0075BDB2 + item * 4, 0x00, 0x00); //������� �������� ��������
		}
		if (ImGui::Button(lang ? "Show item" : (const char*)u8"�������� �������")) {
			change_1Byte_hobbit((LPBYTE)0x007212BC + item * 4, 0x01, 0x01); //������� ������ ��������
		}
		if (ImGui::Button(lang ? "Hide item" : (const char*)u8"�������� �������")) {
			change_2Byte_hobbit((LPBYTE)0x007212BC + item * 4, 0x00, 0x00); //������� �������� ��������
		}
		ImGui::Unindent();
	}
	if (ImGui::CollapsingHeader(lang ? "Special options" : (const char*)u8"����������� �����"))
	{
		ImGui::Indent();
		if (ImGui::Checkbox(lang ? "Disable the possibility of poisoning" : (const char*)u8"��������� ����������� ����������", &poison_chance)) {
			change_1Byte_hobbit((LPVOID)0x0042132C, 0x00, 0x01); //������� ����������� ���������� � ������
		}
		if (ImGui::Checkbox(lang ? "Disable wall sliding" : (const char*)u8"��������� ���������� �� �����", &sliding_wall)) {
			change_1Byte_hobbit((LPVOID)0x0044342F, 0xEB, 0x74); //������� ���������� ���������� �� ����� (���� ������� � ��������, �� ���������� �� ����� ���������)
		}
		if (ImGui::Checkbox(lang ? "Slide on" : (const char*)u8"�������� �����", &slide)) {
			change_1Byte_hobbit((LPVOID)0x0043CD52, 0x08, 0x04); //������� ��������� ���� ����� ��������� ������
		}
		if (ImGui::Checkbox(lang ? "Lock animation" : (const char*)u8"�������� ��������", &lock_animation)) {
			savedPoint.ukazatel_animation = ukazatel_hobbit((LPDWORD)0x0075BA3C);
			ukazatel_animation = savedPoint.ukazatel_animation; //������� ���������� �������
			savedPoint.frame_animation = save_float_hobbit(ukazatel_animation + 0x530);
		}
		if (ImGui::Checkbox(lang ? "Finish the game after completing a level" : (const char*)u8"��������� ���� ����� ��������� ������", &finish_game)) {
			change_1Byte_hobbit((LPVOID)0x0052ACDF, 0x75, 0x74); //������� ��������� ���� ����� ��������� ������
		}
		if (ImGui::Checkbox(lang ? "Finish the demo after completing a level" : (const char*)u8"��������� ���� ����� ��������� ������", &finish_demo)) {
			change_1Byte_hobbit((LPVOID)0x0052ACC2, 0x75, 0x74); //������� ��������� ���� ����� ��������� ������
		}
		ImGui::Text(lang ? "Change HUD HP (max 22)" : (const char*)u8"��������� HUD �� (���� 22)");
		if (ImGui::Button("<")) {
			HUD_HP = read_int_value((LPBYTE)0x004F5BB8);
			if (HUD_HP == 98615552) {
				change_1Byte_hobbit((LPBYTE)0x004F5BB8, 0x16, 0x00);
			}
			else plusA_int_hobbit((LPBYTE)0x004F5BB8, -1); //������� ��������� ���� ��
		}
		ImGui::SameLine();
		if (ImGui::Button(">")) {
			HUD_HP = read_int_value((LPBYTE)0x004F5BB8);
			if (HUD_HP == 98615574) {
				change_1Byte_hobbit((LPBYTE)0x004F5BB8, 0x00, 0x00);
			}
			else plusA_int_hobbit((LPBYTE)0x004F5BB8, 1); //������� ��������� ���� ��
		}
		HUD_HP = read_int_value((LPBYTE)0x004F5BB8);
		ImGui::Text((const char*)to_string(HUD_HP - 98615552).c_str());
		ImGui::Unindent();

	}
	if (ImGui::CollapsingHeader(lang ? "Complicated options" : (const char*)u8"������� �����"))
	{
		ImGui::Indent();
		ImGui::Text(lang ? "Effect change time" : (const char*)u8"����� ����� ��������");
		ImGui::PushItemWidth(300);
		ImGui::InputFloat(" .", &vremaeffectof, 1);
		ImGui::PopItemWidth();
		if (vremaeffectof < 0.0f) {
			vremaeffectof = 0.0f;
		}
		if (ImGui::Checkbox(lang ? "Random mod" : (const char*)u8"������ ���", &randommod)) {
		}
		if (ImGui::Checkbox(lang ? "PickupAll mod" : (const char*)u8"��� ������� ���", &pickupall)) {
		}
		ImGui::Unindent();
	}
	if (ImGui::CollapsingHeader(lang ? "Skinchanger" : (const char*)u8"������������"))
	{
		ImGui::Text(lang ? "Restart the level/Load save\nafter skin selection" :
			(const char*)u8"������������� ������� ��� ��������� ����������\n����� ��������� �����");
		ImGui::Text("");

		displaySkinButtons(lang);
	}

	if (randommod == true) {
		RandomMod(vremaeffectof);
	}
	if (pickupall == true) {
		PickupAll();
	}
	if (stamina == true)
		change_float_hobbit(ukazatel_stamina + 641, 10);


	if (lock_animation == true)
	{
		if (timer_animation >= 0.1) {
			change_float_hobbit(ukazatel_animation + 332, savedPoint.frame_animation);
			timer_animation = 0.0;
		}
		else timer_animation += ImGui::GetIO().DeltaTime;
	}
	if (stones == true)
		change_float_hobbit((LPVOID)0x0075BDB4, 10);

	ImGui::Text("");
	ImGui::Text("");
	ImGui::Text("");
	ImGui::Text("");
	ImGui::Text("");
	ImGui::Text("");
	//change_float_hobbit((LPVOID)0x0F96D9D0, save_float_hobbit((LPVOID)0x0F9685E8));
	//change_float_hobbit((LPVOID)0x0F96D9D8, save_float_hobbit((LPVOID)0x0F9685F4));

	ImGui::Text(lang ? "Our links" : (const char*)u8"���� ������");
	ImGui::Separator();

	if (ImGui::Button("king174rus")) {
		ShellExecute(NULL, L"open", L"https://www.youtube.com/c/@king174rus", 0, 0, SW_SHOWNORMAL);
	}
	ImGui::SameLine(); ImGui::Text(" "); ImGui::SameLine();
	if (ImGui::Button("Mr_Kliff")) {
		ShellExecute(NULL, L"open", L"https://youtube.com/c/@YKliffa", 0, 0, SW_SHOWNORMAL);
	}
	ImGui::SameLine(); ImGui::Text(" "); ImGui::SameLine();
	if (ImGui::Button(lang ? "Hobbit Technical Discord" : (const char*)u8"����������� ����� ������� � ��������")) {
		ShellExecute(NULL, L"open", L"https://discord.gg/hvzB3maxQ3", 0, 0, SW_SHOWNORMAL);
	}

	ImGui::End();
}

//complicated functions

void gui::SetTeleportPoint() noexcept
{
	savedPoint.ukazatel = ukazatel_hobbit((LPVOID)0x0075BA3C);
	ukazatel = savedPoint.ukazatel;
	savedPoint.x = save_float_hobbit(ukazatel + 5);
	savedPoint.y = save_float_hobbit(ukazatel + 6);
	savedPoint.z = save_float_hobbit(ukazatel + 7);//������� ��������� ����� ������������
}

void gui::Teleport() noexcept
{
	x = savedPoint.x;
	y = savedPoint.y;
	z = savedPoint.z;
	ukazatel = savedPoint.ukazatel;
	if (x) {
		change_float_hobbit(ukazatel + 5, x);
		change_float_hobbit(ukazatel + 281, x);
		change_float_hobbit(ukazatel + 6, y);
		change_float_hobbit(ukazatel + 282, y);
		change_float_hobbit(ukazatel + 7, z);
		change_float_hobbit(ukazatel + 283, z);
	}
}