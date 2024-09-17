#pragma once

#include <iostream>
#include <optional>
#include "../Actor/Actor.h"
class Level {
public:
    std::vector<Actor*> getRuntimeActorList() {
		std::vector<Actor*> listOut;
		int version = version::GET_VERSION_INT();
		if (Manager::checkVer(version, Manager::targetVersions1_21_X))
			Memory::CallVFunc<278, void, decltype(&listOut)>(this, &listOut);
		else if (Manager::checkVer(version, Manager::targetVersions1_21_2X)) 
			Memory::CallVFunc<279, void, decltype(&listOut)>(this, &listOut);
		return listOut;
    };

	class HitResult* getHitResult() {
		int version = version::GET_VERSION_INT();
		if (Manager::checkVer(version, Manager::targetVersions1_21_X))
			return Memory::CallVFunc<288, HitResult*>(this);
		else if (Manager::checkVer(version, Manager::targetVersions1_21_2X))
			return Memory::CallVFunc<289, HitResult*>(this);
	};
	class HitResult* getLiquidHitResult() {
		int version = version::GET_VERSION_INT();
		if (Manager::checkVer(version, Manager::targetVersions1_21_X))
			return Memory::CallVFunc<289, HitResult*>(this);
		else if (Manager::checkVer(version, Manager::targetVersions1_21_2X))
			return Memory::CallVFunc<290, HitResult*>(this);
	};
};
