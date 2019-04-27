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
    addAndMakeVisible(&viewport);
    headerControls.generateButton.addListener(this);
    
    viewport.setViewedComponent(&characterSheetWindow, false);
    viewport.setScrollBarThickness(20);
    viewport.setScrollBarsShown(true, false);
    
    resized();
    
}

MainComponent::~MainComponent()
{

}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    auto [width, height] = std::pair<int, int>(getWidth(), getHeight());
    //g.fillAll (Colours::moccasin);

    g.setFont (Font (16.0f));
}

void MainComponent::resized()
{
    auto bounds = getLocalBounds();
    headerControls.setBounds(bounds.removeFromTop(80));
    viewport.setBounds(bounds);
    characterSheetWindow.setBounds(bounds.expanded(0, 400));
    viewport.setViewPositionProportionately(0.0, 0.0);
    
}

void MainComponent::buttonClicked(Button * button){
    String monsterType = headerControls.monsterType.getText();
    int numOfMonsters  = headerControls.numOfMonsters.getSelectedItemIndex() + 1;

    monsters.clearQuick();
    characterSheetWindow.characterSheets.clearQuick();
    
    for(auto i=0;i<numOfMonsters;++i){
        auto newMonster = ( [monsterType]()->std::shared_ptr<NPC>{
            for(auto [name,thisMonster] : Monsters::monsters)
                if (name==monsterType) return std::make_shared<NPC>(thisMonster);
            jassertfalse;
            }()
        );
        monsters.add(newMonster);
        
        
        
        auto newSheet = std::make_shared<CharacterSheet>(newMonster);
        characterSheetWindow.characterSheets.add(newSheet);
        
    }
    
   
    
    characterSheetWindow.processCharacterSheets();
    
    resized();
    characterSheetWindow.resized();
}


//============================Character_Sheet==================================

void CharacterSheet::paint(Graphics &g){
    auto bounds = getLocalBounds();
    bounds.removeFromTop(5);
    bounds.removeFromBottom(5);
    bounds.removeFromLeft(5);
    bounds.removeFromRight(5);

    Rectangle<float> boundsFloat = {static_cast<float>(bounds.getX()),
                                    static_cast<float>(bounds.getY()),
                                    static_cast<float>(bounds.getWidth()),
                                    static_cast<float>(bounds.getHeight())
                                    };
    
    g.setColour(Colour(221, 217, 205));
    g.fillRoundedRectangle(boundsFloat, 10);
    
    auto textArray = fillCharacterSheet(character);
    
    auto [width, height] = std::pair{bounds.getWidth()-20, bounds.getHeight()};
    
    g.setColour(Colours::black);
    for(auto& text : textArray){
        g.drawText(text, bounds.getX()+10, bounds.removeFromTop(20).getY(), width-20, getHeight()*0.1, Justification::left);
    }
    
    

}

void CharacterSheet::resized(){
    
}

Array<String> CharacterSheet::fillCharacterSheet(const std::shared_ptr<Character> input){
    return {String("Race ")  + static_cast<String>(character->race),
            String("HP ")    + static_cast<String>(character->hp) +
            String(" AC ")   + static_cast<String>(character->ac),
            String("Str ")   + static_cast<String>(character->strength) +
            String("  Dex ") + static_cast<String>(character->dexterity) +
            String("  Con ") + static_cast<String>(character->constitution),
            String("Int ")   + static_cast<String>(character->intelligence) +
            String("  Wis ") + static_cast<String>(character->wisdom) +
            String("  Cha ") + static_cast<String>(character->charisma),
            String("Fort ")  + static_cast<String>(character->fort),
            String(" Ref ")  + static_cast<String>(character->ref),
            String(" Will ") + static_cast<String>(character->will),
        
    };
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
    
    monsterType.setText("goblin");
    numOfMonsters.setText("1");
}

void HeaderControls::paint (Graphics& g){
    auto [width, height] = std::pair<int, int>(getWidth(), getHeight());
    g.fillAll(Colours::dimgrey);
    auto logoRect = Rectangle<float>{0,0,static_cast<float>((width) * 0.22),static_cast<float>(height)};
    g.drawImage(logo, logoRect);
}

void HeaderControls::resized(){
    monsterType.setBoundsRelative   (0.3, 0.35, 0.15, 0.3);
    numOfMonsters.setBoundsRelative (0.5, 0.35, 0.075, 0.3);
    generateButton.setBoundsRelative(0.6, 0.35, 0.15, 0.3);
}



//============================CharacterSheetWindow=================================

CharacterSheetWindow::CharacterSheetWindow(){
    //characterSheets.ensureStorageAllocated(16);
}


void CharacterSheetWindow::paint(Graphics &g){
    
}

void CharacterSheetWindow::resized(){
    auto bounds = getLocalBounds();
    
    FlexBox flexbox;
    Array<FlexItem> itemArray;
    
    
    for(auto& characterSheet : characterSheets)
        itemArray.add(FlexItem(240, 240, *characterSheet));
    
    flexbox.flexDirection = FlexBox::Direction::row;
    flexbox.flexWrap = FlexBox::Wrap::wrap;
    flexbox.alignContent = FlexBox::AlignContent::flexStart;
    
    flexbox.items = itemArray;
    flexbox.performLayout(bounds);
}

void CharacterSheetWindow::processCharacterSheets(){
    for(auto characterSheet : characterSheets){
        addAndMakeVisible(*characterSheet);
    }
}
