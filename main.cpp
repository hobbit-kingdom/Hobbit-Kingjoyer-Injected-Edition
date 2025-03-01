#include "includes.h"


typedef long(__stdcall* EndScene)(LPDIRECT3DDEVICE9);
static EndScene oEndScene = NULL;
static HWND window = NULL;

WNDPROC oWndProc;

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

void InitImGui(LPDIRECT3DDEVICE9 pDevice) {
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Arial.ttf", 18, NULL, io.Fonts->GetGlyphRangesCyrillic());
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX9_Init(pDevice);
}

bool init = false;
bool openMenu = false;

std::unordered_map<std::string, int> hotkeys;

int mapKey(const std::string& keyName) {
	static std::unordered_map<std::string, int> keyMap = {
	{"A", 'A'}, {"B", 'B'}, {"C", 'C'}, // Alphabet keys
	{"D", 'D'}, {"E", 'E'}, {"F", 'F'}, {"G", 'G'},
	{"H", 'H'}, {"I", 'I'}, {"J", 'J'}, {"K", 'K'},
	{"L", 'L'}, {"M", 'M'}, {"N", 'N'}, {"O", 'O'},
	{"P", 'P'}, {"Q", 'Q'}, {"R", 'R'}, {"S", 'S'},
	{"T", 'T'}, {"U", 'U'}, {"V", 'V'}, {"W", 'W'},
	{"X", 'X'}, {"Y", 'Y'}, {"Z", 'Z'},
	{"0", '0'}, {"1", '1'}, {"2", '2'}, {"3", '3'}, // Number keys
	{"4", '4'}, {"5", '5'}, {"6", '6'}, {"7", '7'},
	{"8", '8'}, {"9", '9'},
	{"F1", VK_F1}, {"F2", VK_F2}, {"F3", VK_F3}, // Function keys
	{"F4", VK_F4}, {"F5", VK_F5}, {"F6", VK_F6},
	{"F7", VK_F7}, {"F8", VK_F8}, {"F9", VK_F9},
	{"F10", VK_F10}, {"F11", VK_F11}, {"F12", VK_F12},
	{"ESCAPE", VK_ESCAPE}, {"ENTER", VK_RETURN}, {"SPACE", VK_SPACE},
	{"SHIFT", VK_SHIFT}, {"CTRL", VK_CONTROL}, {"ALT", VK_MENU},
	{"TAB", VK_TAB}, {"+", VK_OEM_PLUS}, {"-", VK_OEM_MINUS},
	{"NUMPAD0", VK_NUMPAD0}, {"NUMPAD1", VK_NUMPAD1}, {"NUMPAD2", VK_NUMPAD2},
	{"NUMPAD3", VK_NUMPAD3}, {"NUMPAD4", VK_NUMPAD4}, {"NUMPAD5", VK_NUMPAD5},
	{"NUMPAD6", VK_NUMPAD6}, {"NUMPAD7", VK_NUMPAD7}, {"NUMPAD8", VK_NUMPAD8},
	{"NUMPAD9", VK_NUMPAD9}, {"DECIMAL", VK_DECIMAL}, {"ADD", VK_ADD},
	{"SUBTRACT", VK_SUBTRACT}, {"MULTIPLY", VK_MULTIPLY}, {"DIVIDE", VK_DIVIDE},
	{"OPEN_BRACKET", VK_OEM_4}, {"CLOSE_BRACKET", VK_OEM_6}, {"BACKSLASH", VK_OEM_5},
	{"FORWARD_SLASH", VK_OEM_2}, {"PERIOD", VK_OEM_PERIOD}, {"COMMA", VK_OEM_COMMA},
	{"APOSTROPHE", VK_OEM_7} // Added apostrophe key
	};


	auto it = keyMap.find(keyName);
	if (it != keyMap.end()) {
		return it->second; // Return the virtual key code
	}

	return -1; // Return -1 for unknown keys
}


