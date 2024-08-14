#pragma once
#include "../../../GameData.h"
#include "../../../Client/Module/ModuleManager.h"
class arg {};

class Test__functionHook : public Hook {
public:
	static inline void* Test_functionHook;

	static void CallBack() {
}

	virtual void Initialize() override {
		Memory::CreateHook(Memory::addSignature(""), (void*)&CallBack, &Test_functionHook, xorstr_("FunctionName Hook"));
	}
};