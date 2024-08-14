#pragma once

#include "../../../Client/Module/ModuleManager.h"

class Mouse__feedHook : public Hook {
public:
	static inline void* oMouse_feed;

	static void oMouse_feedCallBack(__int64 a1, char mouseButton, char isDown, __int16 mouseX, __int16 mouseY, __int16 relativeMovementX, __int16 relativeMovementY, char a8) {
		bool cancel = false;
		if (moduleMgr->isInitialized())
			moduleMgr->getModule<ClickGui>()->onMouseUpdate((int)mouseButton, (bool)isDown, cancel);
		if (!cancel)
			return Memory::CallFunc<void, __int64, char, char, __int16, __int16, __int16, __int16, char>(
				oMouse_feed, a1, mouseButton, isDown, mouseX, mouseY, relativeMovementX, relativeMovementY, a8
			);
	}

	virtual void Initialize() override {
		Memory::CreateHook((void*)Memory::addSignature(SigManager::Mouse::feed), (void*)&oMouse_feedCallBack, &oMouse_feed, "Mouse::feed Hook");
	}
};