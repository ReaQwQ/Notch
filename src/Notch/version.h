#pragma once
#include <windows.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <ostream>
#include <cstdarg>
#include <psapi.h>
#include <string>
#include <vector>
#include <set>

class version {
public:
    static std::string GET_VERSION(bool patchVersion = true);
    static int GET_VERSION_INT(bool patchVersion = true);
    static inline std::vector<std::string> supportedVersion = {
        "1.21.2.2",
        "1.21.20.3",
        "1.21.21.1",
        "1.21.22.1"
    };
    static inline std::vector<int> supportedVersionint = {
        12122,
        121203,
        121211,
        121221
    };
};
