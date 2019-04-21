/*
  ==============================================================================

    Items.h
    Created: 20 Apr 2019 7:26:34am
    Author:  Adam Shield

  ==============================================================================
*/

#pragma once

enum Die{
    D2,
    D3,
    D4,
    D6,
    D8,
    D10,
    D20,
    none
};

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
    
    enum weaponType{
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
        weaponType type;
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
                            quarterstaff    {"quarterstaff",    D6, D6, x2,         SIMPLE, ONE},
                            spear           {"spear",           D8, none, x3,       SIMPLE, ONE},
    
    javelin     {"javelin",     D6, none, x2,       SIMPLE, ONE}

    
    ;

    
    inline const Array<Weapon> simple{gauntlet, unarmed, dagger, daggerPunching, gauntletSpiked,
        maceLight, sickle, club, maceHeavy, morningstar, shortspear, longspear, quarterstaff, spear
    };
    
    inline const Array<Weapon> martial{
        
    };
    
    inline const Array<Weapon> exotic{
        
    };
    
    
    
    
}

namespace Armors {
    struct Armor{
        String name;
        int ac;
    };
}
