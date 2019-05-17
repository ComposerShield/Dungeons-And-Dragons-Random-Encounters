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
            startingSkillRanks = 15;
            startingFeatRanks = 1;
            description.add("darkvision");
            
            using namespace Weapons;
            weaponProficiencies.addArray(simpleList);
            
            preferredWeapons.fill(
                {javelin, morningstar, shortspear, dagger},
                {unarmed, daggerPunching, maceLight, shortsword, axeThrowing},
                {club, sickle, crossbowHand, chainSpiked, whip, rapier}
                                  );
            
            using namespace Armors;
            preferredArmor.fill(
                {Armors::none, leather, shieldLW},
                {padded, shieldLS},
                {buckler, chainShirt}
            );
            
            using namespace Skills;
            preferredSkills.fill({hide, listen, move_silently, ride, spot},
                                 {hide, listen, move_silently, ride, spot},
                                 {});
            
            using namespace Feats;
            preferredFeats.fill({alertness},
                                {alertness, agile, athletic, combatReflexes},
                                {});

            finalizeNPC();
        }
        Image getImage() override {return ImageCache::getFromMemory(BinaryData::goblin_png, BinaryData::goblin_pngSize);}
    };
    
    struct Orc : public NPC{
        Orc() : NPC({17,11,12,8,7,6}, 1, 0){
            race = "orc";
            sizeMod = 0;
            HD = {1, D8};
            cr = 0.5;
            baseFort=2;
            baseRef=0;
            baseWill=-1;
            startingSkillRanks = 2;
            startingFeatRanks = 1;
            description.add("light_sensitivity");
            
            using namespace Weapons;
            weaponProficiencies.addArray(simpleList);
            weaponProficiencies.add(falchion);
            
            preferredWeapons.fill(
                           {javelin, falchion},
                           {maceHeavy, maceLight, shortsword, longsword},
                           {dagger, spear, crossbowHand, chainSpiked}
                                  );
            
            using namespace Armors;
            preferredArmor.fill(
                                {studdedLeather, leather},
                                {Armors::none, padded},
                                {buckler}
                                );
            
            using namespace Skills;
            preferredSkills.fill({listen, spot},
                                 {},
                                 {}
                                 );
            
            using namespace Feats;
            preferredFeats.fill({alertness, martialProf_oneHandedMelee, martialProf_lightMelee},
                                {improvedUnarmedStrike, combatExpertise, combatReflexes},
                                {martialProf_ranged, athletic, improvedInitiative});
            
            finalizeNPC();
        }
        Image getImage() override {return ImageCache::getFromMemory(BinaryData::orc_png, BinaryData::orc_pngSize);}
    };
    
    struct Gnoll : public NPC{
        Gnoll() : NPC({15,10,13,8,11,8}, 1, 0){
            race = "gnoll";
            sizeMod = 0;
            HD = {2, D8};
            cr = 1;
            baseFort=3;
            baseRef=0;
            baseWill=1;
            startingSkillRanks = 5;
            startingFeatRanks = 1;
            miscAC += 1;//natual armor
            description.add("darkvision");
            
            using namespace Weapons;
            weaponProficiencies.addArray(simpleList);
            weaponProficiencies.add(falchion);
            
            preferredWeapons.fill(
                                  {battleaxe, shortbow},
                                  {handaxe, maceLight, shortsword, longsword},
                                  {dagger, spear, longbow, flailHeavy}
                                  );
            
            using namespace Armors;
            preferredArmor.fill(
                                {shieldHS, leather},
                                {Armors::none, padded, shieldLS},
                                {buckler}
                                );
            
            using namespace Skills;
            preferredSkills.fill({listen, spot},
                                 {climb, survival, swim, move_silently, spot},
                                 {}
                                 );
            
            using namespace Feats;
            preferredFeats.fill({alertness},
                                {improvedUnarmedStrike, combatExpertise, athletic, combatReflexes},
                                {});
            
            finalizeNPC();
        }
        Image getImage() override {return ImageCache::getFromMemory(BinaryData::gnoll_png, BinaryData::gnoll_pngSize);}
    };
    
    
    
    struct Centaur : public NPC{
        inline static Weapons::Weapon twoHooves = Weapons::Weapon("2 hooves", D6, none, x2, Weapons::NATURAL, ZERO);
        
        Centaur() : NPC({11,13,12,10,9,6}, 4, 2){
            race = "centaur";
            sizeMod = -1;
            HD = {4, D8};
            cr = 3;
            baseFort=1;
            baseRef=4;
            baseWill=6;
            startingSkillRanks = 5;
            startingFeatRanks = 2;
            description.add("darkvision");
            
            using namespace Weapons;

            weaponProficiencies.addArray(simpleList);
            weaponProficiencies.addArray(martialAllList);
            
            preferredWeapons.fill(
                                  {longsword, longbow},
                                  {unarmed, maceHeavy, shortsword},
                                  {club, longspear, shortbow, swordTwoBladed}
                                  );
            naturalWeapons.add(Weapon(twoHooves));
            
            using namespace Armors;
            preferredArmor.fill(
                                {Armors::none},
                                {padded, leather},
                                {Armors::none}
                                );
            
            using namespace Skills;
            preferredSkills.fill({hide, listen, move_silently, ride, spot},
                                 {hide, listen, move_silently, ride, spot},
                                 {});
            
            using namespace Feats;
            preferredFeats.fill({dodge, weaponFocus(twoHooves)},
                                {track, animalAffinity, athletic, combatReflexes},
                                {});
            
            finalizeNPC();
        }
        Image getImage() override {return ImageCache::getFromMemory(BinaryData::centaur_png, BinaryData::centaur_pngSize);}
    };
    
    
    
    inline std::map<String, std::function<NPC*()>> monsters = {
        {"goblin",  []{return new Goblin;}},
        {"orc",     []{return new Orc;}},
        {"gnoll",   []{return new Gnoll;}},
        {"centaur", []{return new Centaur;}}
    };
    

}



