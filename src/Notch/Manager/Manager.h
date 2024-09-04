#pragma once
#include <string>
#include <map>
#include "../version.h"
#include "../Utils/Memory.h"
#include "../Client/System/FileSystem.h"
void addOffset(const std::string& functionName, int offset);
void addSignature(const std::string& functionName, const std::string& signature);
int getOffset(const std::string& functionName);
void* getSig(const std::string& functionName);

class Manager {
public:
    static inline std::set<int> targetVersions1_21_X = { 12103, 12122 };
    static inline std::set<int> targetVersions1_21_2X = { 121203, 121211, 121221, 121231 };

    static bool checkVer(int version, std::set<int> versionList);
    static void init();
};
