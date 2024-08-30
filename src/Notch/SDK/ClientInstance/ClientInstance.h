#pragma once
#include "../../Utils/Memory.h"
#include "../../Manager/OffsetManager.h"
#include "../../Hook/HookManager.h"

#include "GuiData.h"
#include "LoopbackPacketSender.h"
class ClientInstance {
public:
    uintptr_t** VTable;
private:
    char padding_0[0xC0];
public:
    class MinecraftGame* minecraftGame; //0xC8
public:
    class Minecraft* minecraft; //0xD0
private:
    char padding_1[0x18];
public:
    LoopbackPacketSender* loopbackPacketSender; //0xF0
private:
    char padding_2[0x460];
public:
    GuiData* guiData; //0x558
public:
    //BUILD_ACCESS(guiData, int16_t, MousePosX, 0x6A);
    //BUILD_ACCESS(guiData, int16_t, MousePosY, 0x6C);

    glmatrixf* getrefdef() { // 1.21.2
        return (glmatrixf*)((uintptr_t)(this) + 0x330);
    }
    auto getBlockSource() -> class BlockSource* { // 1.21.2
        return Memory::CallVFunc<28, BlockSource*>(this);
    }

    auto getLocalPlayer() -> class LocalPlayer* { // 1.21.2
        return Memory::CallVFunc<29, LocalPlayer*>(this);
    };
    bool isInGame() { // 1.20.73
        return !Memory::CallVFunc<175, bool>((void*)this);
    }
    //LevelRenderer* getLevelRenderer() {
    //    return Memory::CallVFunc<198, LevelRenderer*>(this);
    //}
    void grabMouse() { // 1.21.2
        Memory::CallVFunc<332, void>((void*)this);
    };
    void releaseMouse() { // 1.21.2
        Memory::CallVFunc<333, void>((void*)this);
    };
    Vec2 getMousePos();
    float getFovX() { // 1.21.2
         return (float)((uintptr_t)(this) + 0x6F0); // X = 0x6F0
     }
     float getFovY() { // 1.21.2
         return (float)((uintptr_t)(this) + 0x704); // Y = 0x704
     }

     Vec2 getFov() {
         return Vec2(getFovX(), getFovY());
     }
};
