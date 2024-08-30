#pragma once
#include <string_view>
#include <optional>
#include "../Block/BlockLegacy.h"
#include "Item.h"

class ItemStack {
public:
	virtual void destructor(); // 0
	virtual void reinit(std::basic_string_view<char, std::char_traits<char>>, int, int); // 1
	virtual void reinit(const BlockLegacy&, int); // 2
	virtual void reinit(const Item&, int, int); // 3
	virtual void setNull(std::optional<std::string>); // 4
	virtual std::string toString() const; // 5
	virtual std::string toDebugString() const; // 6
};