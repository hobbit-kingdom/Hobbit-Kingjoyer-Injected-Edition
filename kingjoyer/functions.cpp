#include "functions.h"


#include "byte_functions.h"
#include "Randommod.h"
#include "PickupAll.h"

#include <memoryapi.h>
#include <tlhelp32.h>

void functions::developerMode() noexcept {
	change_1Byte_hobbit((LPVOID)0x007600E9, 0x01, 0x00); //������� ��������� ������ ������������
}

void functions::fps60() noexcept {
	change_2Byte_hobbit((LPVOID)0x006EFBDA, 0x4180, 0x4204); //������� FPS
}

void functions::renderVolumes() noexcept {
	change_1Byte_hobbit((LPVOID)0x00777B04, 0x01, 0x00); // ������� ������� �������
}

void functions::polyCache() noexcept {
	change_1Byte_hobbit((LPVOID)0x00778078, 0x01, 0x00); // ������� ������� ���������
}

void functions::renderLoadTriggers() noexcept {
	change_1Byte_hobbit((LPVOID)0x00777B18, 0x01, 0x00); // ������� ������� ����������� ���������
}

void functions::renderTriggers() noexcept {
	change_1Byte_hobbit((LPVOID)0x00777B1C, 0x01, 0x00); // ������� ������� ���������
}

void functions::renderWater() noexcept {
	change_1Byte_hobbit((LPVOID)0x00777B10, 0x01, 0x00); // ������� ������� ����
}

void functions::renderWeb() noexcept {
	change_1Byte_hobbit((LPVOID)0x00777B90, 0x01, 0x00); // ������� ������� �������
}

void functions::renderRopes() noexcept {
	change_1Byte_hobbit((LPVOID)0x00777B24, 0x01, 0x00); // ������� ������� �������
}

void functions::renderLeaves() noexcept {
	change_1Byte_hobbit((LPVOID)0x00777B80, 0x01, 0x00); // ������� ������ ��������� ������ ��������
}

void functions::renderChests() noexcept {
	change_1Byte_hobbit((LPVOID)0x00777AF0, 0x01, 0x00); // ������� ������ ��������
}

void functions::renderLevers() noexcept {
	change_1Byte_hobbit((LPVOID)0x00777AEC, 0x01, 0x00); // ������� ������ �������
}

void functions::renderBilbo() noexcept {
	change_1Byte_hobbit((LPVOID)0x00777AA0, 0x01, 0x00); // ������� ������ ������
}

void functions::renderLights() noexcept {
	change_1Byte_hobbit((LPVOID)0x00777AA4, 0x01, 0x00); // ������� ������ �����
}

void functions::renderEffects() noexcept {
	change_1Byte_hobbit((LPVOID)0x00777B88, 0x01, 0x00); // ������� ������ ��������
}

void functions::breakway() noexcept {
	change_1Byte_hobbit((LPVOID)0x00777B0C, 0x01, 0x00); // ������� ������� ��������� ����
}

void functions::boulderRun() noexcept {
	change_1Byte_hobbit((LPVOID)0x00777AFC, 0x01, 0x00); // ������� ������ ������ ����
}

void functions::renderSkybox() noexcept {
	change_1Byte_hobbit((LPVOID)0x00777B5C, 0x01, 0x00); // ������� ������� ���������
}

void functions::renderSavePedestal() noexcept {
	change_1Byte_hobbit((LPVOID)0x00777AF8, 0x01, 0x00); // ������� ������� ����������
}

void functions::renderPushBoxes() noexcept {
	change_1Byte_hobbit((LPVOID)0x00777AF4, 0x01, 0x00); // ������� ������� ���������
}

void functions::renderRigidInstances() noexcept {
	change_1Byte_hobbit((LPVOID)0x00777A8C, 0x01, 0x00); // ������� ������� rigidInstances
}

void functions::renderPlaySurface() noexcept {
	change_1Byte_hobbit((LPVOID)0x00777A98, 0x01, 0x00); // ������� ������� ���������
}

void functions::renderGeometry() noexcept {
	change_1Byte_hobbit((LPVOID)0x0075D2CC, 0x01, 0x00); // ������� ������� ���������
}