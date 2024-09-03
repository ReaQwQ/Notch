#pragma once

#include <iostream>
#include <optional>
#include "../Actor/Actor.h"
class Level {
public:
    std::vector<Actor*> getRuntimeActorList() {
		std::vector<Actor*> list;
		int version = version::GET_VERSION_INT();
		if (Manager::checkVer(version, Manager::targetVersions1_21_X))
			Memory::CallVFunc<278, void, std::vector<Actor*>&>(this, list);
		else if (Manager::checkVer(version, Manager::targetVersions1_21_2X)) 
			Memory::CallVFunc<279, void, std::vector<Actor*>&>(this, list);
		return list;
    };
};
