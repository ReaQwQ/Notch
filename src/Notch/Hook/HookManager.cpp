#include "HookManager.h"
// Hook include
#include "Hooks/Keyboard/feed.h"
#include "Hooks/ClientInstance/update.h"
#include "Hooks/Font/drawTransformed.h"
#include "Hooks/LevelRendererPlayer/bobHurt.h"
#include "Hooks/LevelRendererPlayer/getFov.h"
#include "Hooks/Actor/lerp.h"
#include "Hooks/Mouse/feed.h"
#include "Hooks/LoopbackPacketSender/SendToServer.h"
#include "Hooks/Level/tick.h"
#include "Hooks/Test/function.h"
// End
void HookManager::init() {
	Hooks.push_back(new Keyboard__feedHook());
	Hooks.push_back(new ClientInstance__updateHook());
	Hooks.push_back(new Font__drawTransformedHook());
	Hooks.push_back(new LevelRendererPlayer__bobHurtHook());
	Hooks.push_back(new LevelRendererPlayer__getFovHook());
	Hooks.push_back(new Actor__lerpHook());
	Hooks.push_back(new Mouse__feedHook());
	Hooks.push_back(new LoopbackPacketSender__SendToServerHook());
	Hooks.push_back(new Level__tickHook());
	Hooks.push_back(new Test__functionHook());

	for (Hook* hook : Hooks) {
		hook->Initialize();
	}
};