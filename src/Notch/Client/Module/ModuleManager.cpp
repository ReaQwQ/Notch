#include "ModuleManager.h"

void ModuleManager::initModules() {

	{ // Init modules
		//Combat
		//Misc
		//Render
		moduleList.push_back(new PotionHud());
		moduleList.push_back(new CustomFov());
		moduleList.push_back(new ViewModel());
		moduleList.push_back(new NameTags());
		moduleList.push_back(new ViewClip());
		//Movement
		moduleList.push_back(new Velocity());
		//Player
		moduleList.push_back(new AutoEmote());
		//Client
		moduleList.push_back(new CustomFont());
		moduleList.push_back(new ClickGui());
		moduleList.push_back(new Colors());
		moduleList.push_back(new ArrayList());

		//Unknow
	}
	std::sort(moduleList.begin(), moduleList.end(), [](Module* lhs, Module* rhs) {
		return lhs->getModuleName().size() < rhs->getModuleName().size();
		});
	this->initialized = true;
	getModule<ClickGui>()->setEnabled(false);
}

ModuleManager::~ModuleManager() {
	for (Module* mod : moduleList) {
		mod->setEnabled(false);
		delete mod;
	}
}

void ModuleManager::onSaveConfig(json* currentConfig) {
	if (!isInitialized()) return;
	getModule<ClickGui>()->setEnabled(false);
	for (Module* mod : moduleList) {
		mod->onSaveConfig(currentConfig);
	}
}

void ModuleManager::onLoadConfig(json* config) {
	if (!isInitialized()) return;
	for (Module* mod : moduleList) {
		mod->onLoadConfig(config);
	}
	getModule<ClickGui>()->setEnabled(false);
}

void ModuleManager::onKeyUpdate(int key, bool isDown) {
	if (!isInitialized()) return;
	for (Module* mod : moduleList) {
		mod->onKeyUpdate(key, isDown);
	}
}
void ModuleManager::onImGuiRender(ImDrawList* drawlist) {
	if (!isInitialized()) return;
	for (Module* mod : moduleList) {
		if (mod->isEnabled()) {
			mod->onImGuiRender(drawlist);
		}
	}
}
void ModuleManager::onNormalTick(Actor* actor) {
	if (!isInitialized()) return;
	for (Module* mod : moduleList) {
		if (mod->isEnabled()) {
			mod->onTick(actor);
		}
	}
}

void ModuleManager::onLevelRender() {
	if (!isInitialized()) return;
	for (Module* mod : moduleList) {
		if (mod->isEnabled()) {
			mod->onLevelRender();
		}
	}
}

void ModuleManager::onJoiningServer() {
	if (!isInitialized()) return;
	for (Module* mod : moduleList) {
		if (mod->isEnabled()) {
			mod->onJoiningServer();
		}
	}
}

void ModuleManager::onRender(MinecraftUIRenderContext* c) {
	if (!isInitialized()) return;
	for (Module* mod : moduleList) {
		if (mod->isEnabled()) {
			mod->onRender(c);
		}
	}
}

ModuleManager* moduleMgr = new ModuleManager();