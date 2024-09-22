#pragma once
#include "../../Utils/Memory.h"
#include "../../Manager/Manager.h"
#include "../../version.h"

#include "GuiData.h"
#include "LoopbackPacketSender.h"
#include "LevelRenderer.h"
class ClientInstance {
public:
    uintptr_t** VTable;
    BUILD_ACCESS(this, class MinecraftGame*, minecraftGame, 0xC8);
    BUILD_ACCESS(this, class Minecraft*, minecraft, 0xD0);
    BUILD_ACCESS(this, LoopbackPacketSender*, loopbackPacketSender, 0xF0);
    BUILD_ACCESS(this, GuiData*, guiData, 0x558);
    BUILD_ACCESS(this, LevelRenderer*, LevelRender, 0xE0);
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

    Vec3 getOrigin() {
        return LevelRender->getOrigin();
    };

    void grabMouse() {
        if (Manager::checkVer(Manager::targetVersions1_21_X))
            Memory::CallVFunc<332, void>((void*)this);
        if (Manager::checkVer(Manager::targetVersions1_21_2X))
            Memory::CallVFunc<333, void>((void*)this);
        if (Manager::checkVer(Manager::targetVersions1_21_3X))
            Memory::CallVFunc<335, void>((void*)this);
    };
    void releaseMouse() {
        if (Manager::checkVer(Manager::targetVersions1_21_X))
            Memory::CallVFunc<333, void>((void*)this);
        if (Manager::checkVer(Manager::targetVersions1_21_2X))
            Memory::CallVFunc<334, void>((void*)this);
        if (Manager::checkVer(Manager::targetVersions1_21_3X))
            Memory::CallVFunc<336, void>((void*)this);
    };
    Vec2 getMousePos();
    float getFovX() {
         return (float)((uintptr_t)(this) + 0x6F0);
    }
    float getFovY() {
        return (float)((uintptr_t)(this) + 0x704);
    }

    Vec2 getFov() {
        return Vec2(getFovX(), getFovY());
    }
};
