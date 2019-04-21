/*
  ==============================================================================

    Feats.h
    Created: 19 Apr 2019 10:53:49pm
    Author:  Adam Shield

  ==============================================================================
*/
#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "Skills.h"
#include "Character.h"

namespace Feats {
    auto nullFunc = [](Array<Skill>& skillList){};
    
    template<Weapons::WeaponType weaponType>
    auto weaponProfFunc = [](Character& character){
        for(auto& weapon : Weapons::martial)
            if(weapon.type == weaponType)
                character.weaponProficiencies.add(weapon);
    };
    
    //================FEATS==================//
    static const inline Feat    acrobatic{"acrobatic",[](Character& character){
                                    character.getSkill("jump").miscMod += 2;
                                    character.getSkill("tumble").miscMod += 2;
                                }},

                                agile{"agile",[](Character& character){
                                    character.getSkill("balance").miscMod += 2;
                                    character.getSkill("escape artist").miscMod += 2;
                                }},

                                alertness{"alertness", [](Character& character){
                                    for(auto& skill : character.skills)
                                        if(skill.name == "spot" || skill.name == "listen")
                                            skill.miscMod+=2;
                                }},
    
                                animalAffinity{"animal affinity",[](Character& character){
                                    character.getSkill("handle animal").miscMod += 2;
                                    character.getSkill("ride").miscMod += 2;
                                }},
    
                                improvedInitiative{"improved initiative", [](Character& character){
                                    character.initMiscMod += 4;
                                }},
    
                                martialProf_lightMelee    ("martialProf_lightMelee",
                                                           weaponProfFunc<Weapons::MARTIAL_LIGHT_MELEE>),
    
                                martialProf_oneHandedMelee("martialProf_oneHandedMelee",
                                                           weaponProfFunc<Weapons::MARTIAL_ONE_HANDED_MELEE>),
    
                                martialProf_twoHandedMelee("martialProf_twoHandedMelee",
                                                           weaponProfFunc<Weapons::MARTIAL_TWO_HANDED_MELEE>),
    
                                martialProf_ranged        ("martialProf_ranged",
                                                           weaponProfFunc<Weapons::MARTIAL_RANGED>);
    
    
    
    
    
}
