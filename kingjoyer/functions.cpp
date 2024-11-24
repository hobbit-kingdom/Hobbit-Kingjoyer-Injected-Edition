#include "functions.h"


#include "gui.h"
#include "byte_functions.h"
#include "Randommod.h"
#include "PickupAll.h"

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_dx9.h"
#include "../imgui/imgui_impl_win32.h"

#include <iostream>
#include "string"
#include <chrono>
#include <random>
#include <thread>
#include <filesystem>

void functions::renderVolumes(bool& renderVolumes, bool shouldToggle) noexcept {
	change_1Byte_hobbit((LPVOID)0x00777B04, 0x01, 0x00); // функция рендера волумов
	if (shouldToggle) renderVolumes = !renderVolumes;
}

void functions::polyCache(bool& polyCache, bool shouldToggle) noexcept {
	change_1Byte_hobbit((LPVOID)0x00778078, 0x01, 0x00); // функция рендера полигонов
	if (shouldToggle) polyCache = !polyCache;
}

void functions::renderLoadTriggers(bool& renderLoadTriggers, bool shouldToggle) noexcept {
	change_1Byte_hobbit((LPVOID)0x00777B18, 0x01, 0x00); // функция рендера загрузочных триггеров
	if (shouldToggle) renderLoadTriggers = !renderLoadTriggers;
}

void functions::renderTriggers(bool& renderTriggers, bool shouldToggle) noexcept {
	change_1Byte_hobbit((LPVOID)0x00777B1C, 0x01, 0x00); // функция рендера триггеров
	if (shouldToggle) renderTriggers = !renderTriggers;
}

void functions::renderWater(bool& renderWater, bool shouldToggle) noexcept {
	change_1Byte_hobbit((LPVOID)0x00777B10, 0x01, 0x00); // функция рендера воды
	if (shouldToggle) renderWater = !renderWater;
}

void functions::renderWeb(bool& renderWeb, bool shouldToggle) noexcept {
	change_1Byte_hobbit((LPVOID)0x00777B90, 0x01, 0x00); // функция рендера паутины
	if (shouldToggle) renderWeb = !renderWeb;
}

void functions::renderRopes(bool& renderRopes, bool shouldToggle) noexcept {
	change_1Byte_hobbit((LPVOID)0x00777B24, 0x01, 0x00); // функция рендера веревок
	if (shouldToggle) renderRopes = !renderRopes;
}

void functions::renderLeaves(bool& renderLeaves, bool shouldToggle) noexcept {
	change_1Byte_hobbit((LPVOID)0x00777B80, 0x01, 0x00); // функция рендер кластеров листвы деревьев
	if (shouldToggle) renderLeaves = !renderLeaves;
}

void functions::renderChests(bool& renderChests, bool shouldToggle) noexcept {
	change_1Byte_hobbit((LPVOID)0x00777AF0, 0x01, 0x00); // функция рендер сундуков
	if (shouldToggle) renderChests = !renderChests;
}

void functions::renderLevers(bool& renderLevers, bool shouldToggle) noexcept {
	change_1Byte_hobbit((LPVOID)0x00777AEC, 0x01, 0x00); // функция рендер рычагов
	if (shouldToggle) renderLevers = !renderLevers;
}

void functions::renderBilbo(bool& renderBilbo, bool shouldToggle) noexcept {
	change_1Byte_hobbit((LPVOID)0x00777AA0, 0x01, 0x00); // функция рендер Бильбо
	if (shouldToggle) renderBilbo = !renderBilbo;
}

void functions::renderLights(bool& renderLights, bool shouldToggle) noexcept {
	change_1Byte_hobbit((LPVOID)0x00777AA4, 0x01, 0x00); // функция рендер света
	if (shouldToggle) renderLights = !renderLights;
}

void functions::renderEffects(bool& renderEffects, bool shouldToggle) noexcept {
	change_1Byte_hobbit((LPVOID)0x00777B88, 0x01, 0x00); // функция рендер эффектов
	if (shouldToggle) renderEffects = !renderEffects;
}

void functions::breakway(bool& breakway, bool shouldToggle) noexcept {
	change_1Byte_hobbit((LPVOID)0x00777B0C, 0x01, 0x00); // функция рендера падающего пути
	if (shouldToggle) breakway = !breakway;
}

void functions::boulderRun(bool& boulderRun, bool shouldToggle) noexcept {
	change_1Byte_hobbit((LPVOID)0x00777AFC, 0x01, 0x00); // функция рендер болдер рана
	if (shouldToggle) boulderRun = !boulderRun;
}

void functions::renderSkybox(bool& renderSkybox, bool shouldToggle) noexcept {
	change_1Byte_hobbit((LPVOID)0x00777B5C, 0x01, 0x00); // функция рендера скайбокса
	if (shouldToggle) renderSkybox = !renderSkybox;
}

void functions::renderSavePedestal(bool& renderSavePedestal, bool shouldToggle) noexcept {
	change_1Byte_hobbit((LPVOID)0x00777AF8, 0x01, 0x00); // функция рендера сохранялок
	if (shouldToggle) renderSavePedestal = !renderSavePedestal;
}

void functions::renderPushBoxes(bool& renderPushBoxes, bool shouldToggle) noexcept {
	change_1Byte_hobbit((LPVOID)0x00777AF4, 0x01, 0x00); // функция рендера пушбоксов
	if (shouldToggle) renderPushBoxes = !renderPushBoxes;
}

void functions::renderRigidInstances(bool& renderRigidInstances, bool shouldToggle) noexcept {
	change_1Byte_hobbit((LPVOID)0x00777A8C, 0x01, 0x00); // функция рендера rigidInstances
	if (shouldToggle) renderRigidInstances = !renderRigidInstances;
}

void functions::renderPlaySurface(bool& renderPlaySurface, bool shouldToggle) noexcept {
	change_1Byte_hobbit((LPVOID)0x00777A98, 0x01, 0x00); // функция рендера ландшафта
	if (shouldToggle) renderPlaySurface = !renderPlaySurface;
}

void functions::renderGeometry(bool& renderGeometry, bool shouldToggle) noexcept {
	change_1Byte_hobbit((LPVOID)0x0075D2CC, 0x01, 0x00); // функция рендера геометрии
	if (shouldToggle) renderGeometry = !renderGeometry;
}