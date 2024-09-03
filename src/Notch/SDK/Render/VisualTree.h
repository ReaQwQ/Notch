#pragma once
#include "../../Utils/Memory.h"
#include "../../Manager/Manager.h"
class VisualTree {
public:
	BUILD_ACCESS(this, class UIControl*, rootControl, getOffset("VisualTree::rootControl"));
};