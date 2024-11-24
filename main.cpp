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

	hotkeys["developerMode"] = mapKey(reader.Get("Hotkeys", "developerMode", "K"));
	hotkeys["fps60"] = mapKey(reader.Get("Hotkeys", "fps60", "F1"));
}

void keybindings()
{
	if (GetAsyncKeyState(hotkeys["developerMode"]) & 1) functions::developerMode();
	if (GetAsyncKeyState(hotkeys["fps60"]) & 1) functions::fps60();
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

	if (GetAsyncKeyState(VK_NUMPAD3) & 1) openMenu = !openMenu;

	keybindings();

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