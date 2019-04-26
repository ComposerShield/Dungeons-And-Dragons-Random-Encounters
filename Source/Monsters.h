/*
  ==============================================================================

    Monsters.h
    Created: 20 Apr 2019 1:02:06pm
    Author:  Adam Shield

  ==============================================================================
*/

#pragma once

#include "Character.h"
#include "array"
#include "Feats.h"
#include "map"

namespace Monsters {
    //inline auto greg = std::array<int, 6>{11,13,12,10,9,6};
    //inline NPC frank({11,13,12,10,9,6});
    struct Goblin : public NPC{
        Goblin() : NPC({11,13,12,10,9,6}, 1, 1, 4){
            race = "Goblin";
            sizeMod = 1;
            cr = 0.33;
            commonWeapons = { Weapons::javelin,
                              Weapons::morningstar };
        }
    };
    
    struct Orc : public NPC{
        Orc() : NPC({11,13,12,10,9,6}, 1, 1, 4){ //TODO, copied from Goblin
            
        }
    };
    
    
    
    
    
    inline std::map<String, NPC> monsters = {
        //{"Goblin", Goblin},
        //{"Orc", Orc}
    };
}



