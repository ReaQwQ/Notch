#include "Notch.h"

DWORD APIENTRY Notch::ejectThread(HMODULE lpParam) {
    while (Run::running) {
        Sleep(10);
    }
    MH_Uninitialize();
    HookManager::RestoreImGui();
    ImFX::CleanupFX();
    configMgr->saveConfig();
    delete moduleMgr;
    delete configMgr;
    delete cmdMgr;
    delete prefixMgr;
    Notch::closeConsole();
    AudioSystem::getInstance().play(xorstr_("Audios\\uninject.wav"));
    winrt::Windows::ApplicationModel::Core::CoreApplication::MainView().CoreWindow().Dispatcher().RunAsync(winrt::Windows::UI::Core::CoreDispatcherPriority::Normal, []() {
        winrt::Windows::UI::ViewManagement::ApplicationView::GetForCurrentView().Title(L"");
        });
#if _DEBUG
#else
    static Actor* lp = Game.getClientInstance()->getLocalPlayer();
    if (lp != nullptr) lp->displayClientMessage("%sEjected!", RED);
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

    logF(xorstr_("Initializing Hooks"), xorstr_("WAIT"));
    if (MH_Initialize() == MH_OK) {
        HookManager::initImGui();
        HookManager::init();
   }
    logF(xorstr_("ClientInstance"), Game.getClientInstance() == nullptr ? xorstr_("NULLPTR") : xorstr_("NOT NULLPTR"));
    if (Game.getClientInstance() != nullptr) 
        logF(xorstr_("GuiData"), Game.getGuiData() == nullptr ? xorstr_("NULLPTR") : xorstr_("NOT NULLPTR"));
    winrt::Windows::ApplicationModel::Core::CoreApplication::MainView().CoreWindow().Dispatcher().RunAsync(winrt::Windows::UI::Core::CoreDispatcherPriority::Normal, []() {
        winrt::Windows::UI::ViewManagement::ApplicationView::GetForCurrentView().Title(L"NotchHack");
        });
    
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