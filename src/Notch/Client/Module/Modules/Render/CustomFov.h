#pragma once
#include "../Module.h"

class CustomFov : public Module {
public:
	float fov = 165.f;
	CustomFov();
	virtual void onGetFov(float& fov) override;
};