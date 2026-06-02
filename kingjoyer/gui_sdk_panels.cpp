#define _CRT_SECURE_NO_WARNINGS

// "SDK testing" panels split out of gui.cpp:
//   - object list browser
//   - NPC animation tester
//   - object property editor (+ popup window)
//   - object spawner
//   - custom in-game UI helpers (pause text screen / info overlay / dialog hook)

#include "gui.h"
#include "gui_internal.h"
#include "byte_functions.h"

#include "../meridian/meridian.hpp"

#include "../sdk/meridian_types.h"
#include "../sdk/engine_core_sdk.h"
#include "../sdk/meridian_sdk.h"
#include "../sdk/custom_page.h"

#include "../imgui/imgui.h"

#include "../minhook/MinHook.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cfloat>
#include <string>
#include <vector>

static std::vector<std::string> objects;

uint64_t getObjectGUID(void* pEntity)
{
	uint64_t GUID = 0;

	try
	{
		GUID = read_value_hobbit<uint64_t>(LPBYTE(pEntity) + 0x8);
	}
	catch (...)
	{
		GUID = 0;
	}

	return GUID;
}

uint32_t getObjectType(void* pEntity)
{
	uint32_t Type = 0;

	try
	{
		Type = read_value_hobbit<uint8_t>(LPBYTE(pEntity) + 0x7C);
	}
	catch (...)
	{
		Type = 0;
	}

	return Type;
}

char* getObjectName(void* pEntity, char out_name[32])
{
	try
	{
		char* name_ptr = read_value_hobbit<char*>(LPBYTE(pEntity) + 0xA0);
		if (name_ptr) {
			strncpy(out_name, name_ptr, sizeof(out_name));
			out_name[sizeof(out_name) - 1] = '\0';
		}
	}
	catch (...)
	{
		strcpy(out_name, "ERR");
	}

	return out_name;
}

void updateObjectList()
{
	const LPVOID objects_array_ptr_offs = LPVOID(0x0076F648);
	const LPVOID objects_count_offs = LPVOID(0x0076F660);
	const SIZE_T OBJ_RECORD_SIZE = 0x14;

	void* objects_ptr = read_value_hobbit<void*>(objects_array_ptr_offs);
	size_t objects_cnt = read_value_hobbit<size_t>(objects_count_offs);

	objects.clear();

	for (size_t i = 0; i < objects_cnt; i++) {
		void* pRecord = LPBYTE(objects_ptr) + i * OBJ_RECORD_SIZE;
		void* pEntity = *((void**)pRecord);

		if (pEntity) {
			uint64_t GUID = 0;
			char nam[32] = "\"\"";
			char str[256];

			GUID = getObjectGUID(pEntity);
			getObjectName(pEntity, nam);

			sprintf_s(str, "%p - %08X_%08X - %s - %d",
				pEntity,
				uint32_t((GUID >> 32) & 0xFFFFFFFF),
				uint32_t(GUID & 0xFFFFFFFF),
				nam,
				getObjectType(pEntity)
			);

			objects.push_back(str);
		}
	}
}

void* getObjectByGUID(uint64_t guid)
{
	const LPVOID objects_array_ptr_offs = LPVOID(0x0076F648);
	const LPVOID objects_count_offs = LPVOID(0x0076F660);
	const SIZE_T OBJ_RECORD_SIZE = 0x14;

	void* objects_ptr = read_value_hobbit<void*>(objects_array_ptr_offs);
	size_t objects_cnt = read_value_hobbit<size_t>(objects_count_offs);

	for (size_t i = 0; i < objects_cnt; i++) {
		void* pRecord = LPBYTE(objects_ptr) + i * OBJ_RECORD_SIZE;
		void* pEntity = *((void**)pRecord);

		if (pEntity && getObjectGUID(pEntity) == guid) {
			return pEntity;
		}
	}

	return NULL;
}

void showObjectList(void)
{
	if (ImGui::CollapsingHeader(lang ? "Object List" : (const char*)u8"Список объектов"))
	{
		if (ImGui::Button(lang ? "Refresh" : (const char*)u8"Обновить"))
			updateObjectList();

		if (ImGui::BeginCombo(lang ? "ObjectList" : (const char*)u8"СписокОбъектов", ""))
		{
			for (size_t i = 0; i < objects.size(); i++)
				ImGui::Selectable(objects[i].c_str());
			ImGui::EndCombo();
		}

		ImGui::Text(lang ? "Objects Total: %u" : (const char*)u8"Количество объектов: %u", objects.size());
	}
}

