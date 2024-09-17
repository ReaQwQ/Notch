#include "ViewModel.h"

ViewModel::ViewModel() : Module("ViewModel", "Changes hand model", Category::RENDER, 0x0) {
	addEnumSetting("MainHand", "NULL", { "Right", "Left" }, &mainHand);
	addBoolCheck("Translate Hand", "NULL", &translate);
	addBoolCheck("Scale Hand", "NULL", &scale);
	addBoolCheck("Rotate Hand", "NULL", &rotate);
	addSlider<float>("TransX", "NULL", ValueType::FLOAT_T, &translateVec.x, -2.f, 2.f);
	addSlider<float>("TransY", "NULL", ValueType::FLOAT_T, &translateVec.y, -2.f, 2.f);
	addSlider<float>("TransZ", "NULL", ValueType::FLOAT_T, &translateVec.z, -5.f, 2.f);
	addSlider<float>("ScaleX", "NULL", ValueType::FLOAT_T, &scaleVec.x, -3.f, 3.f);
	addSlider<float>("ScaleY", "NULL", ValueType::FLOAT_T, &scaleVec.y, -2.f, 2.f);
	addSlider<float>("ScaleZ", "NULL", ValueType::FLOAT_T, &scaleVec.z, -2.f, 5.f);
	addSlider<float>("RotX", "NULL", ValueType::FLOAT_T, &rotateVec.x, 0.f, 2.f);
	addSlider<float>("RotY", "NULL", ValueType::FLOAT_T, &rotateVec.y, 0.f, 2.f);
	addSlider<float>("RotZ", "NULL", ValueType::FLOAT_T, &rotateVec.z, 0.f, 2.f);
	addSlider<float>("Angle", "Hand rotation angle", ValueType::FLOAT_T, &rotAngle, -6.3f, 6.3f);
	addBoolCheck("Reset", "Resets all the values to default", &reset);
}

void ViewModel::onTick(Actor* actor) {
	if (reset) {
		translateVec = Vec3(0, 0, 0);
		scaleVec = Vec3(1.f, 1.f, 1.f);
		rotateVec = Vec3(0.1f, 0.f, 0.f);
		rotAngle = 0.f;
		reset = false;
	}
}