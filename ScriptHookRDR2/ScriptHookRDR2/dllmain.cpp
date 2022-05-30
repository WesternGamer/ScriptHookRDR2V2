#include "pch.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        if (!Core::EnsureSelfReference(hModule)) return FALSE;

        std::thread thr([] 
            {
                // Do init and runtime

                while (globalvars::g_Running)
                    std::this_thread::yield();

                // Unload process
                Core::DeleteSelfReference();
            });

        thr.detach();
    }
    return TRUE;
}

