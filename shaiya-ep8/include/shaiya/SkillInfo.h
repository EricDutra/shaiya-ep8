#pragma once
#include <array>

namespace shaiya
{
    enum struct Attribute : uint8_t
    {
        None,
        Fire1,
        Water1,
        Earth1,
        Wind1,
        Fire2,
        Water2,
        Earth2,
        Wind2
    };

    enum struct SkillTargetType : uint8_t
    {
        None,
        Trap,
        Caster,
        Target,
        AlliesNearCaster,
        Allies,
        EnemiesNearCaster,
        EnemiesNearTarget
    };

    enum struct SkillDebuffType : uint8_t
    {
        None,
        Sleep,
        Unconscious,
        Silence,
        Darkness,
        Pause,
        Slow,
        Dying,
        Death,
        Poison,
        Illness,
        Delusion,
        Doom,
        Fear,
        Dull,
        Misfortune
    };

    enum struct SkillAbilityType : uint8_t
    {
        MaxHealth = 1,
        MaxMana,
        MaxStamina,
        AbilityStrength,
        AbilityReaction,
        AbilityIntelligence,
        AbilityWisdom,
        AbilityDexterity,
        AbilityLuck,
        AddHpRecovery,
        AddSpRecovery,
        AddMpRecovery,
        DecreaseSpCostPercentage,
        DecreaseMpCostPercentage,
        AbilityAttackRange,
        AbilityAttackSpeed,
        AbilityMoveSpeed,
        AbilityCriticalHitRate,
        DecreaseSkillResetTime,
        AbilityHitRate,
        AbilityRangedHitRate,
        AbilityMagicHitRate,
        AbilityAttackPower,
        AbilityRangedAttackPower,
        AbilityMagicPower,
        AbilityAddDefense,
        AbilityAddRangedDefense,
        AbilityAddMagicResistance,
        AbilityEvasionRate,
        AbilityRangedEvasionRate,
        AbilityMagicEvasionRate,
        AttackBlinded,
        RangedAttackBlinded,
        Silenced,
        MultiplyExp,
        EternalEndurance,
        PreventItemDrop,
        PreventExpLoss,
        RecallWarehouse,
        WhiteTigerCharm,
        BlueDragonCharm,
        RedPhoenixCharm,
        DoubleWarehouse,
        IncreaseGoldDrop,
        PreventEquipmentDrop,
        ContinuousResurrection,
        BattlefieldRune,
        AbilityAbsorption,
        AbilityStrRecIntWisDexLuc,
        EnableEnterDungeon,
        DisableEnterDungeon,
        StrToMaxHealth,
        RecToMaxHealth,
        IntToMaxHealth,
        WisToMaxHealth,
        DexToMaxHealth,
        LucToMaxHealth,
        DecreaseHpByPercentage = 70,
        AbilityAddDefensePercentage = 73,
        AbilityAddRangedDefensePercentage,
        AbilityAddMagicResistancePercentage = 78,
        MultiplyQuestExp = 87
    };

#pragma pack(push, 1)
    struct NeedWeapon
    {
        bool oneHandedSword;    // 0x00
        bool twoHandedSword;    // 0x01
        bool oneHandedAxe;      // 0x02
        bool twoHandedAxe;      // 0x03
        bool dualWeapon;        // 0x04
        bool spear;             // 0x05
        bool oneHandedBlunt;    // 0x06
        bool twoHandedBlunt;    // 0x07
        bool reverseDagger;     // 0x08
        bool dagger;            // 0x09
        bool javelin;           // 0x0A
        bool staff;             // 0x0B
        bool bow;               // 0x0C
        bool crossbow;          // 0x0D
        bool knuckles;          // 0x0E
        bool shield;            // 0x0F
    };

    struct SkillAbility
    {
        SkillAbilityType type;  // 0x00
        uint8_t _;              // 0x01
        uint16_t value;         // 0x02
    };

    struct SkillInfo
    {
        uint16_t skillId;               // 0x00
        uint8_t skillLv;                // 0x02
        char skillName[32];             // 0x03
        uint8_t _;                      // 0x23
        uint16_t reqLevel;              // 0x24
        uint8_t country;                // 0x26
        bool attackFighter;             // 0x27
        bool defenseFighter;            // 0x28
        bool patrolRogue;               // 0x29
        bool shootRogue;                // 0x2A
        bool attackMage;                // 0x2B
        bool defenseMage;               // 0x2C
        uint8_t grow;                   // 0x2D
        uint8_t skillPoint;             // 0x2E
        uint8_t typeShow;               // 0x2F
        uint8_t typeAttack;             // 0x30
        uint8_t typeEffect;             // 0x31
        uint16_t typeDetail;            // 0x32
        NeedWeapon needWeapon;          // 0x34
        uint16_t stamina;               // 0x44
        uint16_t mana;                  // 0x46
        uint16_t readyTime;             // 0x48
        uint16_t resetTime;             // 0x4A
        uint8_t attackRange;            // 0x4C
        SkillDebuffType debuffType;     // 0x4D
        Attribute attribute;            // 0x4E
        uint8_t unk;                    // 0x4F
        bool disable;                   // 0x50
        uint8_t unk2;                   // 0x51
        uint16_t prevSkillId;           // 0x52
        uint8_t successType;            // 0x54
        uint8_t successValue;           // 0x55
        SkillTargetType targetType;     // 0x56
        uint8_t applyRange;             // 0x57
        uint8_t multiAttack;            // 0x58
        uint8_t _unk3[3];               // 0x59
        uint32_t keepTime;              // 0x5C
        uint8_t weapon1;                // 0x60
        uint8_t weapon2;                // 0x61
        uint8_t weaponValue;            // 0x62
        uint8_t bag;                    // 0x63
        uint16_t aggro;                 // 0x64
        uint16_t damageType;            // 0x66
        uint16_t damageHealth;          // 0x68
        uint16_t damageStamina;         // 0x6A
        uint16_t damageMana;            // 0x6C
        uint8_t timeDmgType;            // 0x6E
        uint8_t unk3;                   // 0x6F
        uint16_t timeDmgHealth;         // 0x70
        uint16_t timeDmgStamina;        // 0x72
        uint16_t timeDmgMana;           // 0x74
        uint16_t addDmgHealth;          // 0x76
        uint16_t addDmgStamina;         // 0x78
        uint16_t addDmgMana;            // 0x7A

        std::array<SkillAbility, 3> abilities; // 0x7C
        uint16_t healHealth;             // 0x88
        uint16_t healStamina;            // 0x8A
        uint16_t healMana;               // 0x8C
        uint16_t timeHealHealth;         // 0x8E
        uint16_t timeHealStamina;        // 0x90
        uint16_t timeHealMana;           // 0x92
        uint8_t defenseType;             // 0x94
        uint8_t defenseValue;            // 0x95
        uint8_t limitHealth;             // 0x96
        uint8_t fixRange;                // 0x97
        uint16_t shapeType;              // 0x98
        uint16_t shapeMobId;             // 0x9A
        uint8_t unk4[8];                 // 0x9C
    };
#pragma pack(pop)
}