#define _CRT_SECURE_NO_WARNINGS

// ===== LAYER RELOAD FUNCTIONALITY =====
// Tears down and re-parses the selected level layers (.export files) at
// runtime, then re-activates them. Also renders the "Layers" panel. Split out
// of gui.cpp.

#include "gui.h"
#include "gui_internal.h"

#include "../imgui/imgui.h"

#include <vector>
#include <string>
#include <cstring>

typedef void(__fastcall* LayerMgrMethod_Int)(void* thisPtr, void* edx_unused, int index);
typedef void(__fastcall* LayerMgrMethod_String)(void* thisPtr, void* edx_unused, const char* name);
typedef void(__fastcall* LayerMgrFlush_t)(void* pThis, void* edx_unused);
typedef int(__fastcall* LoadObjects_t)(void* pThis, void* edx_unused);

const auto DeactivateObjects = (LayerMgrMethod_Int)0x00559AC0;
const auto ActivateObjects = (LayerMgrMethod_Int)0x00559A00;
const auto LayerMgrFlush = (LayerMgrFlush_t)0x0055B420;
const auto LoadObjects = (LoadObjects_t)0x0055A400;

void* layerMgr = (void*)0x00771EC8;

struct LayerInfo {
	char name[65];
	bool selected = false;
};
static std::vector<LayerInfo> g_layers;

void gui::RefreshLayers() noexcept {
	int layerCount = *(int*)0x00771F60;
	char* layerArray = *(char**)0x00771F64;
	if (!layerArray || layerCount <= 0) {
		g_layers.clear();
		return;
	}

	g_layers.clear();
	for (int i = 0; i < layerCount && i < 512; i++) {
		char* layerPtr = layerArray + (i * 0x44);
		LayerInfo info;
		memcpy(info.name, layerPtr, 64);
		info.name[64] = '\0';
		info.selected = false;
		g_layers.push_back(info);
	}
}