void* pNPC;
char anim_result[32] = "\"\"";

// exact size is unknown for now
struct rhandle
{
	int something;
};

class anim_track_controller
{
public:
	virtual ~anim_track_controller(void); // create the VMT

	rhandle m_hAnimGroup; // + 0x04
};
typedef void(__thiscall anim_track_controller::* SetAnimPROCPTR)(int anim_id, float blend_time);

class rsc_mgr
{
	int dummy;
};
// loads resource if it's not loaded yet
typedef void* (__thiscall rsc_mgr::* LockRHandlePROCPTR)(rhandle* _rhandle);
// some other operation on rhandle, always follows LockRHandle
typedef int(__thiscall rsc_mgr::* unkhandlePROCPTR)(rhandle* _rhandle);

struct anim_data
{
	char name[32];
	char data[48];
};

struct anim_group
{
	char name[60];
	void* ptr1;
	int version;
	int num_frames;
	int num_unk_jf;

	uint32_t bones_count;
	void* bones_ptr;

	uint32_t anims_count;
	anim_data* anims_ptr;

	// ...
};

static void setNPCAnim(void* pNPC, int anim)
{
	uint32_t animAdd1 = (uint32_t)pNPC;
	uint32_t animAdd2 = read_value_hobbit<uint32_t>(LPVOID(0x304 + animAdd1));
	uint32_t animAdd3 = read_value_hobbit<uint32_t>(LPVOID(0x50 + animAdd2));
	uint32_t animAdd4 = read_value_hobbit<uint32_t>(LPVOID(0x10C + animAdd3));
	if (animAdd4 == 0)
	{
		strcpy(anim_result, "ERROR");
	}
	else {
		anim_track_controller* pController = (anim_track_controller*)animAdd4;

		uint32_t _SetAnimPTR = 0x5434B0;
		SetAnimPROCPTR SetAnimPTR;
		memcpy(&SetAnimPTR, &_SetAnimPTR, 4);

		(pController->*SetAnimPTR)(anim, 1.f);

		/*
		uint32_t animationAddress = 0x8 + animAdd4;
		int *pI = (int*)animationAddress;

		*pI = anim;
		*/

		strcpy(anim_result, "ANIM OK");
	}
}

static void getNPCAnimList(void* pNPC, std::vector<std::string>& out_vec)
{
	uint32_t animAdd1 = (uint32_t)pNPC;
	uint32_t animAdd2 = read_value_hobbit<uint32_t>(LPVOID(0x304 + animAdd1));
	uint32_t animAdd3 = read_value_hobbit<uint32_t>(LPVOID(0x50 + animAdd2));
	uint32_t animAdd4 = read_value_hobbit<uint32_t>(LPVOID(0x10C + animAdd3));
	if (animAdd4 == 0)
	{
		strcpy(anim_result, "ERROR");
	}
	else {
		anim_track_controller* pController = (anim_track_controller*)animAdd4;

		uint32_t _LockRHandlePTR = 0x549470;
		LockRHandlePROCPTR LockRHandlePTR;
		memcpy(&LockRHandlePTR, &_LockRHandlePTR, 4);

		uint32_t _unkhandlePTR = 0x549580;
		unkhandlePROCPTR unkhandlePTR;
		memcpy(&unkhandlePTR, &_unkhandlePTR, 4);

		rsc_mgr* g_RscMgr = (rsc_mgr*)0x76C0D0;

		anim_group* pGroup = (anim_group*)(g_RscMgr->*LockRHandlePTR)(&pController->m_hAnimGroup);
		(g_RscMgr->*unkhandlePTR)(&pController->m_hAnimGroup);

		for (uint32_t i = 0; i < pGroup->anims_count; i++) {
			char str[128];
			sprintf(str, "%d : %s", i, pGroup->anims_ptr[i].name);
			out_vec.push_back(str);
		}

		strcpy(anim_result, "ANIM OK");
	}
}

static char _NPC_anim[128] = "1";

std::vector<std::string> _NPC_anim_list;

