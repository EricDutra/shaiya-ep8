#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include "include/packets/character_list.h"

void main()
{
    packets::character_list::hook();
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
        case DLL_PROCESS_ATTACH:
            //DisableThreadLibraryCalls(hModule);
            //main();
            ::CreateThread(0, 0, (LPTHREAD_START_ROUTINE)main, 0, 0, 0);
            break;

        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
            break;
    }

    return TRUE;
}