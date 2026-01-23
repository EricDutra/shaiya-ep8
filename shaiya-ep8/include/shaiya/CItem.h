#pragma once
#include <array>
#include "include/packets/packet.h"

using namespace packets;

namespace shaiya
{
#pragma pack(push, 1)
    struct Item
    {
        uint8_t type;
        uint8_t typeId;
        uint8_t count;
    };

    struct CharacterItem
    {
        PacketType opcode;
        uint8_t item_count;
        uint8_t bag;
        uint8_t slot;
        uint8_t type;
        uint8_t type_id;
        uint16_t quality;
        uint32_t gem[6];
        uint8_t count = 0;
        char craftname[20];
        uint8_t unk[23];
        uint8_t is_dyed = 0;
        uint8_t unk2[27];
    };

    enum struct ItemEffect : uint8_t
    {
        HypnosisCure = 1,
        StunCure,
        SilenceCure,
        DarknessCure,
        StopCure,
        SlowCure,
        ProtectedFaint,
        ProtectedDeath,
        VenomCure,
        DiseaseCure,
        DisorderCure,
        ArcanePotion = 17,
        CurePotion,
        DispelPotion,
        AbolishingPotion,
        BlessingPotion,
        HolyPotion,
        PerfectCure = 26,
        GoddessBlessing = 30,
        PartyMemberSummon,
        PartyMemberMoveTo,
        SkillReset,
        StatReset,
        WarehouseRecall,
        LinkingHammer,
        Resurrection,
        MessageToServer,
        Teleportation,
        RepairHammer,
        TargetResurrect,
        ItemCreate,
        IncreaseFame,
        AppearanceChange,
        SexChange,
        Firework,
        CapitalRecall,
        BootleggeryRecall,
        ArenaRecall,
        ExpRemoval,
        NameChange,
        Etin1,
        Etin10,
        Etin100,
        Etin1000,
        GuildHouseRecall,
        LuckyCharm,
        ExtractionHammer,
        MoveWar,
        ItemCompose = 62,
        EnergyCrystal,
        EquipMale,
        EquipFemale,
        PerfectLinkingHammer = 69,
        MobGen = 73,
        PremiumLapisiaLv1 = 76,
        PremiumLapisiaLv2,
        PremiumLapisiaLv3,
        CrowleyEssence = 85,
        ItemComposeStr,
        ItemComposeDex,
        ItemComposeInt,
        ItemComposeWis,
        ItemComposeRec,
        ItemComposeLuc,
        CrowleyLiquid,
        ItemRemakeStr,
        ItemRemakeDex,
        ItemRemakeInt,
        ItemRemakeWis,
        ItemRemakeRec,
        ItemRemakeLuc,
        ChaoticSquare,
        DungeonMap,
        CraftingHammer = 102,
        SafetyCharm,
        TownMoveScroll,
        ItemAbilityTransfer,
        Catalyst,
        EnchantEnhancer,
        Dye = 110,
        HaloReactor,
        Spellbook,
        EternalContinuousResurrect,
        EternalPreventItemDrop,
        EternalPreventExpDrop,
        TyrosStone,
        AbsoluteRecreationRune,
        NpcRecall = 200,
        Item500 = 210,
        PetGold = 212,
        PetItem,
        PetGoldItem
    };

    enum struct RealType : uint32_t
    {
        OneHandedSword = 1,
        TwoHandedSword,
        OneHandedAxe,
        TwoHandedAxe,
        DualWeapon,
        Spear,
        OneHandedBlunt,
        TwoHandedBlunt,
        ReverseDagger,
        Dagger,
        Javelin,
        Staff,
        Bow,
        Crossbow,
        Knuckles,
        Helmet,
        UpperArmor,
        LowerArmor,
        Shield,
        Gloves,
        Shoes,
        Ring,
        Necklace,
        Cloak,
        Bracelet,
        Teleportation,
        Quest
    };

    enum struct MarketType : uint8_t
    {
        TwoHandedWeapon = 1,
        OneHandedWeapon,
        DualWeapon,
        Spear,
        HeavyWeapon,
        Knuckles,
        Dagger,
        Staff,
        Bow,
        Projectile,
        Helmet,
        UpperArmor,
        LowerArmor,
        Gloves,
        Shoes,
        Cloak,
        Shield,
        Necklace,
        Ring,
        Bracelet,
        Lapis,
        Lapisian,
        Other,
        Mount,
        HighQuality
    };