void showNPCTest(void)
{
	static char _NPC_Status[128] = "NOSTATUS";
	static char _NPC_Guid[128] = "0D8AD910_E8851002";

	if (ImGui::CollapsingHeader(lang ? "NPC Anim" : (const char*)u8"НПС Анимация"))
	{
		ImGui::Text(_NPC_Status);

		ImGui::InputText(lang ? "NPC Guild:" : (const char*)u8"НПС Guild", _NPC_Guid, sizeof(_NPC_Guid));

		if (ImGui::Button(lang ? "Query NPC" : (const char*)u8"Найти НПС")) {
			uint32_t guid_high;
			uint32_t guid_low;

			if (sscanf(_NPC_Guid, "%X_%X", &guid_high, &guid_low) == 2) {
				pNPC = getObjectByGUID((uint64_t(guid_high) << 32) | guid_low);
				if (pNPC) {
					strcpy_s(_NPC_Status, "NPC OK");
					// Clear and refresh the list
					_NPC_anim_list.clear();
					getNPCAnimList(pNPC, _NPC_anim_list);
				}
				else {
					strcpy_s(_NPC_Status, "NPC Not found");
					_NPC_anim_list.clear();
				}
			}
			else {
				strcpy_s(_NPC_Status, "Invalid GUID");
				_NPC_anim_list.clear();
			}
		}

		ImGui::Text("");

		// Optional: Keep manual input for custom anim IDs
		if (ImGui::TreeNode(lang ? "Manual Input" : (const char*)u8"Ручной ввод")) {
			ImGui::InputText(lang ? "Anim ID:" : (const char*)u8"ID Анимации", _NPC_anim, sizeof(_NPC_anim), ImGuiInputTextFlags_CharsDecimal);
			int anim_id = atoi(_NPC_anim);

			if (ImGui::Button(lang ? "Do Set Anim" : (const char*)u8"Установить Анимацию") && pNPC) {
				setNPCAnim(pNPC, anim_id);
			}
			ImGui::TreePop();
		}

		ImGui::Text("");


		// Alternative simpler version (uncomment if you prefer this style):

		if (ImGui::BeginListBox(lang ? "Anims:" : (const char*)u8"Анимации:", ImVec2(-FLT_MIN, 300))) {
			for (int i = 0; i < _NPC_anim_list.size(); i++) {
				const std::string& str = _NPC_anim_list[i];
				int anim_id = 0;
				sscanf(str.c_str(), "%d", &anim_id);

				ImGui::PushID(i);

				// Calculate button width
				float playBtnWidth = 50.0f;
				float selectableWidth = ImGui::GetContentRegionAvail().x - playBtnWidth - ImGui::GetStyle().ItemSpacing.x;

				// Selectable that doesn't fill entire width
				if (ImGui::Selectable(str.c_str(), false, ImGuiSelectableFlags_None, ImVec2(selectableWidth, 0))) {
					if (pNPC) setNPCAnim(pNPC, anim_id);
				}

				// Play button on same line
				ImGui::SameLine();
				if (ImGui::SmallButton("Play") && pNPC) {
					setNPCAnim(pNPC, anim_id);
				}

				ImGui::PopID();
			}
			ImGui::EndListBox();
		}

	}
}

static object* g_propsObject;
static prop_array g_objectProps;
bool g_propsWindowOpen;

static void formatGuidString(char* pBuffer, size_t bufferSize, const guid& value)
{
	uint32_t guid_high = uint32_t(value.Guid >> 32);
	uint32_t guid_low = uint32_t(value.Guid);
	sprintf_s(pBuffer, bufferSize, "%X_%X", guid_high, guid_low);
}

static bool tryParseGuidString(const char* pBuffer, guid& outGuid)
{
	uint32_t guid_high;
	uint32_t guid_low;
	unsigned long long fullGuid;

	if (sscanf(pBuffer, "%X_%X", &guid_high, &guid_low) == 2) {
		outGuid.Guid = (uint64_t(guid_high) << 32) | guid_low;
		return true;
	}

	if (sscanf(pBuffer, "%llX", &fullGuid) == 1) {
		outGuid.Guid = fullGuid;
		return true;
	}

	return false;
}

