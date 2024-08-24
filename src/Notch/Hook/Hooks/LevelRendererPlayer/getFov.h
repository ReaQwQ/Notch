#pragma once

#include "../BaseHook.h"

#include "../../../Client/Module/ModuleManager.h"
#include "../../../Manager/SignatureManager.h"

class LevelRendererPlayer__getFovHook : public Hook {
public:
	static inline void* LevelRendererPlayergetFov;
	static float LevelRendererPlayergetFovCallback(void* _this, float a, bool applyEffects) {
		float fov = Memory::CallFunc<float, void*, float, bool>(LevelRendererPlayergetFov, _this, a, applyEffects);
		moduleMgr->onGetFov(fov);
		return fov;
	};
	virtual void Initialize() override {
		Memory::CreateHook((void*)Memory::addSignature(SigManager::LevelRendererPlayer::getFov), &LevelRendererPlayergetFovCallback, &LevelRendererPlayergetFov, "LevelRendererPlayer::getFov Hook");
	}
};