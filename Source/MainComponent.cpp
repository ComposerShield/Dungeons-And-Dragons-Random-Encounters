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

    logo = ImageCache::getFromMemory(BinaryData::dnd_logo_png, 472399);
    
    addAndMakeVisible(&test);
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    auto [width, height] = std::pair<int, int>(getWidth(), getHeight());
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setFont (Font (16.0f));
    g.setColour (Colours::white);
    //g.drawImageAt(logo, 0, 0);
    auto logoRect = Rectangle<float>{0,0,static_cast<float>(width)/4,static_cast<float>(height)/4};
    g.drawImage(logo, logoRect);
    //g.drawText ("Hello World!", getLocalBounds(), Justification::centred, true);
}

void MainComponent::resized()
{
    test.setBounds(0, getHeight()/2, getWidth()/2, getHeight()/4);
}






//==============================================================================

void CharacterSheet::paint(Graphics &g){
    g.setColour(Colours::grey);
    g.fillRoundedRectangle(0, 0, getWidth(), getHeight(), 10);
}

void CharacterSheet::resized(){
    
}

