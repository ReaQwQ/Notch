#pragma once
#include "../../Manager/SignatureManager.h"
#include "../../Utils/HMath.h"
#include "../../Utils/TextFormat.h"
class GuiData {
public:
    char pad_0000[48]; //0x0000
    Vec2 realSize; //0x0030
    Vec2 realSize2; //0x0038
    Vec2 scaledSize; //0x0040
    char pad_0048[4]; //0x0048
    float guiScale; //0x004C
    float scaleMultiplier; //0x0050
    char pad_0x0050[22];
public:
    int16_t MousePos[1]; // X: 0x6A Y: 0x6C
public:
    void displayClientMessage(const std::string message, ...) {
        va_list arg;
        va_start(arg, message.c_str());
        char Message[400];
        vsprintf_s(Message, 400, message.c_str(), arg);
        const std::string MessagePointer = std::string(std::string(BOLD) + std::string(BLACK) + "[" + std::string(AQUA) + "Notch" + std::string(BLACK) + "] " + std::string(RESET) + Message);
        Memory::CallFunc<void, GuiData*, const std::string>(Memory::addSignature(SigManager::GuiData::displayClientMessage), this, MessagePointer);
    };
};