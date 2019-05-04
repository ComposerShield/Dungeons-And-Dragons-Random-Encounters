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
#include <functional>

namespace Monsters {

    struct Goblin : public NPC{
        Goblin() : NPC({11,13,12,10,9,6}, 1, 1){
            race = "goblin";
            sizeMod = 1;
            HD = {1, D8};
            cr = 0.33;
            baseFort=2;
            baseRef=0;
            baseWill=-1;
            
            weaponProficiencies.addArray(Weapons::simpleList);
            
            preferredWeapons.fill(
                {Weapons::javelin, Weapons::morningstar, Weapons::shortspear, Weapons::dagger},
                {Weapons::unarmed, Weapons::daggerPunching, Weapons::maceLight, Weapons::shortsword, Weapons::axeThrowing},
                {Weapons::club, Weapons::sickle, Weapons::crossbowHand, Weapons::chainSpiked, Weapons::whip, Weapons::rapier}
                                  );
            
            preferredArmor.fill(
                {Armors::none, Armors::leather, Armors::shieldLW},
                {Armors::padded, Armors::shieldLS},
                {Armors::buckler, Armors::chainShirt}
            );
            
            preferredSkills.fill({Skills::hide, Skills::listen, Skills::move_silently, Skills::ride, Skills::spot},
                                 {},
                                 {});

            finalizeNPC();
        }
        Image getImage() override {return ImageCache::getFromMemory(BinaryData::goblin_png, 319005);}
    };
    
    struct Orc : public NPC{
        Orc() : NPC({17,11,12,8,7,6}, 1, 0){ //TODO, copied from Goblin
            race = "orc";
            sizeMod = 0;
            HD = {1, D8};
            cr = 0.5;
            baseFort=2;
            baseRef=0;
            baseWill=-1;
            
            weaponProficiencies.addArray(Weapons::simpleList);
            weaponProficiencies.add(Weapons::falchion);
            
            preferredWeapons.fill(//TODO
                           {Weapons::javelin, Weapons::falchion},
                           {Weapons::maceHeavy, Weapons::maceLight, Weapons::shortsword, Weapons::longsword},
                           {Weapons::dagger, Weapons::spear, Weapons::crossbowHand, Weapons::chainSpiked}
                                  );
            
            preferredArmor.fill(
                                {Armors::studdedLeather, Armors::leather},
                                {Armors::none, Armors::padded},
                                {Armors::buckler}
                                );
            
            preferredSkills.fill({Skills::listen, Skills::spot},
                                 {Skills::climb, Skills::survival, Skills::swim, Skills::intimidate, Skills::handle_animal},
                                 {}
                                 );
            
            finalizeNPC();
        }
        Image getImage() override {return ImageCache::getFromMemory(BinaryData::orc_png, 319005);}
    };
    
    
    
    inline std::map<String, std::function<NPC*()>> monsters = {
        {"goblin", []{return new Goblin;}},
        {"orc", []{return new Orc;}}
    };
    

}



