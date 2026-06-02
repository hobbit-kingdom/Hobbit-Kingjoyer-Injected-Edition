#pragma once

// Shared declarations for the split-up GUI translation units.
//
// gui.cpp used to be one giant file. It has been broken into category files:
//   gui_platform.cpp    - Win32 window / D3D9 device / ImGui lifecycle
//   gui_layers.cpp      - layer reload functionality + the "Layers" panel
//   gui_sdk_panels.cpp   - object list, NPC anim, object properties, spawn,
//                          and the custom in-game UI helpers ("SDK testing")
//   gui_skins.cpp       - skinchanger ("SKINS" directory) helpers
//   gui.cpp             - shared state + the main gui::Render() menu, split
//                         into per-category static render functions
//
// Anything that needs to be referenced across those files is declared here.

// vector3 is passed by reference only, so a forward declaration is enough and
// we avoid pulling the whole SDK into every file that includes this header.
struct vector3;

// 0 - RUS , 1 - ENG. Defined in gui.cpp, used by every panel for labels.
extern int lang;

// ---- gui_skins.cpp ----
void displaySkinButtons(bool lang);

// ---- gui_layers.cpp ----
// Renders the "Layers" collapsing header (refresh / select / reload UI).
void RenderLayers();

// ---- gui_sdk_panels.cpp ----
// Reads Bilbo's current world position into outPos.
void getBilboPos(vector3& outPos);

// Custom in-game UI helpers.
void InitDialogHook();   // installs the OpenDialog MinHook (the "init hook" button)
void ShowMyTextScreen(); // pops the pause text screen with a custom message
void ShowMyMessage();    // pops the in-game info overlay with a custom message

// "SDK testing" / object panels (collapsing headers + the props popup window).
void showObjectList();
void showNPCTest();
void showSpawnTest();
void showPropsTest();
void showPropsWindow();
extern bool g_propsWindowOpen;
