#pragma once
#include <Windows.h>
#include <cstdarg>
#include "PacketID.h"
#include "PacketHandlerDispatcherInstance.h"
#include "../../Utils/Memory.h"
#include "../../Manager/SignatureManager.h"

class ConnectionRequest;
class ContainerID {};
class ActorRuntimeID {};
enum class LevelSoundEvent : int32_t;

union PacketHeader {
	struct {
		uint32_t packetId : 10;
		uint32_t recipientSubId : 2;
		uint32_t senderSubId : 2;
	};
	uint32_t packed;
};
static_assert(sizeof(PacketHeader) == 0x4);
class Packet {
public:
	uintptr_t** vTable;
public:
	int32_t priority = 2;
	int32_t reliability = 1;
	uint8_t subClientId = 0;
	bool isHandled = false;
	void* unknown = nullptr;
	PacketHandlerDispatcherInstance* handler = nullptr;
	int32_t compressibility = 0;
public:
	template <class T>
	bool isInstanceOf() {
		T packet;
		if (packet.vTable == this->vTable)
			return true;
		else
			return false;
	}
	uintptr_t** GetPacketVTable(PacketID id) {
		return (uint64_t**)(reinterpret_cast<uintptr_t>(this));
	}
public:
	virtual ~Packet() {};
	virtual PacketID getID();
	virtual std::string getName();
	virtual void write(void* stream);
	virtual void readExtended(void* stream);
	virtual bool allowBatch();
	virtual void read(void* stream);
};

class MinecraftPackets {
public:
	static std::shared_ptr<Packet> createPacket(PacketID id) {
		return reinterpret_cast<std::shared_ptr<Packet>(*)(PacketID)>(SigManager::MinecraftPackets::createPacket)(id);
	}
};
