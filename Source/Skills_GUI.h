/*
  ==============================================================================

    Skills_GUI.h
    Created: 2 May 2019 10:07:00am
    Author:  Adam Shield

  ==============================================================================
*/

#pragma once
#include "Character.h"

class SkillSheet : public Component
{
public:
    const Array<Skill>& skills;
    SkillSheet() = default;
    SkillSheet(const Character& character) : skills(character.skills)
    {
        
    }
    
    
    
private:
    void paint (Graphics&) override{
        
    };
    
    void resized() override{
        
    };
    
    
};
