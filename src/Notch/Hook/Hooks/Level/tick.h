#pragma once
#include "../BaseHook.h"
#include "../../../Utils/Memory.h"
#include "../../../GameData.h"
#include "../../../Client/Module/ModuleManager.h"
#include "../../../Manager/SignatureManager.h"
class Level__tickHook : public Hook {
public:
	static inline void* oLevelTick;
	static void LevelTickCallback(void* level) {
		if (Game.getLocalPlayer() != nullptr && Game.getLocalPlayer()->getGameMode() != nullptr) moduleMgr->onNormalTick(Game.getLocalPlayer());
		return Memory::CallFunc<void, void*>(oLevelTick, level);
	};
	virtual void Initialize() override {
		Memory::CreateHook((void*)Memory::addSignature(SigManager::Level::tick), &LevelTickCallback, &oLevelTick, "Level::Tick Hook");
	}
};