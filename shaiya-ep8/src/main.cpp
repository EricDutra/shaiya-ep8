#include "include/utils/win32_lean.h"
#include "include/packets/handler.h"
#include "include/packets/character/list.h"
#include "include/packets/character/details.h"
#include "include/packets/character/status.h"

void init()
{
    packets::handler::hook();
    packets::character::list::hook();
    packets::character::details::hook();
    packets::character::status::hook();
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