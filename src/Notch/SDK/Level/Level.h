#pragma once

#include <iostream>
#include <optional>
#include "../Actor/Actor.h"
class Level {
public:
    virtual std::vector<Actor*, std::allocator<Actor*>> getRuntimeActorList() {
		std::vector<Actor*> list;
		Memory::CallVFunc<278, void, std::vector<Actor*>&>(this, list);
		return list;
    };
};
