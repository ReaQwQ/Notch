#pragma once

class LevelRenderer__renderLevelHook : public Hook {
public:
	static inline void* LevelRendererrenderLevel;
	static void LevelRendererrenderLevelCallback(void* lvl, ScreenContext* scn, void* unk) {
		moduleMgr->onLevelRender();

		return Memory::CallFunc<void, void*, ScreenContext*, void*>(LevelRendererrenderLevel, lvl, scn,unk);
	};
	virtual void Initialize() override {
		Memory::CreateHook((void*)Memory::addSignature(SigManager::LevelRenderer::renderLevel), &LevelRendererrenderLevelCallback, &LevelRendererrenderLevel, "LevelRenderer::renderLevel Hook");
	}
};