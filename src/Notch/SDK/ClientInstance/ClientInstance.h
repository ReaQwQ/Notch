#pragma once
#include "../../Utils/Memory.h"
#include "../../Manager/OffsetManager.h"

#include "GuiData.h"
#include "LoopbackPacketSender.h"

class ClientInstance {
public:
    uintptr_t** VTable;
public:
    BUILD_ACCESS(this, class MinecraftGame*, minecraftGame, OffsetManager::ClientInstance::mcgame);
    BUILD_ACCESS(this, class Minecraft*, minecraft, OffsetManager::ClientInstance::minecraft);
    BUILD_ACCESS(this, LoopbackPacketSender*, loopbackPacketSender, OffsetManager::ClientInstance::packetSender);
    BUILD_ACCESS(this, GuiData*, guiData, OffsetManager::ClientInstance::guiData);
public:
    glmatrixf* getrefdef() {
        return (glmatrixf*)((uintptr_t)(this) + 0x330);
    }
    auto getLocalPlayer() -> class Actor* {
        return Memory::CallVFunc<29, Actor*>(this);
    };
    bool isInGame() {
        return !Memory::CallVFunc<175, bool>((void*)this);
    }
    //LevelRenderer* getLevelRenderer() {
    //    return Memory::CallVFunc<198, LevelRenderer*>(this);
    //}
    void grabMouse() {
        Memory::CallVFunc<332, void>((void*)this);
    };
    void releaseMouse() {
        Memory::CallVFunc<333, void>((void*)this);
    };
     Vec2 getMousePos() {
         Vec2 mousePos = Vec2(guiData->MousePos[0], guiData->MousePos[1]);
         return mousePos;
     }
     float getFovX() {
         return (float)((uintptr_t)(this) + 0x6F0); // X = 0x6F0
     }
     float getFovY() {
         return (float)((uintptr_t)(this) + 0x704); // Y = 0x704
     }

     Vec2 getFov() {
         return Vec2(getFovX(), getFovY());
     }
};