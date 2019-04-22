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
    
    CharacterSheet(){}
    
private:

};


class HeaderControls : public Component{
public:
    HeaderControls();
    void paint (Graphics&) override;
    void resized() override;
    ComboBox monsterType;
    ComboBox numOfMonsters;
    TextButton generateButton;
    
private:
    Image logo;
};


//==============================================================================
//============================MAIN COMPONENT====================================
//==============================================================================


class MainComponent   : public Component,
                        public Button::Listener
{
public:
    MainComponent();
    ~MainComponent();

    void paint (Graphics&) override;
    void resized() override;
    
    Array<CharacterSheet> characterSheets;
    void fillCharacterSheet();

private:
    CharacterSheet test;
    HeaderControls headerControls;
    void buttonClicked (Button* button) override;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
