/*
  ==============================================================================

    Items.h
    Created: 20 Apr 2019 7:26:34am
    Author:  Adam Shield

  ==============================================================================
*/

#pragma once
#include "Common.h"
#include <map>
#include <variant>

enum Critical{
    x2,
    x3,
    x4,
    _18_20x2,
    _19_20x2
};

static inline std::function<void()> nullFunc = []()->void{};

enum NumOfHands{
    ZERO,
    ONE,
    TWO
};

struct Item{
    String name;
    NumOfHands numOfHands;
};

namespace Weapons{
    static inline String criticalToString(Critical crit){
        switch(crit){
            case x2: return "x2";
            case x3: return "x3";
            case x4: return "x4";
            case _18_20x2: return "(18-20)x2";
            case _19_20x2: return "(19-20)x2}";
        }
    }
    
    enum WeaponType{
        SIMPLE,
        MARTIAL_LIGHT_MELEE,
        MARTIAL_ONE_HANDED_MELEE,
        MARTIAL_TWO_HANDED_MELEE,
        MARTIAL_RANGED,
        EXOTIC,
        NATURAL
    };
    
    struct Weapon : public Item{
        Die melee;
        Die ranged;
        Critical crit;
        WeaponType type;
        
        Weapon() = default;
        
        Weapon(String Name, Die Melee, Die Ranged, Critical Crit, WeaponType Type, NumOfHands Hands) :
        melee(Melee), ranged(Ranged), crit(Crit), type(Type)
        {
            name = Name;
            numOfHands = Hands;
        }
    };
    
    
    static inline const Weapon  gauntlet        {"gauntlet",        D3, none, x2,       SIMPLE, ONE},
                                unarmed         {"unarmed strike",  D3, none, x2,       SIMPLE, ONE},
                                dagger          {"dagger",          D4, none, _19_20x2, SIMPLE, ONE},
                                daggerPunching  {"punching dagger", D4, none, x3,       SIMPLE, ONE},
                                gauntletSpiked  {"spiked dagger",   D4, none, x3,       SIMPLE, ONE},
                                maceLight       {"light mace",      D6, none, x2,       SIMPLE, ONE},
                                sickle          {"sickle",          D6, none, x2,       SIMPLE, ONE},
                                club            {"club",            D6, none, x2,       SIMPLE, ONE},
                                maceHeavy       {"heavy mace",      D8, none, x2,       SIMPLE, ONE},
                                morningstar     {"morningstar",     D6, none, x2,       SIMPLE, ONE},
                                shortspear      {"shortspear",      D6, none, x2,       SIMPLE, ONE},
                                longspear       {"longspear",       D8, none, x3,       SIMPLE, ONE},
                                quarterstaff    {"quarterstaff",    D6, D6, x2,         SIMPLE, TWO},
                                spear           {"spear",           D8, none, x3,       SIMPLE, ONE},
                                crossbowHeavy   {"heavy crossbow",  none, D10, _19_20x2,SIMPLE, TWO},
                                crossbowLight   {"light crossbow",  none, D8, _19_20x2, SIMPLE, TWO},
                                dart            {"dart",            none, D4, x2,       SIMPLE, TWO},
                                javelin         {"javelin",         none, D6, x2,       SIMPLE, ONE},
                                sling           {"sling",           none, D4, x2,       SIMPLE, TWO},
    
                                axeThrowing     {"throwing axe",    D6, none, x2,       MARTIAL_LIGHT_MELEE, ONE},
                                hammerLight     {"hammer, light",   D4, none, x2,       MARTIAL_LIGHT_MELEE, ONE},
                                handaxe         {"handaxe",         D6, none, x3,       MARTIAL_LIGHT_MELEE, ONE},
                                kukri           {"kukri",           D4, none, _18_20x2, MARTIAL_LIGHT_MELEE, ONE},
                                pickLight       {"pick, light",     D4, none, x4,       MARTIAL_LIGHT_MELEE, ONE},
                                sap             {"sap",             D6, none, x2,       MARTIAL_LIGHT_MELEE, ONE},
                                shortsword      {"shortsword",      D6, none, _19_20x2, MARTIAL_LIGHT_MELEE, ONE},
    
                                battleaxe       {"battleaxe",       D8, none, x3,       MARTIAL_ONE_HANDED_MELEE, ONE},
                                flail           {"flail",           D8, none, x2,       MARTIAL_ONE_HANDED_MELEE, ONE},
                                longsword       {"longsword",       D8, none, x2,       MARTIAL_ONE_HANDED_MELEE, ONE},
                                pickHeavy       {"pick (heavy)",    D8, none, x2,       MARTIAL_ONE_HANDED_MELEE, ONE},
                                rapier          {"rapier",          D6, none, x4,       MARTIAL_ONE_HANDED_MELEE, ONE},
                                scimitar        {"scimitar",        D6, none, _18_20x2, MARTIAL_ONE_HANDED_MELEE, ONE},
                                trident         {"scimitar",        D6, none, _18_20x2, MARTIAL_ONE_HANDED_MELEE, ONE},
                                warhammer       {"scimitar",        D6, none, _18_20x2, MARTIAL_ONE_HANDED_MELEE, ONE},
    
