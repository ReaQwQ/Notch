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
		static ViewModel* vMod = moduleMgr->getModule<ViewModel>();
		if (vMod && vMod->isEnabled()) {
			if (vMod->translate)
				matrix = glm::translate<float>(matrix, glm::vec3(vMod->translateVec.x, vMod->translateVec.y, vMod->translateVec.z));
			if (vMod->scale)
				matrix = glm::scale<float>(matrix, glm::vec3(vMod->scaleVec.x, vMod->scaleVec.y, vMod->scaleVec.z));
			if (vMod->rotate)
				matrix = glm::rotate<float>(matrix, vMod->rotAngle, glm::vec3(vMod->rotateVec.x, vMod->rotateVec.y, vMod->rotateVec.z));
		}
		return Memory::CallFunc<void, glm::mat4&, float>(LevelRendererPlayerbobHurt, matrix, lerpT);
	};
	virtual void Initialize() override {
		Memory::CreateHook(getSig("LevelRendererPlayer::bobHurt"), &LevelRendererPlayerbobHurtCallback, &LevelRendererPlayerbobHurt, "LevelRendererPlayer::bobHurt Hook");
	}
};