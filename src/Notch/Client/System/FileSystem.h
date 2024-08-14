#pragma once
#include <windows.h>
#include <iostream>
#include <direct.h>
#include <string>
#include <iomanip>

#include "../../Utils/StringUtil.h"

#include <filesystem>

#include "Network.h"

#include "../../Libraries/Libraries.h"

namespace fs = std::filesystem;
class FileSystem {
public:
	static void Initalize();

	static bool createFolder(std::string folderName);
	static bool createAssetsFolder(std::string assetsFolderName);
	static std::string getRoamPath() {
		char* value;
		size_t size;

		_dupenv_s(&value, &size, xorstr_("APPDATA"));

		std::string roam = (value + std::string(xorstr_("\\..\\Local\\Packages\\Microsoft.MinecraftUWP_8wekyb3d8bbwe\\RoamingState\\")));
		return roam;
	}
	static std::string getClientPath() {
		return getRoamPath() + xorstr_("\\Notch");
	}
};