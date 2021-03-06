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
    
    struct weaponProficiency : public Feat{
        weaponProficiency(String name, Array<Weapons::Weapon> weapons) :
            Feat("Weapon Prof: "+name,
                 [weapons](Character* character){
                    for(auto& weapon : weapons)
                        character->weaponProficiencies.add(weapon);
                 }
                 ){}
        weaponProficiency(String name, Weapons::Weapon weapon) :
            Feat("Weapon Prof: "+name,
                 [weapon](Character* character){
                         character->weaponProficiencies.add(weapon);
                 }
                 ){}
    };
    
    
    template<Weapons::Weapon& exoticWeapon>
    static inline Feat exoticProf{"exoticProf ", [](Character* character){
        character->weaponProficiencies.add(exoticWeapon);
    }};
    
    
    struct weaponFocus : public Feat{
        weaponFocus(Weapons::Weapon focus) : Feat("weapon focus: "+ focus.name, [focus](Character* character){
        character->description.add("Weapon focus: " + focus.name);
        }, {DEX, 15})
        {
        }
    };
    
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
    
    
    
    
    static const inline weaponProficiency   martialProf_lightMelee    ("martialProf_lightMelee",
                                                                       Weapons::martialLightList),
    
                                            martialProf_oneHandedMelee("martialProf_oneHandedMelee",
                                                                       Weapons::martialOneHandedMeleeList),
    
                                            martialProf_twoHandedMelee("martialProf_twoHandedMelee",
                                                                       Weapons::martialTwoHandedMeleeList),
    
                                            martialProf_ranged        ("martialProf_ranged",
                                                                       Weapons::martialRanged);
    
    
    
    inline const Array<Feat> featList{acrobatic, agile, alertness, animalAffinity, athletic, combatReflexes,
        improvedInitiative, exoticProf<Weapons::getRandomExoticWeapon>, greatCleave, greatFortitude,
        improvedInitiative, investigator, ironWill, martialProf_lightMelee, pointBlankShot, farShot,
        martialProf_oneHandedMelee, martialProf_twoHandedMelee, martialProf_ranged, preciseShot,
        stealthy, toughness, track, twoWeaponFighting};
    
    
    
    
        
    
    
}