void gui::ReloadSelectedLayers() noexcept {
	static bool firstReloadDone = false;
	static bool isOriginalNonLayer[16384];
	static unsigned char originalByte67[512];

	__try {
		int layerCount = *(int*)0x00771F60;
		char* layerArray = *(char**)0x00771F64;
		char* objTable = *(char**)0x0076F648;
		int* objMgr = (int*)0x0076CD88;

		if (!layerArray) return;

		// Use the user-selected layers
		bool wasLoaded[512];
		memset(wasLoaded, 0, sizeof(wasLoaded));
		int loadedCount = 0;
		for (int i = 0; i < layerCount && i < 512; i++) {
			char* layerPtr = layerArray + (i * 0x44);
			if (i < g_layers.size() && g_layers[i].selected) {
				wasLoaded[i] = true;
				loadedCount++;
			}
			if (!firstReloadDone) {
				originalByte67[i] = (unsigned char)layerPtr[67];
			}
		}

		if (loadedCount == 0) return;

		// Phase 1: Deactivate loaded layers
		for (int i = 0; i < layerCount; i++) {
			if (i < 512 && !wasLoaded[i]) continue;
			DeactivateObjects(layerMgr, nullptr, i);
		}

		// Phase 2: Destroy non-preserved objects
		if (objTable) {
			int maxSlots = objMgr[2614];

			// Snapshot ALL current non-layer objects to preserve them
			memset(isOriginalNonLayer, 0, sizeof(isOriginalNonLayer));
			for (int i = 0; i < maxSlots && i < 16384; i++) {
				char* slot = objTable + (i * 20);
				void* pObj = *(void**)(slot);
				short layerID = *(short*)(slot + 10);
				if (pObj && layerID == -1) {
					isOriginalNonLayer[i] = true;
				}
			}
			if (!firstReloadDone) {
				firstReloadDone = true;
			}

			// Pass 1: Destroy layer objects first (their dtors may reference sub-objects)
			for (int i = 0; i < maxSlots; i++) {
				char* slot = objTable + (i * 20);
				void* pObj = *(void**)(slot);
				if (!pObj) continue;

				short layerID = *(short*)(slot + 10);
				if (layerID == -1) continue;
				if (layerID >= 0 && layerID < 512 && !wasLoaded[layerID]) continue;

				__try {
					void*** vt = (void***)pObj;
					typedef void* (__thiscall* Dtor_t)(void*, int);
					((Dtor_t)(*vt)[0])(pObj, 1);
				}
				__except (EXCEPTION_EXECUTE_HANDLER) {}

				*(void**)(slot + 0) = nullptr;
				*(short*)(slot + 4) = -1;
				*(short*)(slot + 6) = -1;
				*(short*)(slot + 8) = -1;
				*(short*)(slot + 10) = -1;
				*(short*)(slot + 12) = -2;
				*(short*)(slot + 14) = -1;
			}

			// Pass 2: Destroy sub-objects (layerID == -1, not original)
			for (int i = 0; i < maxSlots; i++) {
				char* slot = objTable + (i * 20);
				void* pObj = *(void**)(slot);
				if (!pObj) continue;

				short layerID = *(short*)(slot + 10);
				if (layerID != -1) continue;
				if (i < 16384 && isOriginalNonLayer[i]) continue;

				__try {
					void*** vt = (void***)pObj;
					typedef void* (__thiscall* Dtor_t)(void*, int);
					((Dtor_t)(*vt)[0])(pObj, 0);
				}
				__except (EXCEPTION_EXECUTE_HANDLER) {}

				*(void**)(slot + 0) = nullptr;
				*(short*)(slot + 4) = -1;
				*(short*)(slot + 6) = -1;
				*(short*)(slot + 8) = -1;
				*(short*)(slot + 10) = -1;
				*(short*)(slot + 12) = -2;
				*(short*)(slot + 14) = -1;
			}

			// Reset loaded layer heads and flags
			for (int li = 0; li < layerCount; li++) {
				if (li < 512 && !wasLoaded[li]) continue;
				char* layerPtr = layerArray + (li * 0x44);
				*(short*)(layerPtr + 64) = -1;
				layerPtr[66] = 0;
				layerPtr[67] = originalByte67[li] & ~0x0C;
			}
		}

		// Phase 3: Clear hash table, rebuild for surviving objects, rebuild free list
		short* hashTable = (short*)0x0076CD88;
		for (int i = 0; i < 4096; i++) {
			hashTable[i] = -1;
		}
		objTable = *(char**)0x0076F648;
		int rebuilt = 0;
		int liveCount = 0;
		int freeCount = 0;
		short prevFree = -1;
		short newFreeHead = -1;
		if (objTable) {
			int maxSlots = objMgr[2614];
			for (int i = 0; i < maxSlots; i++) {
				char* slot = objTable + (i * 20);
				void* pObj = *(void**)(slot);
				if (pObj) {
					__try {
						unsigned char flags = *((unsigned char*)pObj + 127);
						if (flags & 0x10) {
							__int64 guid = *(__int64*)((char*)pObj + 8);
							unsigned short lo = (unsigned short)(guid & 0xFFFF);
							unsigned short hi = (unsigned short)((guid >> 32) & 0xFFFF);
							int bucket = ((-251) * (hi ^ lo)) & 0xFFF;
							*(short*)(slot + 14) = hashTable[bucket];
							hashTable[bucket] = (short)i;
							rebuilt++;
						}
						liveCount++;
					}
					__except (EXCEPTION_EXECUTE_HANDLER) {
						*(void**)(slot + 0) = nullptr;
						*(short*)(slot + 4) = -1;
						*(short*)(slot + 6) = -1;
						*(short*)(slot + 8) = -1;
						*(short*)(slot + 10) = -1;
						*(short*)(slot + 12) = -2;
						*(short*)(slot + 14) = -1;
					}
				}
				if (!*(void**)(slot) && i > 0) {
					*(short*)(slot + 4) = -1;
					*(short*)(slot + 6) = prevFree;
					if (prevFree != -1) {
						*(short*)(objTable + 20 * prevFree + 4) = (short)i;
					}
					else {
						newFreeHead = (short)i;
					}
					prevFree = (short)i;
					freeCount++;
				}
			}
		}
		*(short*)&objMgr[2609] = newFreeHead;
		objMgr[2613] = liveCount;

		// Set resource flags on loaded layers before LoadObjects
		for (int li = 0; li < layerCount; li++) {
			if (li < 512 && !wasLoaded[li]) continue;
			char* layerPtr = layerArray + (li * 0x44);
			*(unsigned short*)(layerPtr + 66) |= 0x0408;
		}

		// Temporarily blank non-selected layer names so LoadObjects can't open their .export files
		char savedNames[512][64];
		for (int li = 0; li < layerCount && li < 512; li++) {
			char* layerPtr = layerArray + (li * 0x44);
			memcpy(savedNames[li], layerPtr, 64);
			if (!wasLoaded[li]) {
				memset(layerPtr, 0, 64);
			}
		}

		// Only reset global logic manager for full reloads
		bool fullReload = (loadedCount == layerCount);
		if (fullReload) {
			*(int*)(0x00772050 + 0x10) = 0;
			*(int*)(0x00772050 + 0x2C) = 0;
			*(int*)(0x00772050 + 0x48) = 0;
		}

		// Phase 4: LoadObjects (re-parse .export files)
		__try {
			LoadObjects(layerMgr, nullptr);
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {}

		// Restore blanked layer names
		for (int li = 0; li < layerCount && li < 512; li++) {
			if (!wasLoaded[li]) {
				char* layerPtr = layerArray + (li * 0x44);
				memcpy(layerPtr, savedNames[li], 64);
			}
		}

		// Phase 5: Post-process type-53 objects
		objTable = *(char**)0x0076F648;
		int maxObj = objMgr[2614];
		if (objTable && maxObj > 0) {
			for (int i = 0; i < maxObj; i++) {
				char* slot = objTable + (i * 20);
				void* pObj = *(void**)(slot);
				if (pObj && *((unsigned char*)pObj + 124) == 53) {
					__try {
						void** vtbl = *(void***)pObj;
						typedef void(__thiscall* VMethod_t)(void*);
						((VMethod_t)vtbl[49])(pObj);
						((VMethod_t)vtbl[50])(pObj);
					}
					__except (EXCEPTION_EXECUTE_HANDLER) {}
				}
			}
		}

		// Phase 6: Activate loaded layers
		for (int i = 0; i < layerCount; i++) {
			if (i < 512 && !wasLoaded[i]) continue;
			__try {
				ActivateObjects(layerMgr, nullptr, i);
			}
			__except (EXCEPTION_EXECUTE_HANDLER) {}
		}

		// Phase 7: Flush
		__try {
			*(int*)0x00771F74 = 1;
			LayerMgrFlush(layerMgr, nullptr);
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {}
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {}
}

void RenderLayers()
{
	if (ImGui::CollapsingHeader(lang ? "Layers" : (const char*)u8"Слои"))
	{
		ImGui::Indent();
		if (ImGui::Button(lang ? "Refresh Layer List" : (const char*)u8"Обновить список слоев")) {
			gui::RefreshLayers();
		}

		if (!g_layers.empty()) {
			if (ImGui::Button(lang ? "Select All" : (const char*)u8"Выбрать все")) {
				for (auto& l : g_layers) l.selected = true;
			}
			ImGui::SameLine();
			if (ImGui::Button(lang ? "Deselect All" : (const char*)u8"Снять выделение")) {
				for (auto& l : g_layers) l.selected = false;
			}

			ImGui::BeginChild("LayerListScroll", ImVec2(0, 200), true);
			for (int i = 0; i < (int)g_layers.size(); i++) {
				ImGui::PushID(i);
				ImGui::Checkbox(g_layers[i].name, &g_layers[i].selected);
				ImGui::PopID();
			}
			ImGui::EndChild();

			if (ImGui::Button(lang ? "Reload Selected Layers" : (const char*)u8"Перезагрузить выбранные слои")) {
				gui::ReloadSelectedLayers();
			}
		}
		ImGui::Unindent();
	}
}
