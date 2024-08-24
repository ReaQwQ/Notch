#pragma once
#pragma once
#include "../BaseHook.h"
#include "../../../Utils/Memory.h"
#include "../../../GameData.h"
#include "../../../Client/Module/ModuleManager.h"
#include "../../../Manager/SignatureManager.h"

#include <glm/glm/ext/matrix_clip_space.hpp>
#include <glm/glm/ext/matrix_relational.hpp>
#include <glm/glm/ext/matrix_transform.hpp>
#include <glm/glm/gtc/constants.hpp>
#include <glm/glm/mat4x4.hpp>
#include <glm/glm/trigonometric.hpp>
class LevelRendererPlayer__bobHurtHook : public Hook {
public:
	static inline void* LevelRendererPlayerbobHurt;
	static void LevelRendererPlayerbobHurtCallback(glm::mat4& matrix, float lerpT) {
		moduleMgr->onbobHurt(matrix, lerpT);
		return Memory::CallFunc<void, glm::mat4&, float>(LevelRendererPlayerbobHurt, matrix, lerpT);
	};
	virtual void Initialize() override {
		Memory::CreateHook((void*)Memory::addSignature(SigManager::LevelRendererPlayer::bobHurt), &LevelRendererPlayerbobHurtCallback, &LevelRendererPlayerbobHurt, "LevelRendererPlayer::bobHurt Hook");
	}
};