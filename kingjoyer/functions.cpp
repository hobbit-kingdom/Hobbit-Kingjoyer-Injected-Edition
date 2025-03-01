#include "functions.h"


#include "byte_functions.h"
#include "Randommod.h"
#include "PickupAll.h"

#include <memoryapi.h>
#include <tlhelp32.h>

void functions::developerMode() noexcept {
	change_1Byte_hobbit((LPVOID)0x007600E9, 0x01, 0x00); //функция включения режима разработчика
}

void functions::fps60() noexcept {
	change_2Byte_hobbit((LPVOID)0x006EFBDA, 0x4180, 0x4204); //функция FPS
}

void functions::renderVolumes() noexcept {
	change_1Byte_hobbit((LPVOID)0x00777B04, 0x01, 0x00); // функция рендера волумов
}

void functions::polyCache() noexcept {
	change_1Byte_hobbit((LPVOID)0x00778078, 0x01, 0x00); // функция рендера полигонов
}

void functions::renderLoadTriggers() noexcept {
	change_1Byte_hobbit((LPVOID)0x00777B18, 0x01, 0x00); // функция рендера загрузочных триггеров
}

void functions::renderTriggers() noexcept {
	change_1Byte_hobbit((LPVOID)0x00777B1C, 0x01, 0x00); // функция рендера триггеров
}

void functions::renderWater() noexcept {
	change_1Byte_hobbit((LPVOID)0x00777B10, 0x01, 0x00); // функция рендера воды
}

void functions::renderWeb() noexcept {
	change_1Byte_hobbit((LPVOID)0x00777B90, 0x01, 0x00); // функция рендера паутины
}

void functions::renderRopes() noexcept {
	change_1Byte_hobbit((LPVOID)0x00777B24, 0x01, 0x00); // функция рендера веревок
}

void functions::renderLeaves() noexcept {
	change_1Byte_hobbit((LPVOID)0x00777B80, 0x01, 0x00); // функция рендер кластеров листвы деревьев
}

void functions::renderChests() noexcept {
	change_1Byte_hobbit((LPVOID)0x00777AF0, 0x01, 0x00); // функция рендер сундуков
}

void functions::renderLevers() noexcept {
	change_1Byte_hobbit((LPVOID)0x00777AEC, 0x01, 0x00); // функция рендер рычагов
}

void functions::renderBilbo() noexcept {
	change_1Byte_hobbit((LPVOID)0x00777AA0, 0x01, 0x00); // функция рендер Бильбо
}

void functions::renderLights() noexcept {
	change_1Byte_hobbit((LPVOID)0x00777AA4, 0x01, 0x00); // функция рендер света
}

void functions::renderEffects() noexcept {
	change_1Byte_hobbit((LPVOID)0x00777B88, 0x01, 0x00); // функция рендер эффектов
}

void functions::breakway() noexcept {
	change_1Byte_hobbit((LPVOID)0x00777B0C, 0x01, 0x00); // функция рендера падающего пути
}

void functions::boulderRun() noexcept {
	change_1Byte_hobbit((LPVOID)0x00777AFC, 0x01, 0x00); // функция рендер болдер рана
}

void functions::renderSkybox() noexcept {
	change_1Byte_hobbit((LPVOID)0x00777B5C, 0x01, 0x00); // функция рендера скайбокса
}

void functions::renderSavePedestal() noexcept {
	change_1Byte_hobbit((LPVOID)0x00777AF8, 0x01, 0x00); // функция рендера сохранялок
}

void functions::renderPushBoxes() noexcept {
	change_1Byte_hobbit((LPVOID)0x00777AF4, 0x01, 0x00); // функция рендера пушбоксов
}

void functions::renderRigidInstances() noexcept {
	change_1Byte_hobbit((LPVOID)0x00777A8C, 0x01, 0x00); // функция рендера rigidInstances
}

void functions::renderPlaySurface() noexcept {
	change_1Byte_hobbit((LPVOID)0x00777A98, 0x01, 0x00); // функция рендера ландшафта
}

void functions::renderGeometry() noexcept {
	change_1Byte_hobbit((LPVOID)0x0075D2CC, 0x01, 0x00); // функция рендера геометрии
}

void functions::renderHud() noexcept {
	change_1Byte_hobbit((LPVOID)0x0075EB7C, 0x00, 0x01); // функция рендера геометрии
}

void functions::increaseFOV() noexcept {
	plusA_float_hobbit((LPVOID)0x00772BF0, +0.1); //функция приближения камеры на 0.1
}

void functions::decreaseFOV() noexcept {
	plusA_float_hobbit((LPVOID)0x00772BF0, -0.1); //функция отдаления камеры на 0.1
}