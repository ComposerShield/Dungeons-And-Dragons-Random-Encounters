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


class HeaderControls : public Component{
public:
    HeaderControls();
    void paint (Graphics&) override;
    void resized() override;
    
private:
    Image logo;
    ComboBox monsterType;
    ComboBox numOfMonsters;
    TextButton generateButton;
};


//==============================================================================
//============================MAIN COMPONENT====================================
//==============================================================================


class MainComponent   : public Component
{
public:
    MainComponent();
    ~MainComponent();

    void paint (Graphics&) override;
    void resized() override;
    
    Array<CharacterSheet> characterSheets;
    void displayCharacterSheets();

private:
    CharacterSheet test;
    HeaderControls headerControls;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
