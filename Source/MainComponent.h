/*
  ==============================================================================

    

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Character.h"
#include "Monsters.h"
#include "Common.h"


class CharacterSheet : public Component{
public:
    void paint (Graphics&) override;
    void resized() override;
    const std::shared_ptr<Character> character;
    
    CharacterSheet(const std::shared_ptr<Character> input) : character(input){
        characterImage = character->getImage();
    }
    
    CharacterSheet(const CharacterSheet &input) = default;
    CharacterSheet() = default;
    
private:
    Array<String> fillCharacterSheet(const std::shared_ptr<Character> input);
    Image characterImage;
    String getWeaponDetails(std::shared_ptr<Character> character);
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


class CharacterSheetWindow : public Component{
public:
    void paint (Graphics&) override;
    void resized() override;
    void processCharacterSheets();
    
    CharacterSheetWindow();
    
    Array<std::shared_ptr<CharacterSheet>> characterSheets;
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
    

private:
    HeaderControls headerControls;
    CharacterSheetWindow characterSheetWindow;
    void buttonClicked (Button* button) override;
    Viewport viewport;
    Array<std::shared_ptr<NPC>> monsters;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