static bool showGuidInputText(const char* pLabel, guid& value)
{
	char guidBuffer[32];
	formatGuidString(guidBuffer, sizeof(guidBuffer), value);

	ImGuiInputTextFlags flags = ImGuiInputTextFlags_CharsUppercase | ImGuiInputTextFlags_EnterReturnsTrue;
	bool submitted = ImGui::InputText(pLabel, guidBuffer, sizeof(guidBuffer), flags);
	bool finishedEditing = submitted || ImGui::IsItemDeactivatedAfterEdit();

	if (!finishedEditing)
		return false;

	guid parsedGuid;
	if (!tryParseGuidString(guidBuffer, parsedGuid))
		return false;

	value = parsedGuid;
	return true;
}

static bool showBBoxEditor(bbox& value)
{
	bool changed = false;
	changed |= ImGui::InputFloat3("Min", (float*)&value.Min);
	changed |= ImGui::InputFloat3("Max", (float*)&value.Max);
	return changed;
}

static ImGuiListClipper clipper; // Modera: had to make it global, MSVC doesn't let me use this inside function bc it has a destructor and function uses __try/__expect
void showPropsWindow(void)
{
	if (!ImGui::Begin(lang ? "Objects Properties" : (const char*)u8"Свойства Объектов", &g_propsWindowOpen))
	{
		ImGui::End();
		return;
	}

	// Basic null checks before proceeding
	if (!g_propsObject || !g_objectProps.pData || g_objectProps.m_Count <= 0)
	{
		ImGui::TextDisabled("No object selected or invalid data");
		ImGui::End();
		return;
	}

	// Sanity check count to prevent insane iterations
	if (g_objectProps.m_Count > 10000)
	{
		ImGui::TextDisabled("Invalid property count: %d", g_objectProps.m_Count);
		g_propsWindowOpen = false;
		ImGui::End();
		return;
	}

	__try
	{
		ImGui::Columns(2, NULL, true);
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2, 2));

		clipper.Begin(g_objectProps.m_Count, ImGui::GetTextLineHeightWithSpacing());

		while (clipper.Step())
		{
			for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
			{
				// Validate index and pointer before accessing
				if (!g_objectProps.pData || !g_objectProps.pData[i].m_Name)
					continue;

				// Check if name pointer is readable (quick validation)
				if (IsBadStringPtrA(g_objectProps.pData[i].m_Name, 256))
					continue;

				// draw a line between rows
				ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(8, 3));
				ImGui::Separator();
				ImGui::PopStyleVar(1);

				// draw name
				ImGui::TextUnformatted(g_objectProps.pData[i].m_Name);

				// draw value
				ImGui::NextColumn();
				ImGui::PushItemWidth(-1);

				ImGui::PushID(i); // Use index instead of potentially unstable string pointer

				ed_property prop = { 0 };
				g_propsObject->GetProperty(prop, g_objectProps.pData[i].m_Name);

				switch (g_objectProps.pData[i].m_PropType)
				{
				case PROP_s32: {
					if (ImGui::InputInt("##s32", &prop.m_Value.m_s32Value))
						g_propsObject->SetProperty(g_objectProps.pData[i].m_Name, prop);
					break;
				}

				case PROP_f32: {
					if (ImGui::InputFloat("##f32", &prop.m_Value.m_f32Value))
						g_propsObject->SetProperty(g_objectProps.pData[i].m_Name, prop);
					break;
				}

				case PROP_xbool: {
					bool bVal = !!prop.m_Value.m_xboolValue;
					if (ImGui::Checkbox("##xbool", &bVal)) {
						prop.m_Value.m_xboolValue = xbool(bVal);
						g_propsObject->SetProperty(g_objectProps.pData[i].m_Name, prop);
					}
					break;
				}

				case PROP_string:
				case PROP_resource: {
					prop.m_Value.m_ResourceName[sizeof(prop.m_Value.m_ResourceName) - 1] = 0;
					if (ImGui::InputText("##str", prop.m_Value.m_ResourceName, sizeof(prop.m_Value.m_ResourceName)))
						g_propsObject->SetProperty(g_objectProps.pData[i].m_Name, prop);
					break;
				}

				case PROP_vector3: {
					if (ImGui::InputFloat3("##vec3", (float*)&prop.m_Value.m_vec3Value))
						g_propsObject->SetProperty(g_objectProps.pData[i].m_Name, prop);
					break;
				}

				case PROP_bbox: {
					if (showBBoxEditor(prop.m_Value.m_BBox))
						g_propsObject->SetProperty(g_objectProps.pData[i].m_Name, prop);
					break;
				}

				case PROP_angle: {
					if (ImGui::InputFloat("##angle", &prop.m_Value.m_f32Value))
						g_propsObject->SetProperty(g_objectProps.pData[i].m_Name, prop);
					break;
				}

				case PROP_radian3: {
					if (ImGui::InputFloat3("##rad3", (float*)&prop.m_Value.m_vec3Value))
						g_propsObject->SetProperty(g_objectProps.pData[i].m_Name, prop);
					break;
				}

				case PROP_enum_s32: {
					xstring_array* pArr = (xstring_array*)g_objectProps.pData[i].m_pArray;
					if (!pArr || IsBadReadPtr(pArr, sizeof(xstring_array)))
						break;

					s32 sIdx = prop.m_Value.m_s32Value;
					if (sIdx < 0 || sIdx >= (s32)pArr->m_Count)
						break;

					const char* preview = (sIdx >= 0 && sIdx < (s32)pArr->m_Count && pArr->m_pData)
						? pArr->m_pData[sIdx].m_pData : "INVALID";

					if (!IsBadStringPtrA(preview, 256) && ImGui::BeginCombo("##enums32", preview))
					{
						for (u32 j = 0; j < (u32)pArr->m_Count; j++)
						{
							if (!pArr->m_pData || IsBadReadPtr(&pArr->m_pData[j], sizeof(xstring)))
								break;

							const char* elem = pArr->m_pData[j].m_pData;
							if (!elem || IsBadStringPtrA(elem, 256))
								continue;

							if (ImGui::Selectable(elem, (s32)j == sIdx))
							{
								prop.m_Value.m_s32Value = (s32)j;
								g_propsObject->SetProperty(g_objectProps.pData[i].m_Name, prop);
							}
						}
						ImGui::EndCombo();
					}
					break;
				}

				case PROP_enum_xstring: {
					xstring_array* pArr = (xstring_array*)g_objectProps.pData[i].m_pArray;
					if (!pArr || IsBadReadPtr(pArr, sizeof(xstring_array)))
						break;

					const char* preview = prop.m_Value.m_ResourceName;
					if (IsBadStringPtrA(preview, 256))
						break;

					if (ImGui::BeginCombo("##enumstr", preview))
					{
						for (u32 j = 0; j < (u32)pArr->m_Count; j++)
						{
							if (!pArr->m_pData || IsBadReadPtr(&pArr->m_pData[j], sizeof(xstring)))
								break;

							const char* elem = pArr->m_pData[j].m_pData;
							if (!elem || IsBadStringPtrA(elem, 256))
								continue;

							if (ImGui::Selectable(elem, strcmp(preview, elem) == 0))
							{
								strncpy(prop.m_Value.m_ResourceName, elem, sizeof(prop.m_Value.m_ResourceName));
								prop.m_Value.m_ResourceName[sizeof(prop.m_Value.m_ResourceName) - 1] = '\0';
								g_propsObject->SetProperty(g_objectProps.pData[i].m_Name, prop);
							}
						}
						ImGui::EndCombo();
					}
					break;
				}

				case PROP_guid: {
					if (showGuidInputText("##guid", prop.m_Value.m_guidValue))
						g_propsObject->SetProperty(g_objectProps.pData[i].m_Name, prop);
					break;
				}

				case PROP_xcolor: {
					float rgba[4];
					rgba[0] = prop.m_Value.m_xcolorValue.R / 255.f;
					rgba[1] = prop.m_Value.m_xcolorValue.G / 255.f;
					rgba[2] = prop.m_Value.m_xcolorValue.B / 255.f;
					rgba[3] = prop.m_Value.m_xcolorValue.A / 255.f;

					if (ImGui::ColorEdit4("##color", rgba))
					{
						prop.m_Value.m_xcolorValue.R = (u8)(rgba[0] * 255);
						prop.m_Value.m_xcolorValue.G = (u8)(rgba[1] * 255);
						prop.m_Value.m_xcolorValue.B = (u8)(rgba[2] * 255);
						prop.m_Value.m_xcolorValue.A = (u8)(rgba[3] * 255);
						g_propsObject->SetProperty(g_objectProps.pData[i].m_Name, prop);
					}
					break;
				}

				default:
					ImGui::TextDisabled("Unknown type: %d", g_objectProps.pData[i].m_PropType);
					break;
				}

				ImGui::PopID();
				ImGui::PopItemWidth();
				ImGui::NextColumn();
			}
		}

		clipper.End();

		ImGui::PopStyleVar();
		ImGui::Columns(1);
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		// Memory corruption detected, close the window safely
		g_propsWindowOpen = false;
		ImGui::End();
		return;
	}

	ImGui::End();
}

