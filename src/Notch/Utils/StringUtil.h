#pragma once
#pragma once
#include <string>
class StringUtil {
public:
    static std::string combine() {
        return "";
    }

    template<typename First, typename... Rest>
    static std::string combine(First&& first, Rest&&... rest) {
        return std::forward<First>(first) + combine(std::forward<Rest>(rest)...);
    }
};