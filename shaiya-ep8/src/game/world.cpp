#include "include/game/world.h"
#include "include/utils/memory.h"

namespace game::world
{
    std::unordered_map<int, CUser*> users;
    std::shared_mutex users_mutex;

    void __fastcall enter(CUser* user)
    {
        std::unique_lock lock(users_mutex);

        users[user->userId] = user;
    }

    void __fastcall leave(CUser* user)
    {
        std::unique_lock lock(users_mutex);

        users.erase(user->userId);
    }

    std::vector<CUser*> snapshot()
    {
        std::shared_lock lock(users_mutex);

        std::vector<CUser*> list;
        list.reserve(users.size());

        for (auto& [id, user] : users)
            list.push_back(user);

        return list;
    }

    const uintptr_t enter_world_return = 0x00455B18;

    // 00455B00 - CUser::EnterWorld
    NAKED void enter_world_hook()
    {
        __asm {
            pushad
            mov ecx, edi
            call game::world::enter
            popad

            cmp byte ptr [edi + 0x5808], 0x0A
            jmp enter_world_return
        }
    }

    const uintptr_t logout_user_return = 0x00413EB1;

    // 00413E90 - CWorld::LogoutUser
    NAKED void logout_user_hook()
    {
        __asm {
            pushad
            mov ecx, ebp
			call game::world::leave
            popad

            lea eax, [ebp + 0x6284]

            jmp logout_user_return
        }
	}

    void hook()
    {
        utils::memory::hook((void*)0x00455B18, enter_world_hook, 7);
        utils::memory::hook((void*)0x00413EAB, logout_user_hook, 6);
    }
}