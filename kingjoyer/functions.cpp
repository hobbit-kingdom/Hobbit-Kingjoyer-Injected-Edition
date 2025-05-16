#include "functions.h"


#include "byte_functions.h"
#include "Randommod.h"
#include "PickupAll.h"

#include <memoryapi.h>
#include <tlhelp32.h>

void functions::developerMode() noexcept {
	change_1Byte_hobbit((LPVOID)0x007600E9, 0x01, 0x00); //функция включения режима разработчика
	settings["devMode"] = read_int_value((LPVOID)0x007600E9);
}

void functions::fps60() noexcept {
	change_2Byte_hobbit((LPVOID)0x006EFBDA, 0x4180, 0x4204); //функция FPS
}

void functions::renderVolumes() noexcept {
	change_1Byte_hobbit((LPVOID)0x00777B04, 0x01, 0x00);
	settings["renderVolumes"] = read_int_value((LPVOID)0x00777B04);
}

void functions::polyCache() noexcept {
	change_1Byte_hobbit((LPVOID)0x00778078, 0x01, 0x00);
	settings["polyCache"] = read_int_value((LPVOID)0x00778078);
}

void functions::renderLoadTriggers() noexcept {
	change_1Byte_hobbit((LPVOID)0x00777B18, 0x01, 0x00);
	settings["renderLoadTriggers"] = read_int_value((LPVOID)0x00777B18);
}

void functions::renderTriggers() noexcept {
	change_1Byte_hobbit((LPVOID)0x00777B1C, 0x01, 0x00);
	settings["renderTriggers"] = read_int_value((LPVOID)0x00777B1C);
}

void functions::renderWater() noexcept {
	change_1Byte_hobbit((LPVOID)0x00777B10, 0x01, 0x00);
	settings["renderWater"] = read_int_value((LPVOID)0x00777B10);
}

void functions::renderWeb() noexcept {
	change_1Byte_hobbit((LPVOID)0x00777B90, 0x01, 0x00);
	settings["renderWeb"] = read_int_value((LPVOID)0x00777B90);
}

void functions::renderRopes() noexcept {
	change_1Byte_hobbit((LPVOID)0x00777B24, 0x01, 0x00);
	settings["renderRopes"] = read_int_value((LPVOID)0x00777B24);
}

void functions::renderLeaves() noexcept {
	change_1Byte_hobbit((LPVOID)0x00777B80, 0x01, 0x00);
	settings["renderLeaves"] = read_int_value((LPVOID)0x00777B80);
}

void functions::renderChests() noexcept {
	change_1Byte_hobbit((LPVOID)0x00777AF0, 0x01, 0x00);
	settings["renderChests"] = read_int_value((LPVOID)0x00777AF0);
}

void functions::renderLevers() noexcept {
	change_1Byte_hobbit((LPVOID)0x00777AEC, 0x01, 0x00);
	settings["renderLevers"] = read_int_value((LPVOID)0x00777AEC);
}

void functions::renderBilbo() noexcept {
	change_1Byte_hobbit((LPVOID)0x00777AA0, 0x01, 0x00);
	settings["renderBilbo"] = read_int_value((LPVOID)0x00777AA0);
}

void functions::renderLights() noexcept {
	change_1Byte_hobbit((LPVOID)0x00777AA4, 0x01, 0x00);
	settings["renderLights"] = read_int_value((LPVOID)0x00777AA4);
}

void functions::renderEffects() noexcept {
	change_1Byte_hobbit((LPVOID)0x00777B88, 0x01, 0x00);
	settings["renderEffects"] = read_int_value((LPVOID)0x00777B88);
}

void functions::breakway() noexcept {
	change_1Byte_hobbit((LPVOID)0x00777B0C, 0x01, 0x00);
	settings["breakway"] = read_int_value((LPVOID)0x00777B0C);
}

void functions::boulderRun() noexcept {
	change_1Byte_hobbit((LPVOID)0x00777AFC, 0x01, 0x00);
	settings["boulderRun"] = read_int_value((LPVOID)0x00777AFC);
}

void functions::renderSkybox() noexcept {
	change_1Byte_hobbit((LPVOID)0x00777B5C, 0x01, 0x00);
	settings["renderSkybox"] = read_int_value((LPVOID)0x00777B5C);
}

void functions::renderSavePedestal() noexcept {
	change_1Byte_hobbit((LPVOID)0x00777AF8, 0x01, 0x00);
	settings["renderSavePedestal"] = read_int_value((LPVOID)0x00777AF8);
}

void functions::renderPushBoxes() noexcept {
	change_1Byte_hobbit((LPVOID)0x00777AF4, 0x01, 0x00);
	settings["renderPushBoxes"] = read_int_value((LPVOID)0x00777AF4);
}

void functions::renderRigidInstances() noexcept {
	change_1Byte_hobbit((LPVOID)0x00777A8C, 0x01, 0x00);
	settings["renderRigidInstances"] = read_int_value((LPVOID)0x00777A8C);
}

void functions::renderPlaySurface() noexcept {
	change_1Byte_hobbit((LPVOID)0x00777A98, 0x01, 0x00);
	settings["renderPlaySurface"] = read_int_value((LPVOID)0x00777A98);
}

void functions::renderGeometry() noexcept {
	change_1Byte_hobbit((LPVOID)0x0075D2CC, 0x01, 0x00);
	settings["renderGeometry"] = read_int_value((LPVOID)0x0075D2CC);
}


void functions::renderHud() noexcept {
	change_1Byte_hobbit((LPVOID)0x0075EB7C, 0x00, 0x01);
}

void functions::increaseFOV() noexcept {
	plusA_float_hobbit((LPVOID)0x00772BF0, +0.1); //функция приближения камеры на 0.1
}

void functions::decreaseFOV() noexcept {
	plusA_float_hobbit((LPVOID)0x00772BF0, -0.1); //функция отдаления камеры на 0.1
}

void functions::ressurect() noexcept {
	LPDWORD ressurect = ukazatel_hobbit((LPDWORD)0x0075BA3C) + 441;
	change_1Byte_hobbit(ressurect, 0x0, 0x1);
}