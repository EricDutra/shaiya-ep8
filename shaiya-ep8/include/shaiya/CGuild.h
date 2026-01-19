#pragma once
#include <cstdint>
#include "include/shaiya/CItem.h"

namespace shaiya
{
#pragma pack(push, 1)
    struct CGuild
    {
        uint32_t unk[2];

        uint32_t id;

        char     name[25];
        char     leader_name[23];

        uint32_t admin_count;
        uint32_t faction;
        uint32_t points;

        uint8_t  rank;

        uint32_t etin;
        uint32_t keep_etin;

        bool     has_house;
        bool     bought_house;

        char     message[65];

        uint32_t ranking_points;
        uint32_t etin_return_count;
        uint32_t rank_join_count;

        CItem* deposit_item[240];
    };
#pragma pack(pop)
}