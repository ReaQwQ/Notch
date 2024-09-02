#include "version.h"
std::string version::GET_VERSION(bool patchVersion) {
    char filePath[MAX_PATH];
    if (GetModuleFileNameExA(GetCurrentProcess(), nullptr, filePath, MAX_PATH)) {
        DWORD size = GetFileVersionInfoSizeA(filePath, nullptr);
        BYTE* ver = new BYTE[size];
        VS_FIXEDFILEINFO* pFileInfo;
        if (GetFileVersionInfoA(filePath, 0, size, ver)) {
            if (VerQueryValue(ver, TEXT("\\"), (LPVOID*)&pFileInfo, nullptr)) {
                std::ostringstream oss;
                oss << HIWORD(pFileInfo->dwFileVersionMS) << '.'
                    << LOWORD(pFileInfo->dwFileVersionMS) << '.'
                    << HIWORD(pFileInfo->dwFileVersionLS);
                if (patchVersion)
                    oss << '.' << LOWORD(pFileInfo->dwFileVersionLS);
                return oss.str();
            }
        }
    }
    return "Unknown";
}

int version::GET_VERSION_INT(bool patchVersion) {
    std::string str = GET_VERSION(patchVersion);
    str.erase(std::remove(str.begin(), str.end(), '.'), str.end());
    return std::stoi(str);
}
