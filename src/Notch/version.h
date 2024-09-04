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
};
