#define _CRT_SECURE_NO_WARNINGS

// Skinchanger helpers: copies a selected skin from ./SKINS into the game's
// ./Common/Bilbo folder, and renders the per-skin "Apply" buttons. Split out
// of gui.cpp.

#include "gui_internal.h"

#include "../imgui/imgui.h"

#include <iostream>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

static bool copyAndRenameFile(const std::string& sourceFile) {
	try {
		fs::path sourcePath = "./SKINS/" + sourceFile;
		fs::path destDir = "./Common/Bilbo/";

		if (!fs::exists(sourcePath)) {
			std::cerr << "Source file does not exist: " << sourcePath << std::endl;
			return false;
		}

		std::string fileExtension = sourcePath.extension().string();
		fs::path destFilePath = destDir / ("BILBO[D]" + fileExtension);

		fs::create_directories(destDir);

		if (fs::exists(destFilePath)) {
			fs::remove(destFilePath);
			std::cout << "Existing file deleted: " << destFilePath << std::endl;
		}

		fs::copy_file(sourcePath, destFilePath, fs::copy_options::overwrite_existing);
		std::cout << "File copied and renamed to: " << destFilePath << std::endl;
		return true;
	}
	catch (const fs::filesystem_error& e) {
		std::cerr << "Filesystem error: " << e.what() << std::endl;
		return false;
	}
}

void displaySkinButtons(bool lang)
{
	fs::path skinsDir = "./SKINS";

	if (!fs::exists(skinsDir)) {
		ImGui::Text(lang ? "SKINS directory does not exist." : (const char*)u8"папка SKINS не найдена");
		return;
	}

	if (fs::is_empty(skinsDir)) {
		ImGui::Text(lang ? "SKINS directory is empty." : (const char*)u8"папка SKINS пуста.");
		return;
	}

	for (const auto& entry : fs::directory_iterator(skinsDir))
	{
		if (entry.is_regular_file())
		{
			fs::path filePath = entry.path();

			if (filePath.extension() == ".xbmp" || filePath.extension() == ".XBMP")
			{
				std::string fileName = filePath.stem().string();

				ImGui::Text("%s", fileName.c_str());
				ImGui::SameLine();

				if (ImGui::Button((lang ? "Apply##" : (const char*)u8"Принять##" + fileName).c_str()))
					copyAndRenameFile(filePath.filename().string());

			}
		}
	}
}
