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
        Goblin() : NPC({11,13,12,10,9,6}, 1, 1){
            race = "goblin";
            sizeMod = 1;
            HD = {D8, 1};
            cr = 0.33;
            baseFort=2;
            baseRef=0;
            baseWill=-1;
            commonWeapons = { Weapons::javelin,
                              Weapons::morningstar,
                              Weapons::unarmed,
                              Weapons::dagger,
                              Weapons::daggerPunching,
                              Weapons::maceLight
            };
            //characterImageData.first = BinaryData::goblin_png;
            //{BinaryData::goblin_png, 319005};
            //characterImage = ImageCache::getFromMemory(BinaryData::goblin_png, 319005);
            
            finalizeNPC();
        }
        Image getImage() override {return ImageCache::getFromMemory(BinaryData::goblin_png, 319005);}
    };
    
    struct Orc : public NPC{
        Orc() : NPC({11,13,12,10,9,6}, 1, 1){ //TODO, copied from Goblin
            
        }
        Image getImage() override {return ImageCache::getFromMemory(BinaryData::goblin_png, 319005);}
    };
    
    
    
    
    
    inline std::map<String, NPC*> monsters = {
        {"goblin", new Goblin()},
        {"orc", new Orc()}
    };
}



