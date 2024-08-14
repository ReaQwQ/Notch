#pragma once

#include "../../Utils/HMath.h"
#include "../../Utils/ColorUtil.h"
#include "../../Utils/TextFormat.h"
#include "../../Manager/SignatureManager.h"
#include "../../Manager/OffsetManager.h"
#include "../../Utils/Memory.h"

#include "GameMode.h"
#include "Level.h"
#include <bitset>
#include "ActorFlags.h"
class HashedString;
class ActorType;
class ActorInitializationMethod;
class VariantParameterList;
class ActorDamageSource;
class ActorDamageCause;
class IConstBlockSource;
class ItemStack;
class ActorUniqueID {};
class AddActorBasePacket;
class InputMode;
class NewInteractionModel;
class Block;
class ItemUseMethod;
class ActorEvent;
class RenderParams;
class ArmorSlot;
class HandSlot;
class EntityContext;
class ActorInteraction;
class ItemStackBase;
class Player;
class AnimationComponent;
class MobEffectInstance;
class CommandPermissionLevel;
class MaterialType;
class EquipmentSlot;
class ArmorMaterialType;
class CompoundTag;
class DataLoadHelper;
class StructureFeatureType;
class BlockActor;
class BackgroundTaskBase;
class TextObjectRoot;
class ResolvedTextObject;
class BedSleepingResult;
class GameType;
class IMinecraftEventing;
class IContainerManager;
class Container;
class InventoryTransaction;
class ComplexInventoryTransaction;
class PlayerEventCoordinator;
class PlayerMovementSettings;
class ChunkViewSource;
class ChunkSource;
class LayeredAbilities;
class noooo;
class BodyControl;
class Tick;
class ChunkPos;
class AABBShapeComponent {
public:
	Vec3 PosLower = Vec3(0, 0, 0);
	Vec3 PosUpper = Vec3(0, 0, 0);
	Vec2 Hitbox = Vec2(0, 0);
};
class ActorRotationComponent {
public:
	Vec2 Rotations;
	Vec2 PrevRotations;
};
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
//public:
//	EntityContext* entityContext; //0x8
//private:
//	char padding_0[0x248];
//public:
//	Level* level; //0x258
//private:
//	char padding_1[0x30];
//public:
//	StateVector* stateVector; //0x290
//public:
//	AABBShapeComponent* AABBShape; //0x298
//public:
//	ActorRotationComponent* ActorRotation; //0x2A0
//private:
//	char padding_2[0xc20];
//public:
//	GameMode* gamemode; //0xEC8
public:

	BUILD_ACCESS(this, EntityContext*, entityContext, OffsetManager::Actor::entityContext);
	BUILD_ACCESS(this, StateVector*, stateVector, OffsetManager::Actor::statevector);
	BUILD_ACCESS(this, GameMode*, gamemode, OffsetManager::Actor::gamemode);
	BUILD_ACCESS(this, Level*, level, OffsetManager::Actor::level);
	BUILD_ACCESS(this, AABBShapeComponent*, AABBShape, OffsetManager::Actor::AABBShape);
	BUILD_ACCESS(this, ActorRotationComponent*, ActorRotation, OffsetManager::Actor::ActorRotation);
