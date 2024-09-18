#include "Manager.h"
static std::map<std::string, int> offsets;
static std::map<std::string, void*> signatures;
bool debug = true;
void addOffset(const std::string& functionName, int offset) {
    offsets[functionName] = offset;
    if (debug) {
        std::string message = StringUtil::combine("Offset Added ", functionName, " | ", offset);
        logF(message, "INFO");
    }
}

void addSignature(const std::string& functionName, const std::string& signature) {
    signatures[functionName] = Memory::addSignature(signature.c_str());
    if (debug) {
        std::string message = (uintptr_t)signatures[functionName] == 0u ? StringUtil::combine("Signature Not Found ", functionName, " | ", signature) : StringUtil::combine("Signature Found ", functionName, " | ", signature);
        std::string status = (uintptr_t)signatures[functionName] == 0u ? "FAIL" : "OKAY";
        logF(message, status);
    }
}

int getOffset(const std::string& functionName) {
    for (std::pair<std::string, int> offset : offsets) {
        if (functionName == offset.first) {
            //if (StringUtil::starts_with(offset.first, "Actor::")) logF(StringUtil::combine(offset.first, ": ", offset.second), "INFO");
            return offset.second; // return offset
        }
    }
    return 0;
}
void* getSig(const std::string& functionName) {
    auto it = signatures.find(functionName);
    if (it != signatures.end()) {
        return it->second;
    }
    return nullptr;
}
bool Manager::checkVer(std::set<std::string> versionList) {
    return versionList.find(version::GET_VERSION()) != versionList.end();
}
void Manager::init() {
    try {
        auto ver = version::GET_VERSION();
        logF(StringUtil::combine("Ver: ", ver), "INFO");
        logF(StringUtil::combine("Supported 1.21.X: ", StringUtil::join(targetVersions1_21_X, ", ")), "INFO");
        logF(StringUtil::combine("Supported 1.21.2X: ", StringUtil::join(targetVersions1_21_2X, ", ")), "INFO");
        logF(StringUtil::combine("Supported 1.21.3X: ", StringUtil::join(targetVersions1_21_3X, ", ")), "INFO");
        logF(StringUtil::combine("Switching Offset/Signature to ", ver, "..."), "INFO");
        logF("Initializing Offset...", "WAIT");
        addOffset("vtable", 0x0);
        if (checkVer(targetVersions1_21_X)) {
            addOffset("Actor::playerName", 0x1D30);
            addOffset("Actor::packetSender", 0xC48);
            addOffset("Player::getSupplies", 0x760);
            addOffset("Actor::getPosition", 0x298);
            addOffset("Actor::getAABB", 0x2A0);
            addOffset("Actor::getRotation", 0x2A8);
            addOffset("Actor::level", 0x258);
            addOffset("Actor::dimension", 0x240);
            addOffset("Player::gamemode", 0xEC8);
            addOffset("PlayerInventory::inventory", 0xC0);
        }
        if (checkVer(targetVersions1_21_2X)) {
            addOffset("Actor::playerName", 0xC88);
            addOffset("Actor::packetSender", 0x890);
            addOffset("Player::getSupplies", 0x628);
            addOffset("Actor::getPosition", 0x270);
            addOffset("Actor::getAABB", 0x298);
            addOffset("Actor::getRotation", 0x2A0);
            addOffset("Actor::level", 0x250);
            addOffset("Actor::dimension", 0x220);
            addOffset("Player::gamemode", 0xB00);
            addOffset("PlayerInventory::inventory", 0xB8);
        }
        addOffset("GameMode::lastBreakProgress", 0x10);
        addOffset("GameMode::breakProgress", 0x14);
        logF("Initialized Offset", "OKAY");

        logF("Initializing Signature...", "WAIT");
        addSignature("GameMode::baseUseItem", "48 89 5C 24 ? 48 89 74 24 ? 55 57 41 56 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 48 8B F2 48 8B F9 45 33 F6 4C 89 75 ? 48 8D 4D ? E8 ? ? ? ? 90 48 8B 5F");
        addSignature("GameMode::getDestroyRate", "48 89 5C 24 18 57 48 83 EC 30 48 8B F9 0F 29");
        addSignature("Actor::lerpMotion", "48 83 EC ? 4C 8B 81 ? ? ? ? 4D 85 C0 74 ? 8B 02");
        addSignature("Actor::getNameTag", "48 83 EC ? 48 8B 81 ? ? ? ? 48 85 C0 74 ? 48 8B 08 BA ? ? ? ? 48 8B 40 ? 48 2B C1 48 C1 F8 ? 66 3B D0 73 ? 48 8B 41 ? 48 85 C0 74 ? 38 50 ? 75 ? 48 83 C0");
        addSignature("Actor::playEmote", "48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 B4 24 ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 41 0F B6 F8");
        addSignature("Level::tick", "48 89 5c 24 ? 57 48 81 ec ? ? ? ? 48 8b 05 ? ? ? ? 48 33 c4 48 89 84 24 ? ? ? ? 48 8b d9 48 8b 01 48 8b 80 ? ? ? ? ff 15 ? ? ? ? 48 8d 0d");
        addSignature("MinecraftPackets::createPacket", "E8 ? ? ? ? 90 48 83 BD ? ? 00 00 ? 0F 84 ? ? ? ? ff");
        addSignature("MouseDevice::feed", "48 8B C4 48 89 58 ? 48 89 68 ? 48 89 70 ? 57 41 54 41 55 41 56 41 57 48 83 EC ? 44 0F B7 BC 24");
        addSignature("Keyboard::feed", "48 83 ec ? 0f b6 c1 4c 8d 05");
        addSignature("LevelRendererPlayer::bobHurt", "40 53 56 48 83 EC 78 ? ? 7C");
        addSignature("LevelRendererPlayer::getFov", "48 8B C4 48 89 58 18 48 89 70 20 57 48 81 EC 90 00 00 00 0F 29 70 E8 0F 29 78 D8 44");
        addSignature("ScreenView::SetupAndRender", "48 8B C4 48 89 58 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 70 ? 0F 29 78 ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4C 8B FA");
        addSignature("ClientInstance::update", "48 89 5C 24 ?? 48 89 74 24 ?? 55 57 41 54 41 56 41 57 48 8D AC 24 F0 FA FF FF 48 81 EC ?? ?? ?? ?? 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 85 ?? ?? ?? ?? 44");
        addSignature("UIScene::render", "48 89 5C 24 ? 48 89 74 24 ? 57 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 48 8B FA 48 8B D9 B9 ? ? ? ?");
        addSignature("Font::drawTransformed", "48 8B C4 48 89 58 ? 48 89 68 ? 48 89 70 ? 48 89 78 ? 41 54 41 56 41 57 48 81 EC");
        addSignature("Options::getGamma", "48 83 EC ? 80 B9 ? ? ? ? ? 48 8D 54 24 ? 48 8B 01 48 8B 40 ? 74 ? 41 B8 ? ? ? ? FF 15 ? ? ? ? 48 8B 10 48 85 D2 74 ? 48 8B 42 ? 48 8B 88 ? ? ? ? 48 85 C9 74 ? E8 ? ? ? ? 48 83 C4 ? C3 F3 0F 10 42 ? 48 83 C4 ? C3 41 B8 ? ? ? ? FF 15 ? ? ? ? 48 8B 10 48 85 D2 75 ? E8 ? ? ? ? CC E8 ? ? ? ? CC CC CC CC CC CC CC CC CC CC CC CC CC CC CC CC 40 53 48 83 EC ? 48 8B 01");
        addSignature("ThirdPersonNameTag", "0f 84 ? ? ? ? 49 8b d6 48 8b ce e8 ? ? ? ? 84 c0 0f 84");
        // ActorRenderDispatcher::render | String xref: No renderer found - have you set the entity's description:identifier correctly?
        if (checkVer(targetVersions1_21_X)) {
            addSignature("LevelRenderer::renderLevel", "48 8B C4 48 89 58 ? 55 56 57 41 54 41 55 41 56 41 57 48 81 EC ? ? ? ? 0F 29 70 ? 0F 29 78 ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 49 8B F0");
            addSignature("HudMobEffectRenderer::render", "48 89 5C 24 08 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 E0 EE FF FF");
            addSignature("ConnectionRequest::create", "40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 B4 24 ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 49 8B D9 48 89 55");
            addSignature("ActorRenderDispatcher::render", "48 89 ? ? ? 55 56 57 41 ? 41 ? 41 ? 41 ? 48 8D ? ? ? 48 81 EC ? ? ? ? 48 8B ? ? ? ? ? 48 33 ? 48 89 ? ? 4D 8B ? 49 8B ? 48 8B ? 4C 8B ? 41 8B");
            addSignature("CameraAvoidanceSystemUtil::calculateHardDistanceConstraint", "40 ? 56 57 48 81 EC ? ? ? ? 44 0F");
        }
        else if (checkVer(targetVersions1_21_2X)) {
            addSignature("ConnectionRequest::create", "40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 B4 24 ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4D 8B E0");
            addSignature("ActorRenderDispatcher::render", "48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 4D 8B E9 49 8B F8 48 8B F2");
            addSignature("CameraAvoidanceSystemUtil::calculateHardDistanceConstraint", "40 ? 56 57 48 81 EC ? ? ? ? 44 0F");
        } else if (checkVer(targetVersions1_21_3X)) {
            addSignature("ConnectionRequest::create", "40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 B4 24 ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4D 8B E0");
            addSignature("ActorRenderDispatcher::render", "48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 4D 8B E9 49 8B D8 48 8B FA 4C 8B F9");
        }
        logF("Initialized Signature", "OKAY");
    }
    catch (const std::exception& e) {
        logF(e.what(), "ERROR");
    }
}
