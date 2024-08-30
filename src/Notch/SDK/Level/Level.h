#pragma once

#include <iostream>
#include <optional>
#include "../Actor/Actor.h"
#include "PlayerListEntry.h"
#include "LevelData.h"

class Level {
public:
	BUILD_ACCESS(this, std::shared_ptr<LevelData>, levelData, 0xF8);
	BUILD_ACCESS(this, std::string, name, 0x6C8);
	virtual void playSoundEvent(std::string const& text, Vec3 const& pos, float vol, float pitch) {
		Memory::CallVFunc<163, void, std::string const&, Vec3 const&, float, float>(this, text, pos, vol, pitch);
	}
    virtual std::vector<Actor*, std::allocator<Actor*>> getRuntimeActorList() {
		std::vector<Actor*> list;
		Memory::CallVFunc<278, void, std::vector<Actor*>&>(this, list);
		return list;
    };
};
