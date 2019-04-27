/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Character.h"
#include "Monsters.h"
#define for_indexed(...) for_indexed_v(i, __VA_ARGS__)
#define for_indexed_v(v, ...) for(bool _i_ = true, _break_ = false; _i_;) for(size_t v = 0; _i_; _i_ = false) for(__VA_ARGS__) if(_break_) break; else for(bool _j_ = true; _j_;) for(_break_ = true; _j_; _j_ = false) for(bool _k_ = true; _k_; v++, _k_ = false, _break_ = false)

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/


class CharacterSheet : public Component{
public:
    void paint (Graphics&) override;
    void resized() override;
    const std::shared_ptr<Character> character;
    
    CharacterSheet(const std::shared_ptr<Character> input) : character(input){}
    
    CharacterSheet(const CharacterSheet &input) = default;
    CharacterSheet() = default;
    
private:
    Array<String> fillCharacterSheet(const std::shared_ptr<Character> input);
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
