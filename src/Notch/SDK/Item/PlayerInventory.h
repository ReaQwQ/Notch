#pragma once
#include "../../Utils/Memory.h"
#include "Inventory.h"
class PlayerInventory {
public:
	BUILD_ACCESS(this, int, selectedSlot, getOffset("PlayerInventory::selectedSlot"));
	BUILD_ACCESS(this, Inventory*, inventory, getOffset("PlayerInventory::inventory"));
};