void loadHotkeysFromConfig() {
	INIReader reader("keybinds.ini");

	if (reader.ParseError() != 0) {
		std::cerr << "Can't load keybinds.ini" << std::endl;
		return;
	}

	hotkeys["developerMode"] = mapKey(reader.Get("Hotkeys", "developerMode", "F8"));
	hotkeys["fps60"] = mapKey(reader.Get("Hotkeys", "fps60", "9"));
	hotkeys["renderVolumes"] = mapKey(reader.Get("Hotkeys", "renderVolumes", "NUMPAD4"));
	hotkeys["renderLoadTriggers"] = mapKey(reader.Get("Hotkeys", "renderLoadTriggers", "NUMPAD4"));
	hotkeys["renderTriggers"] = mapKey(reader.Get("Hotkeys", "renderTriggers", "NUMPAD4"));
	hotkeys["renderWater"] = mapKey(reader.Get("Hotkeys", "renderWater", ""));
	hotkeys["renderWeb"] = mapKey(reader.Get("Hotkeys", "renderWeb", ""));
	hotkeys["renderRopes"] = mapKey(reader.Get("Hotkeys", "renderRopes", ""));
	hotkeys["renderLeaves"] = mapKey(reader.Get("Hotkeys", "renderLeaves", ""));
	hotkeys["renderChests"] = mapKey(reader.Get("Hotkeys", "renderChests", ""));
	hotkeys["renderLevers"] = mapKey(reader.Get("Hotkeys", "renderLevers", ""));
	hotkeys["renderBilbo"] = mapKey(reader.Get("Hotkeys", "renderBilbo", "NUMPAD1"));
	hotkeys["renderLights"] = mapKey(reader.Get("Hotkeys", "renderLights", "NUMPAD6"));
	hotkeys["renderEffects"] = mapKey(reader.Get("Hotkeys", "renderEffects", ""));
	hotkeys["renderSkybox"] = mapKey(reader.Get("Hotkeys", "renderSkybox", "NUMPAD3"));
	hotkeys["renderSavePedestal"] = mapKey(reader.Get("Hotkeys", "renderSavePedestal", ""));
	hotkeys["renderPushBoxes"] = mapKey(reader.Get("Hotkeys", "renderPushBoxes", ""));
	hotkeys["breakway"] = mapKey(reader.Get("Hotkeys", "breakway", ""));
	hotkeys["boulderRun"] = mapKey(reader.Get("Hotkeys", "boulderRun", ""));
	hotkeys["polyCache"] = mapKey(reader.Get("Hotkeys", "polyCache", "NUMPAD7"));
	hotkeys["bilboPos"] = mapKey(reader.Get("Hotkeys", "bilboPos", "APOSTROPHE"));
	hotkeys["cutsceneInfo"] = mapKey(reader.Get("Hotkeys", "cutsceneInfo", ""));
	hotkeys["objInfo"] = mapKey(reader.Get("Hotkeys", "objInfo", "CLOSE_BRACKET"));
	hotkeys["maxobjInfo"] = mapKey(reader.Get("Hotkeys", "maxobjInfo", "OPEN_BRACKET"));
	hotkeys["objInView"] = mapKey(reader.Get("Hotkeys", "objInView", "COMMA"));
	hotkeys["trianglesInView"] = mapKey(reader.Get("Hotkeys", "trianglesInView", ""));
	hotkeys["randommod"] = mapKey(reader.Get("Hotkeys", "randommod", ""));
	hotkeys["pickupall"] = mapKey(reader.Get("Hotkeys", "pickupall", ""));
	hotkeys["renderRigidInstances"] = mapKey(reader.Get("Hotkeys", "renderRigidInstances", "NUMPAD9"));
	hotkeys["renderPlaySurface"] = mapKey(reader.Get("Hotkeys", "renderPlaySurface", "NUMPAD5"));
	hotkeys["renderGeometry"] = mapKey(reader.Get("Hotkeys", "renderGeometry", "PERIOD"));
	hotkeys["renderHud"] = mapKey(reader.Get("Hotkeys", "renderHud", "H"));
	hotkeys["invulBilbo"] = mapKey(reader.Get("Hotkeys", "invulBilbo", "V"));
	hotkeys["stamina"] = mapKey(reader.Get("Hotkeys", "stamina", ""));
	hotkeys["stones"] = mapKey(reader.Get("Hotkeys", "stones", ""));
	hotkeys["face1"] = mapKey(reader.Get("Hotkeys", "face1", ""));
	hotkeys["face2"] = mapKey(reader.Get("Hotkeys", "face2", ""));
	hotkeys["poison_chance"] = mapKey(reader.Get("Hotkeys", "poison_chance", ""));
	hotkeys["sliding_wall"] = mapKey(reader.Get("Hotkeys", "sliding_wall", ""));
	hotkeys["finish_game"] = mapKey(reader.Get("Hotkeys", "finish_game", ""));
	hotkeys["finish_demo"] = mapKey(reader.Get("Hotkeys", "finish_demo", ""));
	hotkeys["slide"] = mapKey(reader.Get("Hotkeys", "slide", "J"));
	hotkeys["lock_animation"] = mapKey(reader.Get("Hotkeys", "lock_animation", "R"));
	hotkeys["chesttimer"] = mapKey(reader.Get("Hotkeys", "chesttimer", ""));

	//FOV
	hotkeys["increaseFOV"] = mapKey(reader.Get("Hotkeys", "increaseFOV", "L"));
	hotkeys["decreaseFOV"] = mapKey(reader.Get("Hotkeys", "decreaseFOV", "K"));

	//teleportation
	hotkeys["setTeleportPoint"] = mapKey(reader.Get("Hotkeys", "setTeleportPoint", "Y"));
	hotkeys["teleport"] = mapKey(reader.Get("Hotkeys", "teleport", "T"));

}

