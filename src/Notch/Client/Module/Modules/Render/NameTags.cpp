#include "NameTags.h"
NameTags::NameTags() : Module("NameTags", "", Category::RENDER, 0x0) {
	addBoolCheck("Self", "Shows your nametag for you while in 3rd person mode.", &ThirdPersonNameTag);
};

void NameTags::onImGuiRender(ImDrawList* d) {
	auto plr = Game.getLocalPlayer();
	if (!d || !plr) return;

	/*entityList = plr->level->getRuntimeActorList();
	for (Actor* actor : entityList) {
		logF(StringUtil::combine("ActorNameTag: ", actor->getNameTag()), "INFO");
	}*/
};

void NameTags::onEnable() {
    if (!ThirdPersonNameTag) return;
    instructionPointer = getSig("ThirdPersonNameTag");

    if (instructionPointer) {
        memcpy(originalBytes, instructionPointer, instructionSize);

        DWORD protect;
        VirtualProtect(instructionPointer, instructionSize, PAGE_EXECUTE_READWRITE, &protect);
        memset(instructionPointer, 0x90 /*No-Operation*/, instructionSize);
        VirtualProtect(instructionPointer, instructionSize, protect, &protect);
    }
}

void NameTags::onDisable() {
    if (!ThirdPersonNameTag) return;

    if (instructionPointer) {
        DWORD protect;
        VirtualProtect(instructionPointer, instructionSize, PAGE_EXECUTE_READWRITE, &protect);
        memcpy(instructionPointer, originalBytes, instructionSize);
        VirtualProtect(instructionPointer, instructionSize, protect, &protect);
    }
}