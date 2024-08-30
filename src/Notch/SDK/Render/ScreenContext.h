#pragma once

#include <stack>
#include "../../Utils/Memory.h"
#include "../../Utils/ColorUtil.h"

class ScreenContext {
public:
	BUILD_ACCESS(this, MC_Color*, shaderColor, 0x30);
	BUILD_ACCESS(this, class Tessellator*, tess, 0xC0);

	struct MatrixPtr {
		//MVCLASS_FIELD(std::stack<D2D1::Matrix4x4F>, matrixStack, 0x40, 0x30, 0x30);
	};
	BUILD_ACCESS(this, MatrixPtr*, matrix, 0x18);

	inline static ScreenContext* instance3d = nullptr;
};