#pragma once

#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <Windows.h>

namespace path_navigator
{
	void Toggle(HWND gameWindow) noexcept;
	void Update(HWND gameWindow) noexcept;
	void Shutdown() noexcept;

	bool IsActive() noexcept;
	bool IsCalibrated() noexcept;
	int GetCurrentWaypointIndex() noexcept;
	int GetPathPointCount() noexcept;
	const char* GetStatusText() noexcept;
}
