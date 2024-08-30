#pragma once

#include "../BaseHook.h"

#include "../../../Client/Module/ModuleManager.h"
#include "../../../Manager/SignatureManager.h"

#include "../../../SDK/Render/MinecraftUIRenderContext.h"
#include "../../../SDK/Render/ScreenView.h"

class UIScene__SetupAndRenderHook : public Hook {
public:
	static inline void* UIScene__SetupAndRender;
	static void UIScene__SetupAndRenderCallback(ScreenView* _this, MinecraftUIRenderContext* ctx) {
		return Memory::CallFunc<void, ScreenView*, MinecraftUIRenderContext*>(UIScene__SetupAndRender, _this, ctx);
	};
	virtual void Initialize() override {
		Memory::CreateHook((void*)Memory::addSignature(SigManager::UIScene::SetupAndRender), &UIScene__SetupAndRenderCallback, &UIScene__SetupAndRender, "LevelRendererPlayer::getFov Hook");
	}
};