void showPropsTest(void)
{
	static char _object_Status[32];

	if (ImGui::CollapsingHeader(lang ? "Props Test" : (const char*)u8"Тест Свойств Объектов"))
	{
		static char _object_Guid[32];


		ImGui::Text(_object_Status);

		ImGui::InputText(lang ? "Object Guid:" : (const char*)u8"Guid Объекта", _object_Guid, sizeof(_object_Guid));

		if (ImGui::Button(lang ? "Query Object" : (const char*)u8"Свойтва Объекта")) {
			guid objectGuid;

			if (tryParseGuidString(_object_Guid, objectGuid)) {
				object* pObject = (object*)getObjectByGUID(objectGuid.Guid);
				if (pObject) {
					strcpy_s(_object_Status, "Object OK");
					g_objectProps.Clear();
					pObject->EnumerateProperties(g_objectProps);
					g_propsObject = pObject;
				}
				else {
					strcpy_s(_object_Status, "Object Not found");
					g_objectProps.Clear();
					g_propsObject = NULL;
				}
			}
			else {
				strcpy_s(_object_Status, "Invalid GUID");
				g_objectProps.Clear();
				g_propsObject = NULL;
			}
		}

		if (ImGui::Button(lang ? "ShowPropertiesWindow" : (const char*)u8"Показать Окно Свойств")) {
			g_propsWindowOpen = true;
		}
	}
}

