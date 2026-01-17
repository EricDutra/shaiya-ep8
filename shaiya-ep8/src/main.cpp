#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include "include/packets/character_list.h"

void init()
{
    packets::character_list::hook();
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls(hModule);
            init();
            break;
    }

    return TRUE;
}