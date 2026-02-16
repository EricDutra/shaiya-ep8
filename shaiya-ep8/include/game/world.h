#pragma once
#include <unordered_map>
#include <shared_mutex>
#include "include/shaiya/CUser.h"

using namespace shaiya;

namespace game::world
{
	extern std::unordered_map<int, CUser*> users;
	extern std::shared_mutex users_mutex;

	void __fastcall enter(CUser* user);
	void __fastcall leave(CUser* user);

    std::vector<CUser*> snapshot();

    template<typename Predicate, typename Func>
    inline void for_each_if(Predicate pred, Func func)
    {
        for (CUser* user : snapshot())
        {
            if (user && pred(user))
                func(user);
        }
    }

	void hook();
}