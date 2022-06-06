#include "pch.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        if (!Core::EnsureSelfReference(hModule)) return FALSE;
        DisableThreadLibraryCalls(hModule);

        std::thread thr([] 
            {
                // Do init and runtime
                
                globalvars::g_LogInstance = std::make_unique<Log>("ScriptHookRDR2.log");
                globalvars::g_CoreInstance = std::make_unique<Core>();

                globalvars::g_LogInstance->Write("hello {}", "master");

                if (globalvars::g_CoreInstance == nullptr) return FALSE;

                globalvars::g_CoreInstance->Init();

                while (globalvars::g_Running) {
                    if (GetAsyncKeyState(VK_END))
                        globalvars::g_Running = false;
                    std::this_thread::yield();
                }

                // Unload process
                MessageBeep(0xFFFFF); // for testing purposes
                globalvars::g_CoreInstance->Uninit();
                globalvars::g_CoreInstance.reset();
                globalvars::g_LogInstance.reset();
                Core::DeleteSelfReference();
            });

        thr.detach();
    }
    return TRUE;
}

