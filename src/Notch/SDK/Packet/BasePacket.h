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
	virtual int getId(void) { return 0x0; }

	uintptr_t** GetPacketVTable(PacketID id) {
		return (uint64_t**)(reinterpret_cast<uintptr_t>(this) + 0x0);
	}
};

class MinecraftPackets {
public:
	static std::shared_ptr<Packet> CreatePacket(int packetId) {
		using createPacket = std::shared_ptr<Packet>(__cdecl*)(int);
		static createPacket createPacketFunc = 0x0;
		if (!createPacketFunc) {
			createPacketFunc = (createPacket)Memory::ResolveRef(Memory::FindSignatureModule(SigManager::MinecraftPackets::createPacket));
		}
		return createPacketFunc(packetId);
	}

	static std::shared_ptr<Packet> CreatePacket(PacketID packetId) {
		return CreatePacket((int)packetId);
	}
private:
	template<typename T>
	static std::shared_ptr<T> CreatePacket(int packetId) {
		return std::reinterpret_pointer_cast<T>(CreatePacket(packetId));
	}
public:
	template<typename T>
	static std::shared_ptr<T> CreatePacket() {
		T instance;
		int packetId = instance.getId();
		return std::reinterpret_pointer_cast<T>(CreatePacket(packetId));
	}
};
