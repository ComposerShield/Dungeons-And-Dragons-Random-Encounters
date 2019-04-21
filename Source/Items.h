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
        MARTIAL,
        EXOTIC
    };
    
    struct Weapon{
        String name;
        Die melee;
        Die ranged;
        Critical crit;
        weaponType type;
    };
    
    
    namespace Simple{
        static inline Weapon    gauntlet        {"gauntlet",        D3, none, x2,       SIMPLE},
                                unarmed         {"unarmed strike",  D3, none, x2,       SIMPLE},
                                dagger          {"dagger",          D4, none, _19_20x2, SIMPLE},
                                daggerPunching  {"punching dagger", D4, none, x3,       SIMPLE},
                                gauntletSpiked  {"spiked dagger",   D4, none, x3,       SIMPLE},
                                maceLight       {"light mace",      D6, none, x2,       SIMPLE},
                                sickle          {"sickle",          D6, none, x2,       SIMPLE},
                                club            {"club",            D6, none, x2,       SIMPLE},
                                maceHeavy       {"heavy mace",      D8, none, x2,       SIMPLE},
                                morningstar     {"morningstar",     D6, none, x2,       SIMPLE},
                                shortSpear      {"shortspear",      D6, none, x2,       SIMPLE},
                                longSpear       {"longspear",       D8, none, x3,       SIMPLE},
                                quarterstaff    {"quarterstaff",    D6, D6, x2,         SIMPLE},
                                spear           {"spear",           D8, none, x3,       SIMPLE},
        
        javelin     {"javelin",     D6, none, x2,       SIMPLE}

        
        ;
    }
    
    namespace Martial{
        
    }
}

namespace Armors {
    struct Armor{
        String name;
        int ac;
    };
}