void keybindings()
{
	if (GetAsyncKeyState(hotkeys["developerMode"]) & 1) functions::developerMode();
	if (GetAsyncKeyState(hotkeys["fps60"]) & 1) functions::fps60();

	if (GetAsyncKeyState(hotkeys["renderVolumes"]) & 1) functions::renderVolumes();
	if (GetAsyncKeyState(hotkeys["polyCache"]) & 1) functions::polyCache();
	if (GetAsyncKeyState(hotkeys["renderLoadTriggers"]) & 1) functions::renderLoadTriggers();
	if (GetAsyncKeyState(hotkeys["renderTriggers"]) & 1) functions::renderTriggers();
	if (GetAsyncKeyState(hotkeys["renderWater"]) & 1) functions::renderWater();
	if (GetAsyncKeyState(hotkeys["renderWeb"]) & 1) functions::renderWeb();
	if (GetAsyncKeyState(hotkeys["renderRopes"]) & 1) functions::renderRopes();
	if (GetAsyncKeyState(hotkeys["renderLeaves"]) & 1) functions::renderLeaves();
	if (GetAsyncKeyState(hotkeys["renderChests"]) & 1) functions::renderChests();
	if (GetAsyncKeyState(hotkeys["renderLevers"]) & 1) functions::renderLevers();
	if (GetAsyncKeyState(hotkeys["renderBilbo"]) & 1) functions::renderBilbo();
	if (GetAsyncKeyState(hotkeys["renderLights"]) & 1) functions::renderLights();
	if (GetAsyncKeyState(hotkeys["renderEffects"]) & 1) functions::renderEffects();
	if (GetAsyncKeyState(hotkeys["breakway"]) & 1) functions::breakway();
	if (GetAsyncKeyState(hotkeys["boulderRun"]) & 1) functions::boulderRun();
	if (GetAsyncKeyState(hotkeys["renderSkybox"]) & 1) functions::renderSkybox();
	if (GetAsyncKeyState(hotkeys["renderSavePedestal"]) & 1) functions::renderSavePedestal();
	if (GetAsyncKeyState(hotkeys["renderPushBoxes"]) & 1) functions::renderPushBoxes();
	if (GetAsyncKeyState(hotkeys["renderRigidInstances"]) & 1) functions::renderRigidInstances();
	if (GetAsyncKeyState(hotkeys["renderPlaySurface"]) & 1) functions::renderPlaySurface();

	if (GetAsyncKeyState(hotkeys["renderGeometry"]) & 1) functions::renderGeometry();
	if (GetAsyncKeyState(hotkeys["renderHud"]) & 1) functions::renderHud();

	if (GetAsyncKeyState(hotkeys["increaseFOV"]) & 1) functions::increaseFOV();
	if (GetAsyncKeyState(hotkeys["decreaseFOV"]) & 1) functions::decreaseFOV();

	if (GetAsyncKeyState(hotkeys["setTeleportPoint"]) & 1) gui::SetTeleportPoint();
	if (GetAsyncKeyState(hotkeys["teleport"]) & 1) gui::Teleport();

}

void SendKeyPress(HWND hwnd, WPARAM key) {
	// Send a WM_KEYDOWN message
	PostMessage(hwnd, WM_KEYDOWN, key, 0);

	// Send a WM_KEYUP message
	PostMessage(hwnd, WM_KEYUP, key, 0);
}

// Declare the detour function
long __stdcall hkEndScene(LPDIRECT3DDEVICE9 pDevice)
{
	if (!init)
	{
		InitImGui(pDevice);
		loadHotkeysFromConfig();
		init = true;
	}

	if (GetAsyncKeyState(VK_TAB) & 1) openMenu = !openMenu;

	if (gui::enableKeybinds) keybindings();

	if (openMenu)
	{

		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		gui::Render();

		ImGui::EndFrame();
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
	}

	return oEndScene(pDevice);
}

LRESULT _stdcall WndProc(const HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (true && ImGui_ImplWin32_WndProcHandler(hwnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(oWndProc, hwnd, uMsg, wParam, lParam);
}

BOOL CALLBACK EnumWindowsCallBack(HWND handle, LPARAM lParam)
{
	DWORD procID;
	GetWindowThreadProcessId(handle, &procID);

	if (GetCurrentProcessId() != procID)
		return TRUE;

	window = handle;
	return false;
}

HWND GetProcessWindow()
{
	window = NULL;
	EnumWindows(EnumWindowsCallBack, NULL);
	return window;
}

int mainThread()
{
	if (kiero::init(kiero::RenderType::D3D9) == kiero::Status::Success)
	{
		kiero::bind(42, (void**)&oEndScene, hkEndScene);
		window = GetProcessWindow();
		oWndProc = (WNDPROC)SetWindowLongPtr(window, GWL_WNDPROC, (LONG_PTR)WndProc);
	}

	return 0;
}

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD fdwReason, LPVOID)
{
	DisableThreadLibraryCalls(hInstance);

	if (fdwReason == DLL_PROCESS_ATTACH) {
		CloseHandle(CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)mainThread, NULL, 0, NULL));
	}

	return TRUE;
}