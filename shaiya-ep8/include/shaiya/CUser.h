#pragma once
#include <cstdint>
#include <array>
#include "include/shaiya/SSyncList.h"
#include "include/shaiya/SConnection.h"
#include "include/shaiya/CItem.h"
#include "include/shaiya/CGuild.h"
#include "include/shaiya/CSkill.h"
#include "include/shaiya/CQuest.h"
#include "include/shaiya/CMiniGame.h"
#include "include/shaiya/CFriend.h"
#include "include/shaiya/SVector.h"

namespace shaiya
{
#pragma pack(push, 1)

    struct UserQuickSlot
    {
        uint8_t bag;
        uint8_t slot;
        uint8_t srcBag;
        uint8_t _;
        uint16_t srcSlot;
    };

    enum struct UserAttribute : uint32_t
    {
        None,
        Fire,
        Water,
        Earth,
        Wind,
        Fire2,
        Water2,
        Earth2,
        Wind2
    };

    enum struct UserAttackType : uint32_t
    {
        None,
        Basic,
        Skill
    };

    enum struct UserPvPStatus : uint32_t
    {
        None,
        RequestSent,
        RequestReceived,
        Countdown,
        Start,
        Exchange
    };

    enum struct UserWhere : uint32_t
    {
        Default,
        WorldLeave,
        ZoneWait,
        ZoneLeave,
        ZoneEnter
    };

    struct CUser
    {
        SConnection connection;               // 0x0000

        float posX;                           // 0x00D0
        float posY;                           // 0x00D4
        float posZ;                           // 0x00D8

        uint32_t id;                          // 0x00DC
        uint32_t zone;                        // 0x00E0

        uint8_t  unk[68];                     // 0x00E4

        uint32_t charId;                      // 0x0128
        uint8_t  slot;                        // 0x012C
        uint8_t  faction;                     // 0x012D
        uint8_t  family;                      // 0x012E
        uint8_t  grow;                        // 0x012F
        uint8_t  maxGrow;                     // 0x0130
        uint8_t  hair;                        // 0x0131
        uint8_t  face;                        // 0x0132
        uint8_t  height;                      // 0x0133
        uint8_t  job;                         // 0x0134
        uint8_t  gender;                      // 0x0135

        uint16_t level;                       // 0x0136
        uint16_t statPoints;                  // 0x0138
        uint16_t skillPoints;                 // 0x013A

        uint32_t exp;                         // 0x013C
        uint32_t gold;                        // 0x0140

        uint8_t  unk2[4];                     // 0x0144

        uint32_t kills;                       // 0x0148
        uint32_t deaths;                      // 0x014C
        uint32_t victories;                   // 0x0150
        uint32_t defeats;                     // 0x0154
        uint32_t killRank;                    // 0x0158
        uint32_t deathRank;                   // 0x015C

        uint16_t map;                         // 0x0160
        uint16_t direction;                   // 0x0162
        uint16_t hg;                          // 0x0164
        uint16_t vg;                          // 0x0166
        uint8_t  cg;                          // 0x0168
        uint8_t  og;                          // 0x0169
        uint16_t ig;                          // 0x016A

        uint16_t strength;                    // 0x016C
        uint16_t dexterity;                   // 0x016E
        uint16_t intelligence;                // 0x0170
        uint16_t wisdom;                      // 0x0172
        uint16_t resistance;                  // 0x0174
        uint16_t luck;                        // 0x0176

        uint32_t maxHP;                       // 0x0178
        uint32_t maxMP;                       // 0x017C
        uint32_t maxSP;                       // 0x0180

        char    name[21];                     // 0x0184

        uint8_t  itemQualityLv[13];           // 0x0199
        uint16_t itemQuality[13];             // 0x01A6

        std::array<CItem*, 24> equipment;     // 0x01C0
        std::array<std::array<CItem*, 24>, 5> inventory;
        std::array<CItem*, 240> warehouse;    // 0x0400
        std::array<Item, 240> bank;           // 0x07C0

        SSyncList<CSkill> applySkills;        // 0x0A90
        uint32_t skillCount;                  // 0x0ABC
        std::array<CSkill*, 256> skills;      // 0x0AC0

        uint32_t quickSlotCount;              // 0x0EC0
        std::array<UserQuickSlot, 128> quickSlots; // 0x0EC4

        SSyncList<CQuest> completedQuests;     // 0x11C4
        SSyncList<CQuest> quests;

