#pragma once

#include "../BaseHook.h"

#include "../../../Client/Module/ModuleManager.h"
#include "../../../Manager/SignatureManager.h"

#include "../../../SDK/Render/MinecraftUIRenderContext.h"
#include "../../../SDK/Render/ScreenView.h"

class ScreenView__SetupAndRenderHook : public Hook {
public:
	static inline void* ScreenView__SetupAndRender;
	static inline void* MinecraftUIRenderContext__drawImage;
	static inline void* MinecraftUIRenderContext__drawText;
	static void MinecraftUIRenderContext__drawImageCallback(TexturePtr const& texture, Vec2 const& pos, Vec2 const& size, Vec2 const& uvPos, Vec2 const& uvSize) {
		Memory::CallFunc<void, TexturePtr const&, Vec2 const&, Vec2 const&, Vec2 const&, Vec2 const&>(MinecraftUIRenderContext__drawImage, texture, pos, size, uvPos, uvSize);
	};
	static void MinecraftUIRenderContext__drawTextCallback(class Font* font, const float* pos, std::string const& text, MC_Color const& color, float alpha, ui::TextAlignment textAlignment, TextMeasureData const& textMeasureData, CaretMeasureData const& caretMeasureData) {
		Memory::CallFunc<void, Font*, const float*, std::string const&, MC_Color const&, float, ui::TextAlignment, TextMeasureData const&, CaretMeasureData>(MinecraftUIRenderContext__drawText, font, pos, text, color, alpha, textAlignment, textMeasureData, caretMeasureData);
	};
	static void ScreenView__SetupAndRenderCallback(ScreenView* _this, MinecraftUIRenderContext* ctx) {
		moduleMgr->onPreRender(ctx);

		static bool hookedRenderCtx = false;
		if (!hookedRenderCtx) {
			auto VTable = *(uintptr_t**)ctx;
			Memory::CreateHook((void*)VTable[7], &MinecraftUIRenderContext__drawImageCallback, &MinecraftUIRenderContext__drawImage, "MinecraftUIRenderContext::drawImage Hook");
			Memory::CreateHook((void*)VTable[5], &MinecraftUIRenderContext__drawTextCallback, &MinecraftUIRenderContext__drawText, "MinecraftUIRenderContext::drawText Hook");
			hookedRenderCtx = true;
		}

		Memory::CallFunc<void, ScreenView*, MinecraftUIRenderContext*>(ScreenView__SetupAndRender, _this, ctx);

		moduleMgr->onPostRender(ctx);
	};
	virtual void Initialize() override {
		Memory::CreateHook((void*)Memory::addSignature(SigManager::ScreenView::SetupAndRender), &ScreenView__SetupAndRenderCallback, &ScreenView__SetupAndRender, "ScreenView::SetupAndRender Hook");
	}
};