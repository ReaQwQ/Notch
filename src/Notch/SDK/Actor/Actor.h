#pragma once

#include "../../Utils/HMath.h"
#include "../../Utils/ColorUtil.h"
#include "../../Utils/TextFormat.h"
#include "../../Manager/SignatureManager.h"
#include "../../Manager/Manager.h"
#include "../../Utils/Memory.h"

#include "GameMode.h"
#include "../Level/Level.h"
#include "../Item/PlayerInventory.h"
#include <bitset>
#include "ActorFlags.h"
class StateVector {
public:
	Vec3 pos;
	Vec3 oldPos;
	Vec3 velocity;
};
struct EntityId {
	uint32_t value;
};

class EntityRegistry;

struct EntityContext {
	EntityRegistry* registry;
	EntityId id;

};
class Actor {
public:
	BUILD_ACCESS(this, StateVector*, stateVector, getOffset("Actor::StateVectorComponent"));
	BUILD_ACCESS(this, Level*, level, getOffset("Actor::level"));
	BUILD_ACCESS(this, class TextHolder*, playerName, getOffset("Actor::playerName"));
public:
	virtual bool getStatusFlag(ActorFlags) const; // 0
	virtual void setStatusFlag(ActorFlags, bool); // 1

	std::string getNameTag() {
		return *Memory::CallFunc<std::string*, void*>(getSig("Actor::getNameTag"), (void*)this);
	}

	void jumpFromGround() {
		Memory::CallFunc<void, Actor*>(getSig("SimulatedPlayer::simulateJump"), this);
	}
	void playEmote(const std::string pieceID, bool Message) {
		Memory::CallFunc<void, Actor*, const std::string, bool>(getSig("Actor::playEmote"), this, pieceID, Message);
	};
	Vec3 getPosition() {
		return this->stateVector->pos;
	};
	Vec3 getPositionOld() {
		return this->stateVector->oldPos;
	};
	void setPosition(Vec3 pos) {
		this->stateVector->pos = pos;
	};
	float getSpeedPerSecond() {
		Vec3 targetPos = this->getPosition();
		Vec3 targetPosOld = this->getPositionOld();
		float hVel = sqrtf(((targetPos.x - targetPosOld.x) * (targetPos.x - targetPosOld.x)) + ((targetPos.z - targetPosOld.z) * (targetPos.z - targetPosOld.z)));
		return hVel * 20;
	};
	virtual void lerpMotion(Vec3 motionVector) {
		this->stateVector->velocity.x = motionVector.x;
		this->stateVector->velocity.y = motionVector.y;
		this->stateVector->velocity.z = motionVector.z;
	};
	Level* getLevel() {
		return this->level;
	}
};

class Player : public Actor {
public:
	BUILD_ACCESS(this, GameMode*, gamemode, getOffset("Player::gamemode"));
	BUILD_ACCESS(this, PlayerInventory*, Supplies, getOffset("Player::getSupplies"));

	GameMode* getGameMode() {
		return this->gamemode;
	}
	void displayClientMessage(std::string Message, ...) {
		va_list arg;
		va_start(arg, Message.c_str());
		char message[400];
		vsprintf_s(message, 400, Message.c_str(), arg);
		std::string* MessagePointer = new std::string(std::string(BOLD) + std::string(BLACK) + "[" + std::string(AQUA) + "Notch" + std::string(BLACK) + "] " + std::string(RESET) + message);
		int version = version::GET_VERSION_INT();
		if (version == 1212) Memory::CallVFunc<213, void, std::string*>((void*)this, MessagePointer);
		else if (version > 1212) {
			std::optional<std::string> opt = {};
			Memory::CallVFunc<210, void, std::string*>((void*)this, MessagePointer, opt);
		}
	};
};

class LocalPlayer : public Player {
public:
};