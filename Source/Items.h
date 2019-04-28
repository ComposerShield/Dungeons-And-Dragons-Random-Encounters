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

enum Critical{
    x2,
    x3,
    x4,
    _18_20x2,
    _19_20x2
};

static inline std::function<void()> nullFunc = []()->void{};

namespace Weapons {
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
        EXOTIC
    };
    
    enum NumOfHands{
        ONE,
        TWO
    };
    
    struct Weapon{
        String name;
        Die melee;
        Die ranged;
        Critical crit;
        WeaponType type;
        NumOfHands numOfHands;
    };
    
    
    static inline Weapon    gauntlet        {"gauntlet",        D3, none, x2,       SIMPLE, ONE},
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
    
    javelin     {"javelin",     D6, none, x2,       SIMPLE, ONE},
    
    
    
    //Exotic STATS TODO
    kama     {"javelin",     D6, none, x2,       EXOTIC, ONE},
    nunchaku     {"javelin",     D6, none, x2,       EXOTIC, ONE},
    sai     {"javelin",     D6, none, x2,       EXOTIC, ONE},
    siangham     {"javelin",     D6, none, x2,       EXOTIC, ONE},
    swordBastard     {"javelin",     D6, none, x2,       EXOTIC, ONE},
    waraxeDrawven     {"javelin",     D6, none, x2,       EXOTIC, ONE},
    whip     {"javelin",     D6, none, x2,       EXOTIC, ONE},
    axeOrcDouble     {"javelin",     D6, none, x2,       EXOTIC, TWO},
    chainSpiked     {"javelin",     D6, none, x2,       EXOTIC, TWO},
    flailDire     {"javelin",     D6, none, x2,       EXOTIC, TWO},
    hammerGnomeHooked     {"javelin",     D6, none, x2,       EXOTIC, TWO},
    swordTwoBladed     {"javelin",     D6, none, x2,       EXOTIC, TWO},
    urgoshDwarven     {"javelin",     D6, none, x2,       EXOTIC, TWO},
    bolash     {"javelin",     D6, none, x2,       EXOTIC, TWO},
    crossbowHand     {"javelin",     D6, none, x2,       EXOTIC, TWO},
    crossbowHeavyRepeating     {"javelin",     D6, none, x2,       EXOTIC, TWO},
    crossbowLightRepeating     {"javelin",     D6, none, x2,       EXOTIC, TWO},
    net     {"javelin",     D6, none, x2,       EXOTIC, TWO},
    shuriken     {"javelin",     D6, none, x2,       EXOTIC, ONE}
    ;

    inline const Array<Weapon> allWeapons{gauntlet, unarmed, dagger, daggerPunching, gauntletSpiked,
        maceLight, sickle, club, maceHeavy, morningstar, shortspear, longspear, quarterstaff, spear,
        
        kama, nunchaku, sai, siangham, swordBastard, waraxeDrawven, whip, axeOrcDouble, chainSpiked, flailDire,
        hammerGnomeHooked, swordTwoBladed, urgoshDwarven, bolash, crossbowHand, crossbowHeavyRepeating,
        crossbowLightRepeating, net, shuriken
    };
    
    inline Array<Weapon> getWeaponList(WeaponType weaponType){
        Array<Weapon> output;
        for (auto weapon : allWeapons)
            if(weapon.type==weaponType)
                output.add(weapon);
        return output;
    };
    
    inline const Array<Weapon> simple{gauntlet, unarmed, dagger, daggerPunching, gauntletSpiked,
        maceLight, sickle, club, maceHeavy, morningstar, shortspear, longspear, quarterstaff, spear
    };
    
    inline const Array<Weapon> martial = getWeaponList(EXOTIC);//TODO!
    
    inline const Array<Weapon> exotic = getWeaponList(EXOTIC);
    
    inline Weapon getRandomExoticWeapon = []()->Weapon{
        Random random;
        return exotic[random.nextInt(exotic.size())];
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
    struct Armor{
        String name;
        int ac;
    };
}
