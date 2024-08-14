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
	int32_t priority = 2, reliability = 1;
private:
	char pad_0x10[0x10];
public:
	PacketHandlerDispatcherInstance* dispatcher;
private:
	char pad_0x28[0x8];

public:
	std::string getName() {
		return *Memory::CallVFunc<2, std::string*>(this, std::string());
	}
	template <class T>
	bool isInstanceOf() {
		T packet;
		if (packet.vTable == this->vTable)
			return true;
		else
			return false;
	}
	PacketID getId() {
		return Memory::CallVFunc<1, PacketID>(this);
	}

	uintptr_t** GetPacketVTable(PacketID id) {
		auto packet = CreatePacket(id);
		return packet.get()->vTable;
	}

	std::shared_ptr<Packet> CreatePacket(PacketID id) {
		return Memory::CallFunc<std::shared_ptr<Packet>, void*, PacketID>((void*)Memory::FindSignatureModule(SigManager::MinecraftPackets::createPacket), (void*)this, id);
	}
};