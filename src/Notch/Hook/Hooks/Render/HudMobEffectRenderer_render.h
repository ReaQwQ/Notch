#pragma once
#include "../../../SDK/Render/UIControl.h"
class HudMobEffectRenderer__renderHook : public Hook {
public:
	static inline void* detour;
	static void renderDetour(void* _this, void* renderContext, void* client, void* owner,int pass, void* renderAABB) {
		if (!moduleMgr->isInitialized())
			return Memory::CallFunc<void, void*, void*, void*, void*, int, void*>(detour, _this, renderContext, client, owner, pass, renderAABB);
		if (moduleMgr->getModule<PotionHud>()->isEnabled())
			return;
		return Memory::CallFunc<void, void*, void*, void*, void*, int, void*>(detour, _this, renderContext, client, owner, pass, renderAABB);
	}
	virtual void Initialize() override {
		Memory::CreateHook(getSig("HudMobEffectRenderer::render"), (void*)&renderDetour, &detour, "HudMobEffectRenderer::render Hook");
	}
};