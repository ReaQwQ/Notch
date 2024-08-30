#pragma once
#include "../../Utils/Memory.h"
class ScreenView {
public:
	BUILD_ACCESS(this, class ScreenController*, screenController, 0x38);
	BUILD_ACCESS(this, class VisualTree*, visualTree, 0x48);
}; //Size: 0x0080