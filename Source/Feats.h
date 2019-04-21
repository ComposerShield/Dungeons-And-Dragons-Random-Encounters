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
    
    static const inline Feat alertness{"alertness", [](Character& character){
        for(auto& skill : character.skills)
            if(skill.name == "spot" || skill.name == "listen")
                skill.miscMod+=2;
    }};
    
    static const inline Feat improvedInitiative{"improved initiative", [](Character& character){
        character.initMiscMod += 4;
    }};
    
    static const inline Feat martialWeaponProf{"exotic weapon prof", [](Character& character){
        
    }};
}