        uint32_t abilityStr;
        uint32_t abilityDex;
        uint32_t abilityInt;
        uint32_t abilityWis;
        uint32_t abilityRec;
        uint32_t abilityLuc;                  // 0x1230

        uint32_t HP;                          // 0x1234
        uint32_t MP;                          // 0x1238
        uint32_t SP;                          // 0x123C

        uint32_t combatHpRecovery;             // 0x1240
        uint32_t combatSpRecovery;             // 0x1244
        uint32_t combatMpRecovery;             // 0x1248
        uint32_t sitHpRecovery;                // 0x124C
        uint32_t sitSpRecovery;                // 0x1250
        uint32_t sitMpRecovery;                // 0x1254
        uint32_t addHpRecovery;                // 0x1258
        uint32_t addSpRecovery;                // 0x125C
        uint32_t addMpRecovery;                // 0x1260
        uint32_t healthRecovery;               // 0x1264
        uint32_t staminaRecovery;              // 0x1268
        uint32_t manaRecovery;                 // 0x126C

        enum struct RecoveryType : uint32_t
        {
            Sit,
            Normal,
            Combat
        } recoveryType;                        // 0x1270

        uint32_t decreaseMpCostPercentage;     // 0x1274
        uint32_t decreaseSpCostPercentage;     // 0x1278

        UserAttribute weaponAttribute;         // 0x127C
        UserAttribute armorAttribute;          // 0x1280

        uint8_t  unk3[92];                        // 0x1284

        uint32_t attackPowerAdd;               // 0x12E0
        uint32_t maxAttackPowerAdd;            // 0x12E4
        uint32_t addDefense;                   // 0x12E8
        uint32_t addMagicResistance;           // 0x12EC
        uint32_t abilityAttackRange;           // 0x12F0
        uint32_t abilityAttackSpeed;           // 0x12F4
        uint32_t abilityMoveSpeed;             // 0x12F8
        uint32_t abilityCriticalHitRate;       // 0x12FC
        uint32_t decreaseSkillResetTime;       // 0x1300
        uint32_t abilityAbsorption;            // 0x1304
        uint32_t interpretationLv;             // 0x1308

        uint32_t bagsUnlocked;
        uint8_t  unk4[116];

        uint32_t abilityHitRate;               // 0x1384
        uint32_t abilityAttackPower;           // 0x1388
        uint32_t abilityEvasionRate;           // 0x138C
        uint32_t abilityAddDefense;            // 0x1390
        uint32_t abilityRangedHitRate;         // 0x1394
        uint32_t abilityRangedAttackPower;     // 0x1398
        uint32_t abilityRangedEvasionRate;     // 0x139C
        uint32_t abilityAddRangedDefense;      // 0x13A0
        uint32_t abilityMagicHitRate;          // 0x13A4
        uint32_t abilityMagicPower;            // 0x13A8
        uint32_t abilityMagicEvasionRate;      // 0x13AC
        uint32_t abilityAddMagicResistance;    // 0x13B0

        uint32_t attackBlinded;                // 0x13B4
        uint32_t evasionStatus;                // 0x13B8
        uint32_t evasionPercentage;            // 0x13BC
        uint32_t mirrorSkillId;                // 0x13C0
        uint32_t mirrorSkillLv;                // 0x13C4
        uint32_t hitRate;                      // 0x13C8
        uint32_t minPhysicalAttack;            // 0x13CC
        uint32_t evasionRate;                  // 0x13D0
        uint32_t physicalDefence;              // 0x13D4
        uint32_t criticalHitRate;              // 0x13D8

        uint8_t  unk5[4];                         // 0x13DC

        uint32_t rangedAttackBlinded;          // 0x13E0
        uint32_t rangedEvasionStatus;          // 0x13E4
        uint32_t rangedEvasionPercentage;      // 0x13E8
        uint32_t rangedMirrorSkillId;          // 0x13EC
        uint32_t rangedMirrorSkillLv;          // 0x13F0
        uint32_t rangedHitRate;                // 0x13F4
        uint32_t minRangeAttack;               // 0x13F8
        uint32_t rangedEvasionRate;            // 0x13FC
        uint32_t rangedDefense;                // 0x1400
        uint32_t rangedCriticalHitRate;        // 0x1404

        uint8_t  unk6[4];                         // 0x1408

