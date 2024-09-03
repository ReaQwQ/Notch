#pragma once
#include "../../Utils/Memory.h"
#include "../../Manager/Manager.h"
class ScreenView {
public:
	BUILD_ACCESS(this, class ScreenController*, screenController, getOffset("ScreenView::ScreenController"));
	BUILD_ACCESS(this, class VisualTree*, visualTree, getOffset("ScreenView::VisualTree"));
}; //Size: 0x0080