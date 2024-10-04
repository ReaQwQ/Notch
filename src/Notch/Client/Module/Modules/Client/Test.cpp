#include "Test.h"
#include "Debugconsole.h"
#include "../../../../GameData.h"
#include "../../../../GameData.h"
#include "../../../../SDK/Actor/Actor.h"
#include "../../../../Utils/Memory.h"

Test::Test() : Module("Test", "Test module for dumping things", Category::CLIENT, VK_ESCAPE) {
}
Test::~Test() {
}

void Test::onEnable() {
    static DebugConsole* DebugConsoleMod = moduleMgr->getModule<DebugConsole>();

    // Print the ClientInstance address
    DebugConsoleMod->addLog(StringUtil::combine("ClientInstance Found at: ", Game.getClientInstance()->VTable));
    AddressLogger aaaa;
    // Retrieve the logs and print them using addLog
    for (const auto& log : aaaa.printLogs()) {
        DebugConsoleMod->addLog(log);
    }
}

void Test::onDisable() {
	static DebugConsole* DebugConsoleMod = moduleMgr->getModule<DebugConsole>();

	//DebugConsoleMod->addLog(Game.getClientInstance() == nullptr ? "NULLPTR" : "NOT NULLPTR");

}