public:
	virtual bool getStatusFlag(ActorFlags) const; // 0
	virtual void setStatusFlag(ActorFlags, bool); // 1
	virtual bool hasComponent(const HashedString&) const; // 2
	virtual void outOfWorld(); // 3
	virtual void reloadHardcoded(ActorInitializationMethod, const VariantParameterList&); // 4
	virtual void reloadHardcodedClient(ActorInitializationMethod, const VariantParameterList&); // 5
	virtual void initializeComponents(ActorInitializationMethod, const VariantParameterList&); // 6
	virtual void reloadComponents(ActorInitializationMethod, const VariantParameterList&); // 7
	virtual void _serverInitItemStackIds(); // 8
	virtual void _doInitialMove(); // 9
	virtual void destructor(); // 10
	virtual void resetUserPos(bool); // 11
	virtual  ActorType getOwnerEntityType(); // 12
	virtual void remove(); // 13
	virtual Vec3 getFiringPos() const; // 14
	virtual float getInterpolatedBodyRot(float) const; // 15
	virtual float getInterpolatedHeadRot(float) const; // 16
	virtual float getInterpolatedBodyYaw(float) const; // 17
	virtual float getYawSpeedInDegreesPerSecond() const; // 18
	virtual Vec3 getInterpolatedRidingOffset(float, int) const; // 19
	virtual bool isFireImmune() const; // 20
	virtual void blockedByShield(const ActorDamageSource&, Actor&); // 21
	virtual bool canDisableShield(); // 22
	virtual void teleportTo(const Vec3&, bool, int, int, bool); // 23
	virtual void lerpMotion(const Vec3&); // 24
	virtual std::unique_ptr<AddActorBasePacket, std::default_delete<AddActorBasePacket>> tryCreateAddActorPacket(); // 25
	virtual void normalTick(); // 26
	virtual void baseTick(); // 27
	virtual void passengerTick(); // 28
	virtual bool startRiding(Actor&); // 29
	virtual void addPassenger(Actor&); // 30
	virtual std::string getExitTip(std::string&, InputMode, NewInteractionModel) const; // 31
	virtual std::string getEntityLocNameString() const; // 32
	virtual bool isInWall() const; // 33
	virtual bool isInvisible() const; // 34
	virtual bool canShowNameTag() const; // 35
	virtual std::string getFormattedNameTag() const; // 36
	virtual MC_Color getNameTagTextColor() const; // 37
	virtual float getShadowRadius() const; // 38
	virtual Vec3 getHeadLookVector(float) const; // 39
	virtual bool canInteractWithOtherEntitiesInGame() const; // 40
	virtual float getBrightness(float, const IConstBlockSource&) const; // 41
	virtual void unknown_42(); // 42
	virtual bool isImmobile() const; // 43
	virtual void _doSprintParticleEffect(); // 44
	virtual bool isSleeping() const; // 45
	virtual void setSleeping(bool); // 46
	virtual void setSneaking(bool); // 47
	virtual bool isBlocking() const; // 48
	virtual bool isDamageBlocked(const ActorDamageSource&) const; // 49
	virtual bool isAlive() const; // 50
	virtual bool isOnFire() const; // 51
	virtual bool isSurfaceMob() const; // 52
	virtual void unknown_53(); // 53
	virtual bool canAttack(Actor*, bool) const; // 54
	virtual void setTarget(Actor*); // 55
	virtual bool isValidTarget(Actor*) const; // 56
	virtual bool attack(Actor&, const ActorDamageCause&); // 57
	virtual void performRangedAttack(Actor&, float); // 58
	virtual void setOwner(ActorUniqueID); // 59
	virtual void setSitting(bool); // 60
	virtual void unknown_61(); // 61
	virtual void unknown_62(); // 62
	virtual void setStanding(bool); // 63
	virtual bool canPowerJump() const; // 64
	virtual bool isEnchanted() const; // 65
	virtual bool shouldRender() const; // 66
	virtual void playAmbientSound(); // 67
	virtual LevelSoundEvent getAmbientSound() const; // 68
	virtual bool isInvulnerableTo(const ActorDamageSource&) const; // 69
	virtual ActorDamageCause getBlockDamageCause(const Block&) const; // 70
	virtual bool doFireHurt(int); // 71
	virtual void onLightningHit(); // 72
	virtual void feed(int); // 73
	virtual void handleEntityEvent(ActorEvent, int); // 74
	virtual const HashedString& getActorRendererId() const; // 75
	virtual void despawn(); // 76
	virtual void setArmor(ArmorSlot, const ItemStack&); // 77
	virtual ArmorMaterialType getArmorMaterialTypeInSlot(ArmorSlot) const; // 78
	virtual int getArmorTextureIndexInSlot(ArmorSlot) const; // 79
	virtual float getArmorColorInSlot(ArmorSlot, int) const; // 80
	virtual void setEquippedSlot(EquipmentSlot, const ItemStack&); // 81
	virtual void setCarriedItem(const ItemStack&); // 82
	virtual const ItemStack& getSelectedItem() const; // 83
	virtual void setOffhandSlot(const ItemStack&); // 84
	virtual const ItemStack& getEquippedTotem() const; // 85
	virtual bool consumeTotem(); // 86
	virtual bool save(CompoundTag&) const; // 87
	virtual bool load(const CompoundTag&, DataLoadHelper&); // 88
	virtual const HashedString& getRawName() const; // 89
	virtual ActorUniqueID getSourceUniqueID() const; // 90
	virtual bool canFreeze() const; // 91
	virtual AABB getLiquidAABB(MaterialType) const; // 92
	virtual void handleInsidePortal(const Vec3&); // 93
	virtual bool canChangeDimensionsUsingPortal() const; // 94
	virtual void unknown_95(); // 95
	virtual void changeDimension(void); // 96
	virtual ActorUniqueID getControllingPlayer() const; // 97
	virtual float causeFallDamageToActor(float, float, ActorDamageSource); // 98
	virtual void onSynchedDataUpdate(int); // 99
	virtual bool canAddPassenger(Actor&) const; // 100
	virtual void unknown_101(); // 101
	virtual bool hasGetStrictParsingVersion_102(); // 102
	virtual bool inCaravan() const; // 103
	virtual void unknown_104(); // 104
	virtual void unknown_105(); // 105
	virtual void startSwimming(); // 106
	virtual void stopSwimming(); // 107
	virtual void buildDebugInfo(std::string&) const; // 108
	virtual CommandPermissionLevel getCommandPermissionLevel() const; // 109
	virtual int getDeathTime() const; // 110
	virtual bool canBeAffected(unsigned int) const; // 111
	virtual bool canBeAffectedByArrow(const MobEffectInstance&) const; // 112
	virtual void onEffectRemoved(MobEffectInstance&); // 113
	virtual bool canObstructSpawningAndBlockPlacement() const; // 114
	virtual AnimationComponent& getAnimationComponent(); // 115
	virtual void openContainerComponent(Player&); // 116
	virtual void swing(); // 117
	virtual void useItem(ItemStackBase&, ItemUseMethod, bool); // 118
	virtual void getDebugText(std::string&); // 119
	virtual float getMapDecorationRotation() const; // 120
	virtual float getPassengerYRotation(const Actor&) const; // 121
	virtual bool add(ItemStack&); // 122
	virtual bool drop(const ItemStack&, bool); // 123
	virtual bool getInteraction(Player&, ActorInteraction&, const Vec3&); // 124
	virtual void unknown_125(); // 125
	virtual void unknown_126(); // 126
	virtual void startSpinAttack(); // 127
	virtual void stopSpinAttack(); // 128
	virtual void unknown_129(); // 129
	virtual void kill(); // 130
	virtual void die(const ActorDamageSource&); // 131
	virtual bool shouldDropDeathLoot() const; // 132
	virtual void applySnapshot(const EntityContext&, const EntityContext&); // 133
	virtual float getNextStep(float); // 134
	virtual void unknown_135(); // 135
	virtual std::optional<Vec3> getLastDeathPos() const; // 136
	virtual std::optional<void> getLastDeathDimension() const; // 137
	virtual bool hasDiedBefore() const; // 138
	virtual void doEnterWaterSplashEffect(); // 139
	virtual void doExitWaterSplashEffect(); // 140
	virtual void doWaterSplashEffect(); // 141
	virtual bool _shouldProvideFeedbackOnHandContainerItemSet(HandSlot, const ItemStack&) const; // 142
	virtual bool _shouldProvideFeedbackOnArmorSet(ArmorSlot, const ItemStack&) const; // 143
	virtual void updateEntitySpecificMolangVariables(RenderParams&); // 144
	virtual bool shouldTryMakeStepSound(); // 145
	virtual bool _hurt(const ActorDamageSource&, float, bool, bool); // 146
	virtual void readAdditionalSaveData(const CompoundTag&, DataLoadHelper&); // 147
	virtual void addAdditionalSaveData(CompoundTag&) const; // 148
	virtual void _playStepSound(const Vec3&, const Block&); // 149
	virtual void unknown_150(); // 150
	virtual void knockback(Actor*, int, float, float, float, float, float); // 151
	virtual void unknown_152(); // 152
	virtual void setSprinting(bool); // 153
	virtual LevelSoundEvent getDeathSound(); // 154
	virtual float getSpeed() const; // 155
	virtual void setSpeed(float); // 156
	virtual void hurtEffects(const ActorDamageSource&, float, bool, bool); // 157
	virtual void aiStep(); // 158
	virtual void pushActors(); // 159
	virtual bool checkSpawnRules(bool); // 160
	virtual bool checkSpawnObstruction() const; // 161
	virtual int getItemUseDuration() const; // 162
	virtual float getItemUseStartupProgress() const; // 163
	virtual float getItemUseIntervalProgress() const; // 164
	virtual float getMaxHeadXRot(); // 165
	virtual bool hasGetStrictParsingVersion_166(); // 166
	virtual bool doHurtTarget(Actor*, const ActorDamageCause&); // 167
	virtual int getArmorValue() const; // 168
	virtual void hurtArmorSlots(const ActorDamageSource&, int, std::bitset<4>); // 169
	virtual void setDamagedArmor(ArmorSlot, const ItemStack&); // 170
	virtual void sendArmorDamage(std::bitset<4>); // 171
	virtual void sendArmor(std::bitset<4>); // 172
	virtual std::vector<const ItemStack*, std::allocator<const ItemStack*>> getAllHand() const; // 173
	virtual std::vector<const ItemStack*, std::allocator<const ItemStack*>> getAllEquipment() const; // 174
	virtual void dropEquipmentOnDeath(); // 175
	virtual void dropEquipmentOnDeath(const ActorDamageSource&); // 176
	virtual void clearVanishEnchantedItemsOnDeath(); // 177
	virtual void sendInventory(bool); // 178
	virtual float getDamageAfterEnchantReduction(const ActorDamageSource&, float) const; // 179
	virtual bool createAIGoals(); // 180
	virtual void unknown_181(); // 181
	virtual bool setItemSlot(EquipmentSlot, const ItemStack&); // 182
	virtual void setTransitioningSitting(bool); // 183
	virtual float getAmount(int, float) const; // 184
	virtual void unknown_185(); // 185
	virtual std::unique_ptr<BodyControl, std::default_delete<BodyControl>> initBodyControl(); // 186
	virtual void newServerAiStep(); // 187
	virtual void tickDeath(); // 188
	virtual AABB _getAdjustedAABBForSpawnCheck(const AABB&, const Vec3&) const; // 189
	virtual void prepareRegion(ChunkSource&); // 190
	virtual void destroyRegion(); // 191
	virtual void suspendRegion(); // 192
	virtual void _fireDimensionChanged(); // 193
	virtual void changeDimensionWithCredits(void); // 194
	virtual void tickWorld(const Tick&); // 195
	virtual void unknown_196(); // 196
	virtual const std::vector<ChunkPos, std::allocator<ChunkPos>>& getTickingOffsets() const; // 197
	virtual void moveView(); // 198
	virtual void moveSpawnView(const Vec3&, noooo); // 199
	virtual void checkMovementStats(const Vec3&); // 200
	virtual StructureFeatureType getCurrentStructureFeature() const; // 201
	virtual void unknown_202(); // 202
	virtual void respawn(); // 203
	virtual void unknown_204(); // 204
	virtual bool hasGetStrictParsingVersion_205(); // 205
	virtual void unknown_206(); // 206
	virtual void openBook(int, bool, int, BlockActor*); // 207
	virtual void openTrading(const ActorUniqueID&, bool); // 208
	virtual void unknown_209(); // 209
	virtual void taskRegister(std::shared_ptr<BackgroundTaskBase>); // 210
	virtual void openInventory(); // 211
	virtual void unknown_212(); // 212
    void displayClientMessage(std::string Message, ...) {
		va_list arg;
		va_start(arg, Message.c_str());
		char message[400];
		vsprintf_s(message, 400, Message.c_str(), arg);
		std::string* MessagePointer = new std::string(std::string(BOLD) + std::string(BLACK) + "[" + std::string(AQUA) + "Notch" + std::string(BLACK) + "] " + std::string(RESET) + message);
		Memory::CallVFunc<213, void, std::string*>((void*)this, MessagePointer);
	};
	virtual void displayTextObjectMessage(const TextObjectRoot&, std::string&, std::string&); // 214
	virtual void displayTextObjectWhisperMessage(std::string&, std::string&, std::string&); // 215
	virtual void displayTextObjectWhisperMessage(const ResolvedTextObject&, std::string&, std::string&); // 216
	virtual void displayWhisperMessage(std::string&, std::string&, std::string&, std::string&); // 217
	virtual BedSleepingResult startSleepInBed(const Vec3&); // 218
	virtual void stopSleepInBed(bool, bool); // 219
	virtual bool canStartSleepInBed(); // 220
	virtual void openSign(const Vec3&, bool); // 221
	virtual void unknown_222(); // 222
	virtual bool isLoading() const; // 223
	virtual bool isPlayerInitialized() const; // 224
	virtual void unknown_225(); // 225
	virtual void setPlayerGameType(GameType); // 226
	virtual void initHUDContainerManager(); // 227
	virtual void _crit(Actor&); // 228
	virtual IMinecraftEventing* getEventing() const; // 229
	virtual void unknown_230(); // 230
	virtual void addExperience(int); // 231
	virtual void addLevels(int); // 232
	virtual void setContainerData(IContainerManager&, int, int); // 233
	virtual void slotChanged(IContainerManager&, Container&, int, const ItemStack&, const ItemStack&, bool); // 234
	virtual void refreshContainer(IContainerManager&); // 235
	virtual void deleteContainerManager(); // 236
	virtual bool isActorRelevant(const Actor&); // 237
	virtual bool isTeacher() const; // 238
	virtual void onSuspension(); // 239
	virtual void onLinkedSlotsChanged(); // 240
	virtual void sendInventoryTransaction(const InventoryTransaction&) const; // 241
	virtual void sendComplexInventoryTransaction(std::unique_ptr<ComplexInventoryTransaction, std::default_delete<ComplexInventoryTransaction>>) const; // 242
	virtual void sendNetworkPacket(Packet&) const; // 243
	virtual PlayerEventCoordinator& getPlayerEventCoordinator(); // 244
	virtual bool hasGetStrictParsingVersion_245(); // 245
	virtual std::string getXuid() const; // 246
	virtual const PlayerMovementSettings& getMovementSettings() const; // 247
	virtual void unknown_248(); // 248
	virtual unsigned char getMaxChunkBuildRadius() const; // 249
	virtual void onMovePlayerPacketNormal(const Vec3&, const Vec2&, float); // 250
	virtual std::shared_ptr<ChunkViewSource> _createChunkSource(ChunkSource&); // 251
	virtual void setAbilities(const LayeredAbilities&); // 252
	virtual void getEditorPlayer() const; // 253
	virtual void destroyEditorPlayer(); // 254
	virtual int _getSpawnChunkLimit() const; // 255
	virtual void _updateChunkPublisherView(const Vec3&, float); // 256

	std::string getNameTag() {
		return *Memory::CallFunc<std::string*, void*>(Memory::addSignature(SigManager::Actor::getNameTag), (void*)this);
	}

	void jumpFromGround() {
		Memory::CallFunc<void, Actor*>(Memory::addSignature(SigManager::SimulatedPlayer::simulateJump), this);
	}

	Vec3 getPosition() {
		return Vec3(this->stateVector->pos.x - 1, this->stateVector->pos.y - 2, this->stateVector->pos.z);
	}
	Vec3 getPositionOld() {
		return this->stateVector->oldPos;
	}
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
	ActorRotationComponent* getRotation() {
		return this->ActorRotation;
	}
	AABBShapeComponent* getAABB() {
		return this->AABBShape;
	}
	Level* getLevel() {
		return this->level;
	}
	GameMode* getGameMode() {
		return this->gamemode;
	}
};