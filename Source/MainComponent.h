/*
  ==============================================================================

    

  ==============================================================================
*/

#pragma once

#include "Character.h"
#include "Monsters.h"
#include "Common.h"



class CharacterSheet : public Component,
                       public Button::Listener
{
public:
    enum DisplayMode{STATS, SKILLS_1, SKILLS_2, SKILLS_3, SKILLS_4};

    const std::shared_ptr<Character> character;
    
    CharacterSheet(const std::shared_ptr<Character> input) : character(input){
        characterImage = character->getImage();
        addAndMakeVisible(modeSwitch);
        modeSwitch.addListener(this);
    }
    
    CharacterSheet(const CharacterSheet &input) = default;
    CharacterSheet() = default;
    
private:
    void paint (Graphics&) override;
    void resized() override;
    void buttonClicked (Button* button) override;
    Image characterImage;
    TextButton modeSwitch{"Skills"};
    DisplayMode mode{STATS};
    
    Array<String> fillCharacterSheetStats () const;
    Array<String> fillCharacterSheetSkills() const;
    String getWeaponDetails() const;
    String checkForNegative(const int input) const;
    String getFeatNames() const;
    constexpr int skillStart() const{
        switch(mode){
            case SKILLS_1: return 0; break;
            case SKILLS_2: return 9; break;
            case SKILLS_3: return 18; break;
            case SKILLS_4: return 27; break;
            case STATS:    return 0; break;
        }
    }
    
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




