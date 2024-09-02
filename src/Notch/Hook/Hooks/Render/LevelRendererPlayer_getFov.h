#pragma once

#include "../BaseHook.h"

#include "../../../Client/Module/ModuleManager.h"
#include "../../../Manager/SignatureManager.h"

class LevelRendererPlayer__getFovHook : public Hook {
public:
	static inline void* LevelRendererPlayergetFov;
	static float LevelRendererPlayergetFovCallback(void* _this, float a, bool applyEffects) {
		static CustomFov* fMod = moduleMgr->getModule<CustomFov>();
		if (fMod && fMod->isEnabled())
			return fMod->fov;
		return Memory::CallFunc<float, void*, float, bool>(LevelRendererPlayergetFov, _this, a, applyEffects);;
	};
	virtual void Initialize() override {
		Memory::CreateHook(getSig("LevelRendererPlayer::getFov"), &LevelRendererPlayergetFovCallback, &LevelRendererPlayergetFov, "LevelRendererPlayer::getFov Hook");
	}
};