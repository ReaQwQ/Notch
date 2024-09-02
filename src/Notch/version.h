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
    static std::string join(const std::vector<std::string>& vec, const std::string& delimiter) {
        if (vec.empty()) return "";
        std::ostringstream oss;
        for (size_t i = 0; i < vec.size() - 1; ++i) {
            oss << vec[i] << delimiter;
        }
        oss << vec.back();
        return oss.str();
    }
    static std::string join(const std::vector<int>& vec, const std::string& delimiter) {
        if (vec.empty()) return "";
        std::ostringstream oss;
        for (size_t i = 0; i < vec.size() - 1; ++i) {
            oss << vec[i] << delimiter;
        }
        oss << vec.back();
        return oss.str();
    }
    static std::string join(const std::set<std::string>& vec, const std::string& delimiter) {
        if (vec.empty()) return "";
        std::ostringstream oss;
        auto it = vec.begin();
        while (std::next(it) != vec.end()) {
            oss << *it << delimiter;
            ++it;
        }
        oss << *it;
        return oss.str();
    }

    static std::string join(const std::set<int>& vec, const std::string& delimiter) {
        if (vec.empty()) return "";
        std::ostringstream oss;
        auto it = vec.begin();
        while (std::next(it) != vec.end()) {
            oss << *it << delimiter;
            ++it;
        }
        oss << *it;
        return oss.str();
    }
};
