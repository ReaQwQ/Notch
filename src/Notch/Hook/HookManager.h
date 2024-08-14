#pragma once
#include <iostream>
#include <vector>
#include <thread>

#include "Hooks/BaseHook.h"

class HookManager {
public:
	static void init();
	static void initImGui();
	static void RestoreImGui();

	static inline std::vector<Hook*> Hooks;
};