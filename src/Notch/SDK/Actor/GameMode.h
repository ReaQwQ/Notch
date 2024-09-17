#pragma once

#include "../../Utils/HMath.h"

#include "Actor.h"

#include <functional>

class InputMode;
class ItemStack;
class Block;
class Actor;

class GameMode {
    uintptr_t** VTable;
public:
    BUILD_ACCESS(this, class Player*, plr, getOffset("GameMode::player"));
    BUILD_ACCESS(this, float, LastBreakProgress, getOffset("GameMode::lastBreakProgress"))
    BUILD_ACCESS(this, float, BreakProgress, getOffset("GameMode::breakProgress"))
public:
    virtual ~GameMode();// 0 Destructor
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
    float getDestroyRate(Block const& block) {
        using getDestroyRate = float(__fastcall*)(GameMode*, Block const&);
        static getDestroyRate getDestroyRateFunc = reinterpret_cast<getDestroyRate>(getSig("GameMode::getDestroyRate"));
        return getDestroyRateFunc(this, block);
    }

    void baseUseItem(ItemStack& a1) {
        using GM_baseUseItem_t = void (*)(GameMode*, ItemStack&);
        static GM_baseUseItem_t baseUseItem = reinterpret_cast<GM_baseUseItem_t>(getSig("GameMode::baseUseItem"));  //"ItemUseInventoryTransaction::handle - destroy block failed, rending blocks around area to player"

        return baseUseItem(this, a1);
    }
};