#include "CustomFov.h"

CustomFov::CustomFov() : Module("CustomFov", "Customs Your Field Of View.", Category::RENDER, 0x0) {
	addSlider<float>("Fov", "Customized Field Of View", ValueType::FLOAT_T, &fov, 0.f, 179.9f);
};

void CustomFov::onGetFov(float& fovs) {
	fovs = fov;
}