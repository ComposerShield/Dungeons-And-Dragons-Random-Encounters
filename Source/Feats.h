/*
  ==============================================================================

    Feats.h
    Created: 19 Apr 2019 10:53:49pm
    Author:  Adam Shield

  ==============================================================================
*/
#pragma once
#include "Skills.h"
#include "Character.h"
#include "Common.h"

namespace Feats {
    auto nullFunc = [](Array<Skill>& skillList){};
    
    template<Weapons::WeaponType weaponType>
    auto weaponProfFunc = [](Character* character){
        for(auto& weapon : Weapons::martialAllList)
            if(weapon.type == weaponType)
                character->weaponProficiencies.add(weapon);
    };
    
    template<Weapons::Weapon& exoticWeapon>
    static inline Feat exoticProf{"exoticProf ", [](Character* character){
        character->weaponProficiencies.add(exoticWeapon);
    }};
    
    //================FEATS==================//
    static const inline Feat    acrobatic{"acrobatic",[](Character* character){
                                    character->getSkill("jump").miscMod += 2;
                                    character->getSkill("tumble").miscMod += 2;
                                }},

                                agile{"agile",[](Character* character){
                                    character->getSkill("balance").miscMod += 2;
                                    character->getSkill("escape artist").miscMod += 2;
                                }},

                                alertness{"alertness", [](Character* character){
                                    for(auto& skill : character->skills)
                                        if(skill.name == "spot" || skill.name == "listen")
                                            skill.miscMod+=2;
                                }},
    
                                animalAffinity{"animal affinity",[](Character* character){
                                    character->getSkill("handle animal").miscMod += 2;
                                    character->getSkill("ride").miscMod += 2;
                                }},
    
                                athletic{"athletic",[](Character* character){
                                    character->getSkill("climb").miscMod += 2;
                                    character->getSkill("swim").miscMod += 2;
                                }},
    
                                combatExpertise{"combat expertise",[](Character* character){
                                    character->description.add("Combat expertise: may trade attack bonus for AC");
                                }},
    
                                improvedDisarm{"improved disarm",[](Character* character){
                                        character->description.add("Improved disarm: +4 on disarm checks, no attacks of opportunity");
                                }, combatExpertise},
    
                                improvedTrip{"improved trip",[](Character* character){
                                        character->description.add("Improved trip: +4 on trip attempts, no attacks of opportunity");
                                }, combatExpertise},
    
                                combatReflexes{"combat reflexes",[](Character* character){
                                    character->description.add("Combat reflexes: attacks of opportunity while flat-footed, additional attacks per Dex bonus.");
                                }},
    
                                deceitful{"deceitful",[](Character* character){
                                    character->getSkill("disguise").miscMod += 2;
                                    character->getSkill("forgery").miscMod += 2;
                                }},
    
                                dodge{"dodge",[](Character* character){
                                    character->description.add("Combat reflexes: +1 AC against one enemy every round.");
                                }, {DEX, 13}},
    
                                endurance{"endurance",[](Character* character){
                                    character->getSkill("swim").miscMod += 4;
                                    character->description.add("Combat reflexes: +4 CON checks to continue running. Generally less fatigued.");
                                }},
    
                                improvedInitiative{"improved initiative", [](Character* character){
                                    character->initMiscMod += 4;
                                }},
    
                                improvedUnarmedStrike{"improved unarmed strike",[](Character* character){
                                    character->description.add("Improved unarmed: Unarmed does not provoke attack of opportunity and can be lethal.");
                                }},
    
                                investigator{"investigator",[](Character* character){
                                    character->getSkill("gather information").miscMod += 2;
                                    character->getSkill("search").miscMod += 2;
                                }},
    
                                ironWill{"iron will",[](Character* character){
                                    character->miscWill += 2;
                                }},
    
                                greatCleave{"great cleave",[](Character* character){
                                    character->description.add("Improved trip: +4 on trip attempts, no attacks of opportunity");
                                }},
    
                                greatFortitude{"great fortitude",[](Character* character){
                                    character->miscFort += 4;
                                }},
    
                                lightningReflexes{"lightning reflexes",[](Character* character){
                                    character->miscRef += 2;
                                }},
    
                                magicApt{"magic aptitude",[](Character* character){
                                    character->getSkill("spellcraft").miscMod += 2;
                                    character->getSkill("use magic device").miscMod += 2;
                                }},
    
                                martialProf_lightMelee    ("martialProf_lightMelee",
                                                           weaponProfFunc<Weapons::MARTIAL_LIGHT_MELEE>),
    
                                martialProf_oneHandedMelee("martialProf_oneHandedMelee",
                                                           weaponProfFunc<Weapons::MARTIAL_ONE_HANDED_MELEE>),
    
                                martialProf_twoHandedMelee("martialProf_twoHandedMelee",
                                                           weaponProfFunc<Weapons::MARTIAL_TWO_HANDED_MELEE>),
    
                                martialProf_ranged        ("martialProf_ranged",
                                                           weaponProfFunc<Weapons::MARTIAL_RANGED>),
    
                                pointBlankShot{"point blank shot",[](Character* character){
                                    character->rangedMiscBonus += 1;
                                }},
    
                                    farShot{"far shot",[](Character* character){
                                        character->description.add("Far shot: Ranged weapon range increases by half, doubled for thrown.");
                                    }, pointBlankShot},
    
                                    preciseShot{"precise shot",[](Character* character){
                                        character->description.add("Precise shot: No -4 penalty against opponant engaged in melee.");
                                    }, pointBlankShot},
    
                                stealthy{"stealthy",[](Character* character){
                                    character->getSkill("hide").miscMod += 2;
                                    character->getSkill("move silently").miscMod += 2;
                                }},
    
                                toughness{"toughness",[](Character* character){
                                    character->miscHP += 3;
                                }},
    
                                track{"track",[](Character* character){
                                    character->description.add("Track: Good at tracking.");
                                }},
    
                                twoWeaponFighting{"two-weapon fighting",[](Character* character){
                                    character->description.add("Two weapon fighting.");
                                }, {DEX, 15}};
    
    
    inline const Array<Feat> featList{acrobatic, agile, alertness, animalAffinity, athletic, combatReflexes,
        improvedInitiative, exoticProf<Weapons::getRandomExoticWeapon>, greatCleave, greatFortitude,
        improvedInitiative, investigator, ironWill, martialProf_lightMelee, pointBlankShot, farShot,
        martialProf_oneHandedMelee, martialProf_twoHandedMelee, martialProf_ranged, preciseShot,
        stealthy, toughness, track, twoWeaponFighting};
    
    
}
