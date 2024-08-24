#include "ModuleManager.h"

void ModuleManager::initModules() {

	{ // Init modules
		//Combat
		//Misc
		//Render
		moduleList.push_back(new CustomFov());
		moduleList.push_back(new ViewModel());
		moduleList.push_back(new AutoEmote());
		//Movement
		moduleList.push_back(new Velocity());
		//Player
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
	getModule<ClickGui>()->setEnabled(false);
	for (Module* mod : moduleList) {
		mod->onSaveConfig(currentConfig);
	}
}

void ModuleManager::onLoadConfig(json* config) {
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
			mod->onNormalTick(actor);
		}
	}
}
void ModuleManager::onGetFov(float& fov) {
	if (!isInitialized()) return;
	for (Module* mod : moduleList) {
		if (mod->isEnabled()) {
			mod->onGetFov(fov);
		}
	}
}
void ModuleManager::onbobHurt(glm::mat4& matrix, float lerpT) {
	if (!isInitialized()) return;
	for (Module* mod : moduleList) {
		if (mod->isEnabled()) {
			mod->onbobHurt(matrix, lerpT);
		}
	}
}
ModuleManager* moduleMgr = new ModuleManager();