static guid spawned_guid;

void getBilboPos(vector3& outPos)
{
	DWORD ukazatel = read_value_hobbit<DWORD>((LPVOID)0x0075BA3C);
	outPos.X = read_value_hobbit<float>((LPDWORD)ukazatel + 5);
	outPos.Y = read_value_hobbit<float>((LPDWORD)ukazatel + 6);
	outPos.Z = read_value_hobbit<float>((LPDWORD)ukazatel + 7);//функция установки точки телепортации
}

static void showSpawnTest_(void)
{
	if (ImGui::CollapsingHeader("Spawn Test"))
	{
		uint32_t guid_high = spawned_guid.Guid >> 32;
		uint32_t guid_low = spawned_guid.Guid;
		char str[32];

		sprintf(str, "%X_%X", guid_high, guid_low);

		ImGui::Text(lang ? "Spawned GUID: %s" : (const char*)u8"Заспавнен GUID: %s", str);

		if (ImGui::Button(lang ? "Do Spawn" : (const char*)u8"Заспавнить"))
		{
			spawned_guid = g_ObjMgr.CreateObject("Marker", guid());

			static int nmarker = 0;
			marker* pMarker = (marker*)getObjectByGUID(spawned_guid.Guid);
			if (pMarker)
			{
				sprintf(str, "marker%d", nmarker++);

				vector3 P; getBilboPos(P);
				pMarker->Move(P, 0);

				pMarker->SetText(str);

				//pMarker->SetObjSaveFlag(1);
			}
		}

		static char i_text[32];
		ImGui::InputText(lang ? "SetText" : (const char*)u8"Установить Текс", i_text, 32);
		if (ImGui::Button(lang ? "Set Text" : (const char*)u8"Установить Текс"))
		{
			marker* pMarker = (marker*)getObjectByGUID(spawned_guid.Guid);
			if (pMarker)
			{
				pMarker->SetText(i_text);
			}
		}
	}
}


const char* ObjectClasses[] = { "RigidInstance", "NPC", "Marker" };

