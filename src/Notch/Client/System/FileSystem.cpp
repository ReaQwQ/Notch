#include "FileSystem.h"

bool FileSystem::createFolder(std::string folderName) {
	fs::create_directory(StringUtil::combine(getRoamPath(), folderName));
	return true;
}

bool FileSystem::createAssetsFolder(std::string assetsFolderName) {
	fs::create_directory(StringUtil::combine(getClientPath(), xorstr_("\\"), assetsFolderName));
	return true;
}


void FileSystem::Initalize() {
	FileSystem::createFolder(xorstr_("Notch"));
	FileSystem::createAssetsFolder(xorstr_("Audios"));
	FileSystem::createAssetsFolder(xorstr_("Configs"));
	FileSystem::createAssetsFolder(xorstr_("Assets"));
	Network::downloadFile(xorstr_("inject.wav"), xorstr_("https://github.com/ReaQwQ/cdn.Nuke.pl.moment/raw/main/inject.wav"), xorstr_("Audios"));
	Network::downloadFile(xorstr_("uninject.wav"), xorstr_("https://github.com/ReaQwQ/cdn.Nuke.pl.moment/raw/main/uninject.wav"), xorstr_("Audios"));
};