        uint32_t silenced;                     // 0x140C
        uint32_t magicEvasionStatus;           // 0x1410
        uint32_t magicEvasionCounter;          // 0x1414
        uint32_t magicMirrorSkillId;           // 0x1418
        uint32_t magicMirrorSkillLv;           // 0x141C
        uint32_t magicHitRate;                 // 0x1420
        uint32_t minMagicAttack;               // 0x1424
        uint32_t magicEvasionRate;             // 0x1428
        uint32_t magicResist;                  // 0x142C
        uint32_t magicCriticalHitRate;         // 0x1430

        uint8_t  unk7[16];

        uint32_t status;
        uint8_t  unk8[4];
        uint8_t  movementStatus;
        uint8_t  unk9[2];

        uint32_t running;                      // 0x1450
        uint32_t attacking;                    // 0x1454
        UserAttackType attackType;             // 0x1458
        uint32_t prevSkillUseIndex;            // 0x145C

        uint8_t  unk10[5];

        uint32_t itemQualityDecreaseSlot;      // 0x1464
        uint32_t attackTypeSkillTick;          // 0x1468
        uint32_t attackTypeBasicTick;          // 0x146C
        uint32_t rebirthExpireTick;            // 0x1470
        uint32_t leaderResurrect;               // 0x1474
        uint32_t expLossRate;                  // 0x1478

        uint32_t mountStatus;
        uint8_t  unk11[324];

        uint32_t tradingWith;
        uint8_t  unk12[28];

        bool     tradeButtonOkState;
        uint8_t  unk13[83];

        uint32_t marketStatus;
        uint8_t  unk14[440];

        uint32_t party;
        uint8_t  unk15[8];

        uint32_t guildId;
        uint32_t guildRank;
        uint8_t  unk16[8];

        CGuild* guild;

        uint32_t guildCreate;                  // 0x1814
        CMiniGame miniGame;                    // 0x1818

        uint32_t buddyCount;                   // 0x1838
        CFriend  buddyList[100];               // 0x183C

        uint32_t blockCount;                   // 0x377C
        BlockUser blockList[100];              // 0x3780

        uint32_t buddyRequestSenderId;          // 0x5530
        uint8_t  unk17[76];

        uint32_t joinGuildDisabled;             // 0x5580
        uint32_t grbZoneEnterFlag;              // 0x5584
        uint32_t insZoneEnterFlag;              // 0x5588
        UserPvPStatus pvpStatus;                // 0x558C

        uint32_t pvpRequestExpireTick;          // 0x5590
        uint32_t pvpRequestTargetId;            // 0x5594
        SVector  pvpPos;                        // 0x5598

        uint32_t gvgRequestTargetId;            // 0x55A4
        SVector  gvgPos;                        // 0x55A8
        uint32_t gvgRequestExpireTick;          // 0x55B4

        uint8_t  unk18[8];
        uint8_t  crypto[564];                  // 0x55C0

        UserWhere where;                       // 0x57F4

        uint8_t  unk19[8];
        uint32_t sessionId;

        uint8_t  unk20[4];
        uint32_t adminStatus;

        uint32_t questionId;                   // 0x580C
        uint32_t chatSendToTargetId;            // 0x5810

        uint8_t  isVisible;
        uint8_t  isAttackable;
        uint8_t  unk21[22];

        uint32_t userId;
        uint8_t  unk22[4];

        char     username[21];                 // 0x5834

        uint8_t  unk23[107];

        uint32_t teleportType;
        uint32_t teleportDelay;
        uint32_t teleportMapId;

        float    teleportDestX;
        float    teleportDestY;
        float    teleportDestZ;

        uint8_t  unk24[128];

        uint32_t abilityCharm;
        uint32_t abilityExtraGold;
        uint32_t abilityEndurance;
        uint32_t abilityPreventExpLoss;
        uint32_t abilityPreventItemDrop;
        uint32_t abilityPreventEquipDrop;
        uint32_t abilityWarehouseRecall;
        uint32_t abilityDoubleWarehouse;
        uint32_t abilityPvpExp;

        uint8_t  unk25[4];

        uint32_t abilityContiRes;
        uint8_t  unk26[328];

        uint32_t points;
        uint32_t isBuying;

        uint8_t  unk27[2620];

        void SendItem(CItem* item, uint8_t bag, uint8_t slot);
        void Send(void* packet_ptr, size_t packet_size);
    };
#pragma pack(pop)
}