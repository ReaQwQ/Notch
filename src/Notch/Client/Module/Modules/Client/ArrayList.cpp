#include "ArrayList.h"

ArrayList::ArrayList() : Module("ArrayList", "A GUI use to enable/disable modules.", Category::CLIENT, 0x0) {
	addEnumSetting("Position", "Position of Arraylist", { "Center","Left","Right" }, &position);  // migi kara or center or hidari kara
	addBoolCheck("Top", "is Arraylist is Top", &top);
	addBoolCheck("shadow", "Text Shadow", &hasShadow);
	addSlider<float>("X Position", "X Position", ValueType::FLOAT_T, &spos.x, 0.f, 1.f);
	addSlider<float>("Y Position", "Y Position", ValueType::FLOAT_T, &spos.y, 0.f, 1.f);
	addSlider<float>("TextSize", "changes text size", ValueType::FLOAT_T, &textsize, 0.5f, 3.f);
	addSlider<float>("Height", "height gaps", ValueType::FLOAT_T, &height, 1.f, 2.f);
	addSlider<float>("Width", "width gaps", ValueType::FLOAT_T, &width, 1.f, 2.f);
	addEnumSetting("BG Color", "Set Background Color Type", { "Interface", "Rainbow", "Custom" }, &backgroundEnum);
	addColorPicker("Color", "BackGround Color", &backgroundCol);
	addEnumSetting("TEXT Color", "Set Text Color Type", { "Interface", "Rainbow", "Custom" }, &textEnum);
	addColorPicker("Text Color", "Text Color", &textCol);
	addBoolCheck("ShowKeybind", "draw key bind", &drawKeybind);
	addEnumSetting("KeybindMode", "change drawing keybind mode", { " ","[]","<>" }, &keymode);

}
void ArrayList::onImGuiRender(ImDrawList* drawlist) {
	if (drawlist == nullptr) return;
	if (Game.getLocalPlayer() == nullptr)return;

	if (modInfo.empty()) {
		for (Module* mod : *moduleMgr->getModuleList()) {
			modInfo.push_back(modules(mod, false, 0.f));
		}

	}

	auto io = ImGui::GetIO();

	UIColor white = UIColor(255, 255, 255, 255);
	Colors* cm = moduleMgr->getModule<Colors>();
	UIColor textColor;
	UIColor backGroundColor;

	switch (backgroundEnum) {
	case 0: {
		backGroundColor = cm->getColor();
		break;
	};
	case 1: {
		backGroundColor = cm->getRainbowColor();
		break;
	};
	case 2: {
		backGroundColor = backgroundCol;
		break;
	};
	}

	backGroundColor.a = backgroundCol.a;

	switch (textEnum) {
	case 0: {
		textColor = cm->getColor();
		break;
	};
	case 1: {
		textColor = cm->getRainbowColor();
		break;
	};
	case 2: {
		textColor = textCol;
		break;
	};
	}

	textColor.a = textCol.a;

	Vec2 winsize = Game.getGuiData()->realSize;
	Vec2 startPos = Vec2(winsize.x * spos.x, winsize.y * spos.y);
	float modHeight = ImGuiUtils::getTextHeight(textsize) * height;

	for (auto& it : modInfo) {
		it.persent = smoothLerp(it.mod->isEnabled() ? 1.f : -0.1f, it.persent, io.DeltaTime * 7.f);
		if (it.persent < 0.f || !it.mod->isVisible()) continue;

		std::string modKey;
		auto keyString = Utils::getKeybindName(it.mod->getKeybind());
		if (keyString != nullptr && keyString != "" && keyString != "Unknown") {
			if (keymode == 0) modKey = " " + std::string(keyString);
			else if (keymode == 1) modKey = " [" + std::string(keyString) + "]";
			else if (keymode == 2) modKey = " <" + std::string(keyString) + ">";
		}
		else modKey = "";
		std::string allText = std::string(it.mod->getModuleName());
		if (drawKeybind)allText += modKey;

		float allTextWidth = ImGuiUtils::getTextWidth(allText, textsize);
		float keyWidth = ImGuiUtils::getTextWidth(modKey, textsize);
		Vec4 modRect{};
		// canter
		if (position == 0) modRect = Vec4(startPos.x - ((allTextWidth * width + 1) * it.persent) / 2, startPos.y, startPos.x + ((allTextWidth * width + 1) * it.persent) / 2, startPos.y + modHeight * it.persent);
		// left
		else if (position == 1) modRect = Vec4(startPos.x, startPos.y, startPos.x + (allTextWidth * width + 1) * it.persent, startPos.y + modHeight * it.persent);
		// right
		else if (position == 2) modRect = Vec4(startPos.x - (allTextWidth * width + 1) * it.persent, startPos.y, startPos.x, startPos.y + modHeight * it.persent);
		ImGuiUtils::fillRectangle(modRect, backGroundColor, 0);
		std::string modText = it.mod->getModuleName();
		float m1 = allTextWidth * it.persent;

		Vec2 tpos = Vec2((modRect.x + modRect.z) / 2 - m1 / 2, (modRect.y + modRect.w) / 2);


		for (char s : modText) {
			std::string t(1, s);
			if (tpos.x > modRect.z)continue;
			ImGuiUtils::drawTextCenterY(tpos, t, textColor, textsize * it.persent, hasShadow, 0);
			tpos.x += ImGuiUtils::getTextWidth(t, textsize);
		}
		if (modKey != "" && drawKeybind)
			for (char s : modKey) {
				std::string t(1, s);
				if (tpos.x > modRect.z)continue;
				ImGuiUtils::drawTextCenterY(tpos, t, white, textsize * it.persent, hasShadow, 0);
				tpos.x += ImGuiUtils::getTextWidth(t, textsize);
			}
		if (top)
			startPos.y += modHeight * it.persent;
		else
			startPos.y -= modHeight * it.persent;
	}
}

void ArrayList::onEnable()
{
	for (auto it = moduleMgr->getModuleList()->begin(); it > moduleMgr->getModuleList()->end(); it++) {
		Module* mod = *it;

		modInfo.push_back(modules(mod, mod->isEnabled(), 1.f));
	}
}

void ArrayList::onDisable()
{
	modInfo.clear();
}