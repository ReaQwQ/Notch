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
class MinecraftPackets {
public:
	static std::shared_ptr<class Packet> createPacket(PacketID id) {
		return reinterpret_cast<std::shared_ptr<Packet>(*)(PacketID)>(SigManager::MinecraftPackets::createPacket)(id);
	}
};

class Packet {
public:
	BUILD_ACCESS(this, uintptr_t**, vTable, 0x0);
public:
	int32_t priority = 2;
	int32_t reliability = 1;
	uint8_t subClientId = 0;
	bool isHandled = false;
	void* unknown = nullptr;
	PacketHandlerDispatcherInstance* handler = nullptr;
	int32_t compressibility = 0;
public:
	uintptr_t** GetPacketVTable(PacketID id) {
		auto packet = MinecraftPackets::createPacket(id);
		return packet.get()->vTable;
	}
public:
	virtual ~Packet() {};
	virtual PacketID getID() { 
		return Memory::CallVFunc<1, PacketID>(this); 
	};
	std::string getName() {
		return *Memory::CallVFunc<2, std::string*>(this);
	}
	virtual void write(void* stream) {
		return Memory::CallVFunc<3, void, void*>(this, stream);
	};
	virtual void readExtended(void* stream) {
		return Memory::CallVFunc<4, void, void*>(this, stream);
	};
	virtual bool allowBatch() {
		return Memory::CallVFunc<5, bool>(this);
	};
	virtual void _read(void* stream) {
		return Memory::CallVFunc<6, void, void*>(this, stream);
	};
};