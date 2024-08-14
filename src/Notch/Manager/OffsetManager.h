#pragma once

class OffsetManager {
public:
	class Actor {
	public:
		static inline int entityContext = 0x8; // I Dont Know Bruh
		static inline int level = 0x258; // TheEndGenerator::getBiomeSource
		static inline int gamemode = 0x0EC8; // Player::getGameMode
		static inline int statevector = 0x290; // Actor::getPosition
		static inline int AABBShape = 0x298; // Actor::getAABB or statevector + 8
		static inline int ActorRotation = 0x2A0; // Actor::getRotation or statevector + 16
		static inline int rcx = 0x10;
		static inline int rda = 0x18;
	};
	class ClientInstance {
	public:
		static inline int getMousePos = 0x498;
		static inline int mcgame = 0x00C8;
		static inline int guiData = 0x558;
		static inline int minecraft = 0xD0;
		static inline int packetSender = 0xF0;
	};
};