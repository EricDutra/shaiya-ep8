#include "include/utils/win32_lean.h"
#include "include/packets/handler.h"
#include "include/packets/character_list.h"
#include "include/packets/character_details.h"
#include "include/packets/character_status.h"

void init()
{
    packets::handler::hook();
    packets::character_list::hook();
    packets::character_details::hook();
    packets::character_status::hook();
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