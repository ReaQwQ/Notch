#pragma once

class BlockLegacy {
	// BlockLegacy::getBlockItemId(void) | 0x1A6 (1.21.2)
	//BUILD_ACCESS(this, FNVString, translateName, 0x28); // tile.deepslate_diamond_ore
	BUILD_ACCESS(this, std::string, name, 0x50); // deepslate_diamond_ore
	//BUILD_ACCESS(this, FNVString, Namespace, 0x78); // minecraft
	BUILD_ACCESS(this, std::string, namespacedId, 0xA0); // minecraft:deepslate_diamond_ore
	BUILD_ACCESS(this, std::string, itemGroup, 0x140); // itemGroup.name.ore
};