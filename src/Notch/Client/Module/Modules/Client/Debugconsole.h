#pragma once
#include <vector>
#include <string>
#include "../../../../Utils/ImGuiUtils.h"
#include "../Module.h"
#include "../../ModuleManager.h"
#include "../../../Config/ConfigManager.h"
#include "../../../../Libraries/Libs/ImFX/imfx.h"

#include "../../../../GameData.h"
#include "../../../../Utils/Input.h"
class DebugConsole : public Module {
private:
    std::vector<std::string> console_log;
    std::string input_buffer;
    bool is_open = false;
    const int max_lines = 100; // Maximum number of lines to display
    float blink_time = 0.0f;

public:
    DebugConsole();
    ~DebugConsole();

    void toggle();
    void addLog(const std::string& log);
    void render(ImDrawList* drawlist);
    void handleInput(int key, bool is_down);
    bool isVisible() const;
    void addNotchLog(const std::string& log, const std::string& type);
    void processCommand(const std::string& command);
};

// Global instance
extern DebugConsole g_DebugConsole;