void showSpawnTest(void)
{
	if (ImGui::CollapsingHeader("Spawn Test"))
	{
		uint32_t guid_high = spawned_guid.Guid >> 32;
		uint32_t guid_low = spawned_guid.Guid;
		char str[32];

		sprintf(str, "%X_%X", guid_high, guid_low);

		ImGui::Text(lang ? "Spawned GUID: %s" : (const char*)u8"Заспавнен GUID: %s", str);

		static int objectIndex = 0;
		ImGui::Text(lang ? "Select Object Type" : (const char*)u8"Выбирите тип объекта");
		ImGui::Combo("##spawnObjectType", &objectIndex, ObjectClasses, IM_ARRAYSIZE(ObjectClasses));

		if (ImGui::Button(lang ? "Do Spawn" : (const char*)u8"Заспавнить"))
		{
			spawned_guid = g_ObjMgr.CreateObject(ObjectClasses[objectIndex], guid());

			object* pMarker = (object*)getObjectByGUID(spawned_guid.Guid);
			if (pMarker)
			{
				{
					bin_in BinIn{};
					if (BinIn.OpenFile("./Templates/Test.export") && BinIn.ReadHeader() && BinIn.ReadFields())
					{
						pMarker->OnImport(BinIn);
					}
				}

				vector3 P; getBilboPos(P);
				pMarker->Move(P, 1);
			}
		}


	}
}

typedef void(__thiscall* PauseTextBox_t)(void* self, const wchar_t* title, const wchar_t* body);
typedef void(__thiscall* PauseSaveKiosk_t)(void* self);

static const PauseTextBox_t   Pause_TextBox = (PauseTextBox_t)0x0052D9B0;
static const PauseSaveKiosk_t Pause_SaveKiosk = (PauseSaveKiosk_t)0x0052D960; // the one you tested
void* g_PauseMgr = (void*)0x00763208;

// keep strings alive (the engine copies them, but static is safest)

void ShowMyTextScreen() {

	const wchar_t* kTitle = L"Hello from king174rus";
	const wchar_t* kBody = L"Hello everyone. If you are seeing this message\nit means I'm stepping away from work\nand handing over my crown to Modera.\nI am sorry, goodbye.";

	Pause_TextBox(g_PauseMgr, kTitle, kBody);   // pops the pause text screen with your text
}


typedef void(__thiscall* InfoBox_t)(void* self, const char* title, const wchar_t* body, int withButton);
static const InfoBox_t InfoBox = (InfoBox_t)0x00526640;
void* g_InfoOverlay = (void*)0x007626D0;     // the in-game info-overlay singleton

void ShowMyMessage() {
	// title is ASCII; body is wide (UTF-16). withButton: 1 = show a dismiss button, 0 = none.
	InfoBox(g_InfoOverlay, "QUEST UPDATE", L"You found the Arkenstone!\nReturn to Thorin.", 1);
}

static hobbit_ui::OpenDialog_t o_OpenDialog = nullptr;

void* __fastcall hk_OpenDialog(void* uimgr, void* /*edx*/, void* ctx, const char* name,
	int rL, int rT, int rR, int rB, int a, int b, int c)
{
	if (name && std::strcmp(name, "pause summary") == 0) {
		hobbit_ui::BackdropMode() = hobbit_ui::BD_SUMMARY;   // summary bg
		// -- or --
		// hobbit_ui::BackdropMode() = hobbit_ui::BD_PANEL;
		// hobbit_ui::BackdropScale() = 1.6f;                 // bigger panel
		hobbit_ui::RegisterTemplate();
		void* dlg = o_OpenDialog(uimgr, ctx, "kitchen_sink", rL, rT, rR, rB, a, b, c);
		if (dlg) hobbit_ui::Relabel(dlg);
		return dlg;
	}
	return o_OpenDialog(uimgr, ctx, name, rL, rT, rR, rB, a, b, c);
}

// Installs the OpenDialog MinHook + click callback (the "init hook" button).
void InitDialogHook()
{
	MH_Initialize();
	MH_CreateHook((void*)hobbit_ui::addr::OpenDialog, &hk_OpenDialog, (void**)&o_OpenDialog);
	MH_EnableHook((void*)hobbit_ui::addr::OpenDialog);

	hobbit_ui::OnClick() = [](int id, void* dlg) {
		if (id == hobbit_ui::ID_BUTTON)
			printf("A Button! slider=%d check=%d\n",
				hobbit_ui::GetSliderValue(dlg), hobbit_ui::GetCheck(dlg));
		// ID_CLOSE auto-closes; ID_CHECK fires on toggle
		};
}