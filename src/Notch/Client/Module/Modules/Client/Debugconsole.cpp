#include "Debugconsole.h"


DebugConsole g_DebugConsole;

DebugConsole::DebugConsole() : Module("DebugConsole", "A GUI used to display logs and accept user input.", Category::CLIENT, VK_TAB) {

}

DebugConsole::~DebugConsole() {}

void DebugConsole::toggle() {
    is_open = !is_open;
}

void DebugConsole::addLog(const std::string& log) {
    console_log.push_back(log);
    if (console_log.size() > max_lines) {
        console_log.erase(console_log.begin());
    }
}

bool DebugConsole::isVisible() const {
    return is_open;
}

void DebugConsole::render(ImDrawList* drawlist) {
    if (!is_open) return;

    ImGuiIO& io = ImGui::GetIO();
    const float padding = 10.0f;
    const float console_width = io.DisplaySize.x * 0.5f;
    const float console_height = io.DisplaySize.y * 0.5f;
    const Vec2 console_pos(io.DisplaySize.x * 0.25f, io.DisplaySize.y * 0.25f);

    // Console background
    Vec4 console_rect(console_pos.x, console_pos.y, console_pos.x + console_width, console_pos.y + console_height);
    ImGuiUtils::fillRectangle(console_rect, UIColor(0, 0, 0, 200));
    ImGuiUtils::drawRectangle(console_rect, UIColor(255, 255, 255, 100), 1.0f);

    // Render console log
    float y_offset = console_pos.y + padding;
    for (const auto& log : console_log) {
        ImGuiUtils::drawText(Vec2(console_pos.x + padding, y_offset), log, UIColor(255, 255, 255, 255), 1.0f);
        y_offset += ImGuiUtils::getTextHeight(1.0f) + 2.0f;
    }

    // Input box
    Vec4 input_rect(console_pos.x + padding, console_pos.y + console_height - ImGuiUtils::getTextHeight(1.0f) - padding * 2,
        console_pos.x + console_width - padding, console_pos.y + console_height - padding);
    ImGuiUtils::fillRectangle(input_rect, UIColor(50, 50, 50, 200));
    ImGuiUtils::drawText(Vec2(input_rect.x + 5, input_rect.y + 2), input_buffer, UIColor(255, 255, 255, 255), 1.0f);

    // Cursor blink
    blink_time += io.DeltaTime;
    if (fmod(blink_time, 1.0f) < 0.5f) {
        float cursor_x = input_rect.x + 5 + ImGuiUtils::getTextWidth(input_buffer, 1.0f);
        Vec4 cursor_rect(cursor_x, input_rect.y + 2, cursor_x + 2, input_rect.w - 2);
        ImGuiUtils::fillRectangle(cursor_rect, UIColor(255, 255, 255, 255));
    }
}

void DebugConsole::handleInput(int key, bool is_down) {
    if (!is_open || !is_down) return;

    if (key == VK_RETURN) {
        if (!input_buffer.empty()) {
            addLog("> " + input_buffer);
            processCommand(input_buffer);
            input_buffer.clear();
        }
    }
    else if (key == VK_BACK) {
        if (!input_buffer.empty()) {
            input_buffer.pop_back();
        }
    }
    else if (key >= 32 && key <= 126) { // Printable ASCII characters
        input_buffer += (char)key;
    }
}

void DebugConsole::processCommand(const std::string& command) {
    // Here you can add custom command processing logic
    // For now, we'll just echo the command
    addLog("Command received: " + command);
}

// Integration with Notch system
void DebugConsole::addNotchLog(const std::string& log, const std::string& type) {
    std::string formattedLog = "[" + type + "] " + log;
    addLog(formattedLog);
}