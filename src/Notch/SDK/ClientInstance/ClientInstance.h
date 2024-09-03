#pragma once
#include "../../Utils/Memory.h"
#include "../../Manager/Manager.h"
#include "../../version.h"

#include "GuiData.h"
#include "LoopbackPacketSender.h"
class ClientInstance {
public:
    uintptr_t** VTable;
    BUILD_ACCESS(this, class MinecraftGame*, minecraftGame, getOffset("ClientInstance::MinecraftGame"));
    BUILD_ACCESS(this, class Minecraft*, minecraft, getOffset("ClientInstance::Minecraft"));
    BUILD_ACCESS(this, LoopbackPacketSender*, loopbackPacketSender, getOffset("ClientInstance::LoopbackPacketSender"));
    BUILD_ACCESS(this, GuiData*, guiData, getOffset("ClientInstance::GuiData"));
public:
    glmatrixf* getrefdef() {
        return (glmatrixf*)((uintptr_t)(this) + 0x330);
    }
    auto getBlockSource() -> class BlockSource* {
        return Memory::CallVFunc<28, BlockSource*>(this);
    }

    auto getLocalPlayer() -> class LocalPlayer* {
        return Memory::CallVFunc<29, LocalPlayer*>(this);
    };
    bool isInGame() {
        return !Memory::CallVFunc<175, bool>((void*)this);
    }
    //LevelRenderer* getLevelRenderer() {
    //    return Memory::CallVFunc<198, LevelRenderer*>(this);
    //}
    void grabMouse() {
        int ver = version::GET_VERSION_INT();
        if (Manager::checkVer(ver, Manager::targetVersions1_21_X))
            Memory::CallVFunc<332, void>((void*)this);
        if (Manager::checkVer(ver, Manager::targetVersions1_21_2X))
                Memory::CallVFunc<333, void>((void*)this);
    };
    void releaseMouse() {
        int ver = version::GET_VERSION_INT();
        if (Manager::checkVer(ver, Manager::targetVersions1_21_X))
            Memory::CallVFunc<333, void>((void*)this);
        if (Manager::checkVer(ver, Manager::targetVersions1_21_2X))
            Memory::CallVFunc<334, void>((void*)this);
    };
    Vec2 getMousePos();
    float getFovX() {
         return (float)((uintptr_t)(this) + getOffset("ClientInstance::getFovX")); // X = 0x6F0
     }
     float getFovY() {
         return (float)((uintptr_t)(this) + getOffset("ClientInstance::getFovY")); // Y = 0x704
     }

     Vec2 getFov() {
         return Vec2(getFovX(), getFovY());
     }
};
