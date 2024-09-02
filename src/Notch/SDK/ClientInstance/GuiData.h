#pragma once
#include "../../Manager/SignatureManager.h"
#include "../../Utils/HMath.h"
#include "../../Utils/TextFormat.h"
class GuiData {
public:
    BUILD_ACCESS(this, Vec2, realSize, getOffset("GuiData::realSize"));
    BUILD_ACCESS(this, Vec2, realSize2, getOffset("GuiData::realSize2"));
    BUILD_ACCESS(this, Vec2, scaledSize, getOffset("GuiData::scaledSize"));
    BUILD_ACCESS(this, float, guiScale, getOffset("GuiData::guiScale"));
    BUILD_ACCESS(this, float, scaleMultiplier, getOffset("GuiData::scaleMultiplier"));
    BUILD_ACCESS(this, int16_t, MousePosX, getOffset("GuiData::MousePosX"));
    BUILD_ACCESS(this, int16_t, MousePosY, getOffset("GuiData::MousePosY"));
public:
    void displayClientMessage(const std::string message, ...) {
        va_list arg;
        va_start(arg, message.c_str());
        char Message[400];
        vsprintf_s(Message, 400, message.c_str(), arg);
        const std::string MessagePointer = std::string(std::string(BOLD) + std::string(BLACK) + "[" + std::string(AQUA) + "Notch" + std::string(BLACK) + "] " + std::string(RESET) + Message);
        Memory::CallFunc<void, GuiData*, const std::string>(getSig("GuiData::displayClientMessage"), this, MessagePointer);
    };
};