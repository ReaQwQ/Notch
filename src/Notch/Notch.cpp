#include "Notch.h"
bool Initialized;
bool& MH_Initialized() {
    return Initialized;
}

DWORD APIENTRY Notch::ejectThread(HMODULE lpParam) {
    while (Run::running) {
        Sleep(10);
    }
    std::lock_guard<std::mutex> lock(mutex);
    MH_Uninitialize();
    HookManager::RestoreImGui();
    ImFX::CleanupFX();
    if (MH_Initialized())
        MH_Uninitialize();

    HookManager::RestoreImGui();
    ImFX::CleanupFX();

    if (configMgr) {
        configMgr->saveConfig();
        delete configMgr;
        configMgr = nullptr;
    }

    if (moduleMgr) {
        delete moduleMgr;
        moduleMgr = nullptr;
    }

    if (cmdMgr) {
        delete cmdMgr;
        cmdMgr = nullptr;
    }

    if (prefixMgr) {
        delete prefixMgr;
        prefixMgr = nullptr;
    }
    Notch::closeConsole();
    AudioSystem::getInstance().play(xorstr_("Audios\\uninject.wav"));
    winrt::Windows::ApplicationModel::Core::CoreApplication::MainView().CoreWindow().Dispatcher().RunAsync(winrt::Windows::UI::Core::CoreDispatcherPriority::Normal, []() {
        winrt::Windows::UI::ViewManagement::ApplicationView::GetForCurrentView().Title(L"");
        });

#if _DEBUG
#else
    if (Game.getLocalPlayer() != nullptr) Game.getLocalPlayer()->displayClientMessage("%sEjected!", RED);
#endif
    Sleep(200);
    FreeLibraryAndExitThread(lpParam, 0);
 };
void Notch::initialize() {
    Run::running = true;
    init();
    InjectTime = TimeUtil::getCurrentMs();
    FileSystem::Initalize();
    AudioSystem::getInstance().play(xorstr_("Audios\\inject.wav"));

    Notch::openConsole();
    logF("MC Version " + getMCVersion(), "INFO");
    logF(xorstr_("Initializing Hooks"), xorstr_("WAIT"));
    if (MH_Initialize() == MH_OK) {
        MH_Initialized() = true;
        HookManager::initImGui();
        HookManager::init();
   }
    logF(xorstr_("ClientInstance"), Game.getClientInstance() == nullptr ? xorstr_("NULLPTR") : xorstr_("NOT NULLPTR"));
    if (Game.getClientInstance() != nullptr) 
        logF(xorstr_("GuiData"), Game.getGuiData() == nullptr ? xorstr_("NULLPTR") : xorstr_("NOT NULLPTR"));
    winrt::Windows::ApplicationModel::Core::CoreApplication::MainView().CoreWindow().Dispatcher().RunAsync(winrt::Windows::UI::Core::CoreDispatcherPriority::Normal, []() {
        winrt::Windows::UI::ViewManagement::ApplicationView::GetForCurrentView().Title(L"Notch");
        });
    logF(Memory::combine("ClientInstance Found at: ", Game.getClientInstance()->VTable), "INFO")
    Sleep(10);
    logF("Initializing modules.", "WAIT");
    moduleMgr->initModules();
    logF("Initialized Modules", "OKAY");
    configMgr->loadConfig("default");
    logF("Initializing Commands.", "WAIT");
    cmdMgr->initCommands();
    logF("Initialized Commands", "OKAY");
    logF("Initialized Client", "OKAY");
#if _DEBUG
#else
    static Actor* lp = Game.getLocalPlayer();
    static GuiData* gu = Game.getGuiData();
    if (lp != nullptr) {
        logF("LocalPlayer", "NOT NULLPTR");
        lp->displayClientMessage("%sInjected!", GREEN);
        lp->displayClientMessage("NameTag: %s%s", YELLOW, lp->getNameTag());
        Vec3 Pos = lp->getPosition();
        lp->displayClientMessage("XYZ: %i, %i, %i", (int)Pos.x, (int)Pos.y, (int)Pos.z);
        if (gu != nullptr)
            lp->displayClientMessage("WindowSizeReal: %i, %i", (int)Game.getGuiData()->realSize.x, (int)Game.getGuiData()->realSize.y);
    }
    else if (lp == nullptr) {
        logF("LocalPlayer", "NULLPTR");
    };
#endif
};

std::string Notch::getMCVersion() {
    char filePath[MAX_PATH];
    if (GetModuleFileNameExA(GetCurrentProcess(), nullptr, filePath, MAX_PATH)) {
        DWORD size = GetFileVersionInfoSizeA(filePath, nullptr);
        BYTE* ver = new BYTE[size];
        VS_FIXEDFILEINFO* pFileInfo;
        if (GetFileVersionInfoA(filePath, 0, size, ver)) {
            if (VerQueryValue(ver, TEXT("\\"), (LPVOID*)&pFileInfo, nullptr)) {
                std::ostringstream oss;
                oss << HIWORD(pFileInfo->dwFileVersionMS) << '.'
                    << LOWORD(pFileInfo->dwFileVersionMS) << '.'
                    << HIWORD(pFileInfo->dwFileVersionLS) << '.'
                    << LOWORD(pFileInfo->dwFileVersionLS);
                return oss.str();
            }
        }
    }
    return "Unknown";
}

Vec2 ClientInstance::getMousePos() {
    return Game.mousepos;
};