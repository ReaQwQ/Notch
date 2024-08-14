#include "Notch/Notch.h"

#include <Windows.h>
#include <thread>

bool __stdcall DllMain(const HINSTANCE hinstDLL, const DWORD fdwReason, [[maybe_unused]] LPVOID lpReserved) {
    if (fdwReason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hinstDLL);
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Notch::initialize, hinstDLL, 0, 0);
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Notch::ejectThread, hinstDLL, 0, 0);
    };
   return true;  // Successful DLL_PROCESS_ATTACH
}
