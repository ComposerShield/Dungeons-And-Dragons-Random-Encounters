/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Character.h"
#include "Monsters.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class CharacterSheet : public Component{
public:
    void paint (Graphics&) override;
    void resized() override;
    
private:

};

class MainComponent   : public Component
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    Array<CharacterSheet> characterSheets;

private:
    //==============================================================================
    Image logo;
    CharacterSheet test;
    
    //Monsters::Goblin jack;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};



