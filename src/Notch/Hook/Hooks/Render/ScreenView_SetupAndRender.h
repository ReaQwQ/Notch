#pragma once

#include "../BaseHook.h"

#include "../../../Client/Module/ModuleManager.h"
#include "../../../Manager/SignatureManager.h"

#include "../../../SDK/Render/MinecraftUIRenderContext.h"
#include "../../../SDK/Render/ScreenView.h"

class ScreenView__SetupAndRenderHook : public Hook {
public:
	static inline void* ScreenView__SetupAndRender;
	static void ScreenView__SetupAndRenderCallback(ScreenView* _this, MinecraftUIRenderContext* ctx) {
		return Memory::CallFunc<void, ScreenView*, MinecraftUIRenderContext*>(ScreenView__SetupAndRender, _this, ctx);
	};
	virtual void Initialize() override {
		Memory::CreateHook((void*)Memory::addSignature(SigManager::ScreenView::SetupAndRender), &ScreenView__SetupAndRenderCallback, &ScreenView__SetupAndRender, "ScreenView::SetupAndRender Hook");
	}
};