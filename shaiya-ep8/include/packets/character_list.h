#pragma once
#include <cstdint>
#include "include/shaiya/CUser.h"
#include "include/packets/packet.h"

using namespace shaiya;

namespace packets
{
	namespace character_list
	{

#pragma pack(push, 1)

        struct Character
        {
            uint16_t opcode; // 0x0101
            uint8_t  slot;
            uint32_t charId;
            uint32_t creationTime;

            uint16_t level;
            uint8_t  family;
            uint8_t  mode;
            uint8_t  hair;
            uint8_t  face;
            uint8_t  height;
            uint8_t  job;
            uint8_t  gender;

            uint16_t map;

            uint16_t strength;
            uint16_t dexterity;
            uint16_t resistance;
            uint16_t intelligence;
            uint16_t wisdom;
            uint16_t luck;

            uint8_t  unk[6];

            uint8_t  helmetType;
            uint8_t  armorType;
            uint8_t  pantsType;
            uint8_t  gloveType;
            uint8_t  bootType;
            uint8_t  weaponType;
            uint8_t  shieldType;
            uint8_t  capeType;

            uint8_t  unk2[6];

            uint8_t  petType;
            uint8_t  costumeType;
            uint8_t  wingType;

            uint8_t  helmetTypeID;
            uint8_t  armorTypeID;
            uint8_t  pantsTypeID;
            uint8_t  gloveTypeID;
            uint8_t  bootTypeID;
            uint8_t  weaponTypeID;
            uint8_t  shieldTypeID;
            uint8_t  capeTypeID;

            uint8_t  unk3[6];

            uint8_t  petTypeID;
            uint8_t  costumeTypeID;
            uint8_t  wingTypeID;

            uint8_t  unk4[540];

            char     name[19];

            uint8_t  deleteFlag;
            uint8_t  renameFlag;
        };

#pragma pack(pop)

        void send(CUser* user, Packet* old_packet);
        void hook();
	}
}