                                falchion        {"falchion",    {2, D4},none, _18_20x2, MARTIAL_TWO_HANDED_MELEE, TWO},
                                flailHeavy      {"flail (heavy)",   D10,none, _19_20x2, MARTIAL_TWO_HANDED_MELEE, TWO},
    //todo last of two handed melee
                                longbow         {"longbow",         D8, none, x3,       MARTIAL_TWO_HANDED_MELEE, TWO},
                                shortbow        {"shortbow",        D6, none, x3,       MARTIAL_TWO_HANDED_MELEE, TWO},
    
    
                                kama            {"kama",            D6, none, x2,       EXOTIC, ONE},
                                nunchaku        {"nunchaku",        D6, none, x2,       EXOTIC, ONE},
                                sai             {"sai",             D4, none, x2,       EXOTIC, ONE},
                                siangham        {"siangham",        D6, none, x2,       EXOTIC, ONE},
                                swordBastard    {"bastard sword",   D10,none, _19_20x2, EXOTIC, ONE},
                                waraxeDwarven   {"dwarven waraxe",  D10,none, x2,       EXOTIC, ONE},
                                whip            {"whip",            D4, none, x2,       EXOTIC, ONE},
                                axeOrcDouble    {"orc double axe",  D8, none, x2,       EXOTIC, TWO},
                                chainSpiked     {"spiked chain", {2,D4},none, x2,       EXOTIC, TWO},
                                flailDire       {"dire flail",      D8, none, x2,       EXOTIC, TWO},
                            hammerGnomeHooked{"gnome hooked hammer",D6, none, x2,       EXOTIC, TWO},
                                swordTwoBladed  {"two bladed sword",D8, none, _19_20x2, EXOTIC, TWO},
                                urgoshDwarven   {"dwarven urgosh",  D6, none, x2,       EXOTIC, TWO},
                                bolash          {"bolash",          D4, none, x2,       EXOTIC, TWO},
                                crossbowHand    {"hand crossbow",   D4, none, _19_20x2, EXOTIC, TWO},
                crossbowHeavyRepeating {"heavy repeating crossbow", D10,none, _19_20x2, EXOTIC, TWO},
                crossbowLightRepeating {"light repeating crossbow", D8, none, _19_20x2, EXOTIC, TWO},
                                shuriken        {"shuriken",        D2, none, x2,       EXOTIC, ONE}
    ;

    inline const Array<Weapon> allWeapons{gauntlet, unarmed, dagger, daggerPunching, gauntletSpiked,
        maceLight, sickle, club, maceHeavy, morningstar, shortspear, longspear, quarterstaff, spear,
        crossbowHeavy,crossbowLight, dart, javelin, sling, axeThrowing, hammerLight, handaxe, kukri,
        pickLight, sap, shortsword, battleaxe, flail, longsword, pickHeavy, rapier, scimitar, trident,
        warhammer, falchion,
        
        kama, nunchaku, sai, siangham, swordBastard, waraxeDwarven, whip, axeOrcDouble, chainSpiked, flailDire,
        hammerGnomeHooked, swordTwoBladed, urgoshDwarven, bolash, crossbowHand, crossbowHeavyRepeating,
        crossbowLightRepeating, shuriken
    };
    
    inline Array<Weapon> getWeaponList(WeaponType weaponType){
        Array<Weapon> output;
        for (auto weapon : allWeapons)
            if(weapon.type==weaponType)
                output.add(weapon);
        return output;
    };
    
    inline const Array<Weapon> simpleList = getWeaponList(SIMPLE);
    inline const Array<Weapon> martialLightList = getWeaponList(MARTIAL_LIGHT_MELEE);
    inline const Array<Weapon> martialOneHandedMeleeList = getWeaponList(MARTIAL_ONE_HANDED_MELEE);
    inline const Array<Weapon> martialTwoHandedMeleeList = getWeaponList(MARTIAL_TWO_HANDED_MELEE);
    inline const Array<Weapon> martialRanged = getWeaponList(MARTIAL_RANGED);
    inline const Array<Weapon> exoticList = getWeaponList(EXOTIC);
    inline const Array<Weapon> martialAllList = []{
        Array<Weapon> output;
        output.addArray(martialLightList);
        output.addArray(martialOneHandedMeleeList);
        output.addArray(martialTwoHandedMeleeList);
        output.addArray(martialRanged);
        return output;
    }();
    
    inline Weapon getRandomExoticWeapon = []()->Weapon{
        Random random;
        return exoticList[random.nextInt(exoticList.size())];
    }();
    
    
    inline const std::map<Critical, String> critToString{
        {x2, "x2"},
        {x3, "x3"},
        {x4, "x4"},
        {_18_20x2, "(18-20)x2"},
        {_19_20x2, "(19-20)x2"}
    };
    
    
}

namespace Armors {
    enum ArmorType{
        NONE,
        LIGHT,
        MEDIUM,
        HEAVY,
        SHIELD
    };
    
    struct Armor{
        String name;
        int ac;
        std::optional<int> maxDex;
        int armorCheckPenalty;
        ArmorType armorType;
        NumOfHands numOfHands;
        

    };
    
    
    static inline Armor padded{         "padded",           1,8,0, LIGHT, ZERO},
                        leather{        "leather",          2,6,0, LIGHT, ZERO},
                        studdedLeather{ "studded leather",  3,5,-1,LIGHT, ZERO},
                        chainShirt{     "chain shirt",      4,4,-2,LIGHT, ZERO},
    
    
    
                        buckler{        "buckler",          1,NA,-1,LIGHT, ONE},
                        shieldLW{   "shield (light wooden)", 1,NA,-1,LIGHT, ONE},
                        shieldLS{   "shield (light steel)",  1,NA,-1,LIGHT, ONE},
                        shieldHW{   "shield (heavy wooden)", 2,NA,-2,LIGHT, ONE},
                        shieldHS{   "shield (heavy steel)",  2,NA,-2,LIGHT, ONE},
                        shieldTower{    "tower shield",     4,2,-10,LIGHT, TWO},
    
                        none{           "(none)",           0,NA,0, NONE, ZERO};
    
}

