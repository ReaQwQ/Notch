#pragma once

#include <stack>
#include "../../Utils/Memory.h"
#include "../../Utils/ColorUtil.h"

class ScreenContext {
public:
	BUILD_ACCESS(this, MC_Color*, shaderColor, getOffset("ScreenContext::shaderColor"));
	BUILD_ACCESS(this, class Tessellator*, tess, getOffset("ScreenContext::tessellator"));

	BUILD_ACCESS(this, class MatrixPtr*, matrix, getOffset("ScreenContext::matrix"));

	inline static ScreenContext* instance3d = nullptr;
};