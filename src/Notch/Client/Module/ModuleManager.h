#pragma once

#include <type_traits>

#include "Modules/Module.h"

//Combat
//Misc
//Render
#include "Modules/Render/AutoEmote.h"
//Movement
#include "Modules/Movement/Velocity.h"
//Player
//Client
#include "Modules/Client/CustomFont.h"
#include "Modules/Client/ClickGui.h"
#include "Modules/Client/Colors.h"
#include "Modules/Client/ArrayList.h"
//Unknow

class ModuleManager {
private:
    std::vector<Module*> moduleList;
    bool initialized = false;
public:
    ~ModuleManager();
public:
    std::vector<Module*>* getModuleList() { return &this->moduleList; }
    const bool isInitialized() { return this->initialized; }
    void initModules();
    template <typename TRet>
    TRet* getModule() {
        if (!isInitialized())
            return nullptr;
        for (auto pMod : moduleList) {
            if (auto pRet = dynamic_cast<typename std::remove_pointer<TRet>::type*>(pMod)) {

                return pRet;
            }
        }
        return nullptr;
    };

    Module* getModuleByName(const std::string& moduleName) {
        std::string nameLower(moduleName);
        std::transform(nameLower.begin(), nameLower.end(), nameLower.begin(), ::tolower);

        for (Module* mod : moduleList) {
            std::string modNameLower = mod->getModuleName();
            std::transform(modNameLower.begin(), modNameLower.end(), modNameLower.begin(), ::tolower);
            if (strcmp(nameLower.c_str(), modNameLower.c_str()) == 0) return mod;
        }
        return nullptr;
    }
public:
    void onSaveConfig(json* currentConfig);
    void onLoadConfig(json* config);
    void onKeyUpdate(int key, bool isDown);
    void onImGuiRender(ImDrawList* drawlist);
    void onNormalTick(Actor* actor);
};


extern ModuleManager* moduleMgr;