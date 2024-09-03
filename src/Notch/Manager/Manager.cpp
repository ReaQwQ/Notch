#include "Manager.h"
static std::map<std::string, int> offsets;
static std::map<std::string, void*> signatures;
bool debug = false;
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
        std::string message = StringUtil::combine("Signature Added ", functionName, " | ", signature);
        logF(message, "INFO");
    }
}

int getOffset(const std::string& functionName) {
    for (std::pair<std::string, int> offset : offsets) {
        if (functionName == offset.first) {
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
bool Manager::checkVer(int version, std::set<int> versionList) {
    return versionList.find(version) != versionList.end();
}
void Manager::init() {
    try {
        int ver = version::GET_VERSION_INT();
        logF(StringUtil::combine("Ver: ", ver), "INFO");
        logF(StringUtil::combine("Supported 1.21.X: ", StringUtil::join(targetVersions1_21_X, ", ")), "INFO");
        logF(StringUtil::combine("Supported 1.21.2X: ", StringUtil::join(targetVersions1_21_2X, ", ")), "INFO");
        logF(StringUtil::combine("Switching Offset/Signature to ", ver, "..."), "INFO");
        logF("Initializing Offset...", "WAIT");
        if (checkVer(ver, targetVersions1_21_X)) {
            addOffset("Actor::playerName", 0x1D30);
            addOffset("Actor::packetSender", 0xC48);
            addOffset("Player::getSupplies", 0x760);
            addOffset("Actor::StateVectorComponent", 0x258);
            addOffset("Actor::dimension", 0x240);
            addOffset("Player::gamemode", 0xEC8);
            addOffset("PlayerInventory::inventory", 0xC0);
        }
        if (checkVer(ver, targetVersions1_21_2X)) {
            addOffset("Actor::playerName", 0xC88);
            addOffset("Actor::packetSender", 0x890);
            addOffset("Player::getSupplies", 0x628);
            addOffset("Actor::StateVectorComponent", 0x270);
            addOffset("Actor::dimension", 0x220);
            addOffset("Player::gamemode", 0xB00);
            addOffset("PlayerInventory::inventory", 0xB8);
        }

        addOffset("GuiData::realSize", 0x0030);
        addOffset("GuiData::realSize2", 0x0038);
        addOffset("GuiData::scaledSize", 0x0040);
        addOffset("GuiData::guiScale", 0x004C);
        addOffset("GuiData::scaleMultiplier", 0x0050);
        addOffset("GuiData::MousePosX", 0x006A);
        addOffset("GuiData::MousePosY", 0x006C);
        addOffset("ClientInstance::getFovX", 0x6F0);
        addOffset("ClientInstance::getFovY", 0x704);
        addOffset("ClientInstance::MinecraftGame", 0xC8);
        addOffset("ClientInstance::Minecraft", 0xD0);
        addOffset("ClientInstance::LoopbackPacketSender", 0xF0);
        addOffset("ClientInstance::GuiData", 0x558);
        addOffset("PlayerInventory::selectedSlot", 0x10);
        addOffset("GameMode::player", 0x8);
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
        addSignature("LevelRenderer::renderLevel", "48 8B C4 48 89 58 ? 55 56 57 41 54 41 55 41 56 41 57 48 81 EC ? ? ? ? 0F 29 70 ? 0F 29 78 ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 49 8B F0");
        addSignature("ScreenView::SetupAndRender", "48 8B C4 48 89 58 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 70 ? 0F 29 78 ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4C 8B FA");
        addSignature("ClientInstance::update", "48 89 5C 24 ?? 48 89 74 24 ?? 55 57 41 54 41 56 41 57 48 8D AC 24 F0 FA FF FF 48 81 EC ?? ?? ?? ?? 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 85 ?? ?? ?? ?? 44");
        addSignature("CameraAvoidanceSystemUtil::calculateHardDistanceConstraint", "40 ? 56 57 48 81 EC ? ? ? ? 44 0F");
        addSignature("UIScene::render", "48 89 5C 24 ? 48 89 74 24 ? 57 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 48 8B FA 48 8B D9 B9 ? ? ? ?");
        addSignature("Font::drawTransformed", "48 8B C4 48 89 58 ? 48 89 68 ? 48 89 70 ? 48 89 78 ? 41 54 41 56 41 57 48 81 EC");
        addSignature("GuiData::displayClientMessage", "40 55 53 56 57 41 56 48 8D AC 24 F0 FE FF FF 48 81 EC 10 02 00 00 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 85 00 01 00 00 41");
        // ActorRenderDispatcher::render | String xref: No renderer found - have you set the entity's description:identifier correctly?
        if (checkVer(ver, targetVersions1_21_X)) {
             addSignature("ConnectionRequest::create", "40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 B4 24 ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 49 8B D9 48 89 55");
             addSignature("ActorRenderDispatcher::render", "48 89 ? ? ? 55 56 57 41 ? 41 ? 41 ? 41 ? 48 8D ? ? ? 48 81 EC ? ? ? ? 48 8B ? ? ? ? ? 48 33 ? 48 89 ? ? 4D 8B ? 49 8B ? 48 8B ? 4C 8B ? 41 8B");
        }
        else if (checkVer(ver, targetVersions1_21_2X)) {
            addSignature("ConnectionRequest::create", "40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 B4 24 ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4D 8B E0");
            addSignature("ActorRenderDispatcher::render", "48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 4D 8B E9 49 8B F8 48 8B F2");
        }
        addSignature("ThirdPersonNameTag", "0f 84 ? ? ? ? 49 8b d6 48 8b ce e8 ? ? ? ? 84 c0 0f 84");
        logF("Initialized Signature", "OKAY");
    }
    catch (const std::exception& e) {
        logF(e.what(), "ERROR");
    }
}