    struct ItemInfo
    {
        uint32_t itemId;                  // 0x00
        char itemName[32];                // 0x04
        uint8_t type;                     // 0x24
        uint8_t typeId;                   // 0x25
        uint8_t country;                  // 0x26
        bool attackFighter;               // 0x27
        bool defenseFighter;              // 0x28
        bool patrolRogue;                 // 0x29
        bool shootRogue;                  // 0x2A
        bool attackMage;                  // 0x2B
        bool defenseMage;                 // 0x2C
        uint8_t unk;                      // 0x2D
        uint16_t level;                   // 0x2E
        uint8_t grow;                     // 0x30

        enum struct ReqOg : uint8_t
        {   // 0x31
            Tradable,
            AccountBound,
            CharacterBound
        } reqOg;

        uint8_t reqIg;                    // 0x32
        uint8_t unk2;                     // 0x33
        uint16_t reqVg;                   // 0x34
        uint16_t reqStr;                  // 0x36
        uint16_t reqDex;                  // 0x38
        uint16_t reqRec;                  // 0x3A
        uint16_t reqInt;                  // 0x3C
        uint16_t reqWis;                  // 0x3E
        uint16_t reqLuc;                  // 0x40
        uint16_t range;                   // 0x42
        uint8_t attackTime;               // 0x44
        uint8_t attribute;                // 0x45
        ItemEffect effect;                // 0x46
        uint8_t slotCount;                // 0x47
        uint8_t speed;                    // 0x48
        uint8_t exp;                      // 0x49
        uint8_t composeCount;             // 0x4A
        uint8_t count;                    // 0x4B
        uint16_t maxQuality;              // 0x4C
        uint16_t midQuality;              // 0x4E
        uint16_t lowQuality;              // 0x50
        uint16_t maxAtkPower;             // 0x52
        uint16_t maxAtkPowerMidQ;         // 0x54
        uint16_t maxAtkPowerLowQ;         // 0x56
        uint16_t minAtkPower;             // 0x58
        uint16_t minAtkPowerMidQ;         // 0x5A
        uint16_t minAtkPowerLowQ;         // 0x5C
        uint16_t defense;                 // 0x5E
        uint16_t defenseMidQ;             // 0x60
        uint16_t defenseLowQ;             // 0x62
        uint16_t resistance;              // 0x64
        uint16_t resistanceMidQ;          // 0x66
        uint16_t resistanceLowQ;          // 0x68
        uint16_t health;                  // 0x6A
        uint16_t stamina;                 // 0x6C
        uint16_t mana;                    // 0x6E
        uint16_t strength;                // 0x70
        uint16_t dexterity;               // 0x72
        uint16_t reaction;                // 0x74
        uint16_t intelligence;            // 0x76
        uint16_t wisdom;                  // 0x78
        uint16_t luck;                    // 0x7A
        uint16_t itemDropGrade;           // 0x7C
        uint16_t itemDropLimit;           // 0x7E
        uint32_t buy;                     // 0x80
        uint32_t sell;                    // 0x84
        uint8_t unk3[4];                  // 0x88
        uint32_t itemDropCount;           // 0x8C
        uint8_t unk4[4];                  // 0x90
        uint32_t itemDropDelay;           // 0x94
        uint32_t itemDropEnableTick;      // 0x98
        uint8_t unk5[4];                  // 0x9C
        RealType realType;                // 0xA0
        MarketType marketType;            // 0xA4
        uint8_t unk6[3];                  // 0xA5
    }; // size: 0xA8

    struct CItem
    {
        uint8_t unk[48];                  // 0x00
        ItemInfo* itemInfo;               // 0x30
        uint32_t unk2;                    // 0x38 
        uint64_t itemUid;                 // 0x3C
        uint8_t type;                     // 0x44
        uint8_t typeId;                   // 0x45
        uint8_t count;                    // 0x46
        uint8_t unk3;                     // 0x47
        uint16_t quality;                 // 0x48
        uint8_t gem[6];                   // 0x4A
        char craftname[20];               // 0x50
        uint32_t makeTime;                // 0x64
        uint8_t makeType;                 // 0x68
        char _[31];                       // 0x69
        uint16_t craftStats[9];           // 0x88
        uint16_t defLapisia;              // 0x9A
        uint16_t atkLapisia;              // 0x9C

        uint32_t GetItemId() { return type * 1000 + typeId; }

        ItemInfo* GetItemInfo(uint32_t itemType, uint32_t itemTypeId);
    };
#pragma pack(pop)
}