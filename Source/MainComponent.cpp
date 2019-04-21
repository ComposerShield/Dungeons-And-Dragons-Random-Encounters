/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    setSize (800, 600);
    
    addAndMakeVisible(&headerControls);
    
    resized();
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    auto [width, height] = std::pair<int, int>(getWidth(), getHeight());
    g.fillAll (Colours::moccasin);

    g.setFont (Font (16.0f));
}

void MainComponent::resized()
{
    headerControls.setBoundsRelative(0.0f, 0.0f, 1.0f, 0.15f);
}

void MainComponent::displayCharacterSheets(){
    for(auto& characterSheet : characterSheets)
        addAndMakeVisible(characterSheet);
}



//============================Character_Sheet==================================

void CharacterSheet::paint(Graphics &g){
    g.setColour(Colours::grey);
    g.fillRoundedRectangle(0, 0, getWidth(), getHeight(), 10);
}

void CharacterSheet::resized(){
    
}





//=============================HEADER_CONTROLS==================================

HeaderControls::HeaderControls() : generateButton("Generate"){
    logo = ImageCache::getFromMemory(BinaryData::dnd_logo_png, 472399);
    addAndMakeVisible(&monsterType);
    addAndMakeVisible(&numOfMonsters);
    addAndMakeVisible(&generateButton);
    
    for(auto monster : {"goblin", "orc", "gnoll"})
        monsterType.addItem(monster, monsterType.getNumItems()+1);
    for(auto i=1; i<20 ;++i)
        numOfMonsters.addItem(static_cast<String>(i), i);
}

void HeaderControls::paint (Graphics& g){
    auto [width, height] = std::pair<int, int>(getWidth(), getHeight());
    g.fillAll(Colours::dimgrey);
    auto logoRect = Rectangle<float>{0,0,static_cast<float>(width)/4,static_cast<float>(height)};
    g.drawImage(logo, logoRect);
}

void HeaderControls::resized(){
    monsterType.setBoundsRelative   (0.3, 0.35, 0.15, 0.3);
    numOfMonsters.setBoundsRelative (0.5, 0.35, 0.075, 0.3);
    generateButton.setBoundsRelative(0.6, 0.35, 0.15, 0.3);
}
