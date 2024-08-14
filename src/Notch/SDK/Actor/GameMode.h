#pragma once

#include "../../Utils/HMath.h"

#include "Actor.h"

#include <functional>

class InputMode;
class ItemStack;
class Block;
class Actor;

class GameMode {
private:
    virtual void Destructor();// 0 Destructor
public:
    virtual void startDestroyBlock(Vec3 const& pos, unsigned char blockSide, bool auth); // 1
    virtual void destroyBlock(Vec3 const& a1, unsigned char a2, bool auth); // 2
    virtual void continueDestroyBlock(Vec3 const& a1, unsigned char a2, Vec3 const& a3, bool& a4); // 3
    virtual void stopDestroyBlock(Vec3 const& a1); // 4
    virtual void startBuildBlock(Vec3 const& a1, unsigned char a2, bool auth); // 5
    virtual void buildBlock(Vec3 const& a1, unsigned char a2, bool auth); // 6
    virtual void continueBuildBlock(Vec3 const& a1, unsigned char a2); // 7
    virtual void stopBuildBlock(); // 8
    virtual void tick(); // 9
    virtual void getPickRange(InputMode const& a1, bool a2); // 10
    virtual void useItem(ItemStack& a1); // 11
    virtual void useItemOn(ItemStack& a1, Vec3 const& a2, unsigned char a3, Vec3 const& a4, Block const* a5); // 12
    virtual void interact(Actor* a1, Vec3 const& a2); // 13
    virtual void attack(class Actor& a1); // 14
    virtual void releaseUsingItem(); // 15
    virtual void setTrialMode(bool a1); // 16
    virtual void isInTrialMode(); // 17
    virtual void registerUpsellScreenCallback(std::function<void> a3); // 18
public:
    float getDestroyRate(Block* block) {
        using getDestroyRateFunc = float(__fastcall*)(GameMode*, Block*);
        static getDestroyRateFunc Func = (getDestroyRateFunc)(Memory::FindSignatureModule("48 89 5C 24 18 57 48 83 EC 30 48 8B F9 0F 29"));
        return Func(this, block);
    }
    __int64 baseUseItem(ItemStack& a1) {
        return Memory::CallFunc<__int64, void*, ItemStack&>(Memory::addSignature("48 89 5C 24 10 48 89 7C 24 18 55 48 8D 6C 24 D0 48 81 EC 30 01 00 00 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 45 20 48 8B DA 48 8B F9 48 C7 45 C8 00 00 00 00 48 8D 4D C8 E8 ?? ?? ?? ?? 90 48"), (void*)this, a1);
    };
};