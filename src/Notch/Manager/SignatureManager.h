#pragma once

class SigManager {
public:
	class EnchantUtils {
	public:
		static inline const char* getEnchantLevel = "48 89 ? ? ? 48 89 ? ? ? 57 48 83 EC ? 48 8B ? 0F B6 ? 33 FF"; // EnchantUtils::getEnchantLevel
	};
	class ItemStackBase {
	public:
		static inline const char* getCustomName = "E8 ? ? ? ? 48 8D ? ? ? ? ? 48 8B ? E8 ? ? ? ? 48 8B ? ? ? 48 83 FA ? 0F 82"; // ItemStackBase::getCustomName
	};
	class ItemStack {
	public:
		static inline const char* EMPTY_ITEM = "48 8D 1D ? ? ? ? 48 8B D3 48 8D 4D ? E8 ? ? ? ? 48 8D 05 ? ? ? ? 48 89 45 ? 89 B5"; // ItemStack const ItemStack::EMPTY_ITEM
		static inline const char* vtable = "48 8D 05 ? ? ? ? 48 89 85 ? ? ? ? 89 BD ? ? ? ? C6 85 ? ? ? ? ? 48 8D 95"; // const ItemStack::`vftable'
	};
	class MinecraftPackets {
	public:
		static inline const char* createPacket = "E8 ? ? ? ? 90 48 83 BD ? ? 00 00 ? 0F 84 ? ? ? ? ff"; // MinecraftPackets::createPacket
	};
	class Actor {
	public:
		static inline const char* lerpMotion = "48 83 EC ? 4C 8B 81 ? ? ? ? 4D 85 C0 74 ? 8B 02"; // Actor::lerpMotion
		static inline const char* setNameTag = "48 89 ? ? ? 57 48 83 EC ? 48 8B ? 48 8B ? 48 8B ? ? ? ? ? 48 85 ? 0F 84 ? ? ? ? 48 8B ? 4C 8B"; // Actor::setNameTag
		static inline const char* shouldRender = "48 83 EC ? 48 8B 01 48 8B 80 ? ? ? ? FF 15 ? ? ? ? 84 C0 0F 94 C0 48 83 C4 ? C3 CC CC 40 53"; // Actor::shouldRender
		static inline const char* getNameTag = "48 83 EC ? 48 8B 81 ? ? ? ? 48 85 C0 74 ? 48 8B 08 BA ? ? ? ? 48 8B 40 ? 48 2B C1 48 C1 F8 ? 66 3B D0 73 ? 48 8B 41 ? 48 85 C0 74 ? 38 50 ? 75 ? 48 83 C0"; // Actor::getNameTag
	};
	class ClientInstance {
	public:
		static inline const char* update = "48 89 5C 24 ?? 48 89 74 24 ?? 55 57 41 54 41 56 41 57 48 8D AC 24 F0 FA FF FF 48 81 EC ?? ?? ?? ?? 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 85 ?? ?? ?? ?? 44"; // ClientInstance::update
	};
	class SimulatedPlayer {
	public:
		static inline const char* simulateJump = "48 89 ? ? ? 57 48 83 EC ? 48 8B ? 48 8B ? 48 8B ? ? ? ? ? FF 15 ? ? ? ? 84 C0 0F 84 ? ? ? ? 8B 47"; // SimulatedPlayer::simulateJump
	};
	class ActorCollision {
	public:
		static inline const char* isOnGround = "E8 ? ? ? ? 84 C0 0F 84 ? ? ? ? F3 0F ? ? F3 0F ? ? ? F3 0F"; // ActorCollision::isOnGround
		static inline const char* setOnGround = "E8 ? ? ? ? EB ? 0F B6 ? ? 48 8D ? ? E8"; // ActorCollision::setOnGround
	};
	class Camera {
	public:
		static inline const char* Clip = "40 ? 56 57 48 81 EC ? ? ? ? 44 0F"; // LevelRenderCamera::IDK
	};
	class AppPlatForm {
	public:
		static inline const char* getEdition = "40 53 48 83 EC ? 33 C0 48 8B DA 0F 57 C0 48 8B CB 0F 11 02 48 89 42 ? 48 89 42 ? 44 8D 40 ? 48 8D 15 ? ? ? ? E8 ? ? ? ? 48 8B C3 48 83 C4 ? 5B C3 CC CC CC CC CC CC CC CC CC CC CC 48 8D 81"; // AppPlatForm::getEdition
	};
	class ConnectionRequest {
	public:
		static inline const char* create = "40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 B4 24 ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 49 8B D9 48 89 55"; // ConnectionRequest::Create
	};
	class GuiData {
	public:
		static inline const char* displayClientMessage = "48 89 5C 24 ? 55 56 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 48 8B DA 48 8B F9 0F 57 C0"; // GuiData::displayClientMessage
	};
	class Keyboard {
	public:
		static inline const char* feed = "48 83 ec ? 0f b6 c1 4c 8d 05"; // Keyboard::feed
	};
	class ActorRenderDispatcher {
	public:
		static inline const char* render = "48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 4D 8B E9 49 8B D8 48 8B FA"; // ActorRenderDispatcher::render
	};
	class Mouse {
	public:
		static inline const char* feed = "48 8B C4 48 89 58 ? 48 89 68 ? 48 89 70 ? 57 41 54 41 55 41 56 41 57 48 83 EC ? 44 0F B7 BC 24"; // Mouse::feed
	};
	class ShulkerBoxBlockItem {
	public:
		static inline const char* appendFormattedHovertext = "40 53 55 56 57 41 56 41 57 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 4D 8B F9 48 8B DA"; // ShulkerBoxBlockItem::appendFormattedHovertext
	};
	class Item {
	public:
		static inline const char* appendFormattedHovertext = "40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 49 8B F1 4D 8B E0 48 8B DA"; // Item::appendFormattedHovertext
	};
	class LevelRendererPlayer {
	public:
		static inline const char* renderOutlineSelectionOpcode = "0F 10 ? ? ? ? ? 0F 11 ? C6 40 10 ? 0F 57 ? 0F 11 ? ? 0F 11 ? ? 48 8D"; // LevelRendererPlayer::renderOutlineSelectionOpcode
		static inline const char* renderOutlineSelection = "48 8B ? 55 53 56 57 41 ? 41 ? 48 8D ? ? 48 81 EC ? ? ? ? 0F 29 ? ? 0F 29 ? ? 44 0F"; // LevelRendererPlayer::renderOutlineSelection
		static inline const char* bobHurt = "40 53 56 48 83 EC 78 ? ? 7C"; // LevelRendererPlayer::bobHurt
		static inline const char* getFov = "48 8B C4 48 89 58 18 48 89 70 20 57 48 81 EC 90 00 00 00 0F 29 70 E8 0F 29 78 D8 44"; // LevelRendererPlayer::getFov
	};
	class MinecraftUIRenderContext {
	public:
		static inline const char* SetupAndRender = "48 8B C4 48 89 58 18 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? ? ? 70 B8 ? ? 78 A8 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4C 8B FA"; // MinecraftUIRenderContext::SetupAndRender
	};
	class UIScene {
	public:
		static inline const char* render = "48 89 5C 24 ? 48 89 74 24 ? 57 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 48 8B FA 48 8B D9 B9 ? ? ? ?"; // UIScene::render
	};
	class Mob {
	public:
		static inline const char* getCurrentSwingDuration = "48 89 5C 24 ?? 57 48 83 EC ?? 48 8B 15 ?? ?? ?? ?? 48 8B F9"; // Mob::getCurrentSwingDuration
	};
	class SplashTextRenderer {
	public:
		static inline const char* render = "48 8B C4 55 53 56 57 41 54 41 55 41 56 41 57 48 8D A8 D8 F0"; // SplashTextRenderer::render
		static inline const char* _loadSplashes = "48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 49 8B D9 49 8B F0"; // SplashTextRenderer::_loadSplashes
	};
	class Dimension {
	public:
		static inline const char* getTimeOfDay = "44 8B C2 B8 ? ? ? ? F7 EA"; // Dimension::getTimeOfDay
		static inline const char* getFogColor = "41 0F 10 08 48 8B C2 0F"; // Dimension::getFogColor
	};
	class Options {
	public:
		static inline const char* getGamma = "48 83 EC ? 80 B9 ? ? ? ? ? 48 8D 54 24 ? 48 8B 01 48 8B 40 ? 74 ? 41 B8 ? ? ? ? FF 15 ? ? ? ? 48 8B 10 48 85 D2 74 ? 48 8B 42 ? 48 8B 88 ? ? ? ? 48 85 C9 74 ? E8 ? ? ? ? 48 83 C4 ? C3 F3 0F 10 42 ? 48 83 C4 ? C3 41 B8 ? ? ? ? FF 15 ? ? ? ? 48 8B 10 48 85 D2 75 ? E8 ? ? ? ? CC E8 ? ? ? ? CC CC CC CC CC CC CC CC CC CC CC CC CC CC CC CC F3 0F 11 4C 24"; // Options::getGamma
	};
	class Level {
	public:
		static inline const char* tick = "48 89 5c 24 ? 57 48 81 ec ? ? ? ? 48 8b 05 ? ? ? ? 48 33 c4 48 89 84 24 ? ? ? ? 48 8b d9 48 8b 01 48 8b 80 ? ? ? ? ff 15 ? ? ? ? 48 8d 0d"; // Level::tick
	};
	class Font {
	public:
		static inline const char* drawTransformed = "48 8B C4 48 89 58 08 48 89 68 10 48 89 70 18 48 89 78 20 41 54 41 56 41 57 48 81 EC 00"; // Font::drawTransformed
	};
};