/*
  ==============================================================================

    

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
        auto newMonsterPtr = ( [monsterType]()->NPC*{
            for(auto [name,thisMonster] : Monsters::monsters)
                if (name==monsterType) return Monsters::monsters[monsterType](); //PLACEHOLDER TODO
            jassertfalse;
            }()
        );
        std::shared_ptr<NPC> newMonster(newMonsterPtr);
        
        newMonster->evaluateCharacterSheet();
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
    
    const auto textArray = (mode==STATS) ? fillCharacterSheetStats (character)
                                         : fillCharacterSheetSkills(character);
    
    Array<String> skillNums;
    if(mode != STATS){
        for(auto skill : character->skills){
            skillNums.add(static_cast<String>(skill.total())       + "    " +
                          static_cast<String>(skill.ranks)         + "  "   +
                          static_cast<String>(skill.keyAbilityMod) + "  "   +
                          static_cast<String>(skill.miscMod));
        }
    }
    
    auto [width, height] = std::pair{bounds.getWidth(), bounds.getHeight()};
    
    g.setColour(Colours::black);
    for_indexed(auto& text : textArray){
        if(i==1 && mode!=STATS)
            g.drawLine(bounds.getX(), bounds.getY(), bounds.getWidth(), bounds.getY());
        
        //Write line of text.
        g.drawText(text, bounds.getX()+10, bounds.removeFromTop(20).getY(), width-40, getHeight()*0.1, Justification::left);
        
        //Write skill numbers.
        if (mode!=STATS){
            g.drawText(skillNums[i], bounds.getX()+110, bounds.getY(), width-40, getHeight()*0.1, Justification::left);
        }
    }
    
    auto rect = Rectangle<float>(width * 0.75f, 0.05f, width*0.25f, height * 0.25);
    g.drawImage(characterImage, rect);
}

void CharacterSheet::resized(){
    modeSwitch.setBoundsRelative(0.75f, 0.85f, 0.2f, 0.1f);
}

Array<String> CharacterSheet::fillCharacterSheetStats(const std::shared_ptr<Character> input){
    return {String("Race ")  + static_cast<String>(character->race),
            String("HP ")    + static_cast<String>(character->hp) +
            String(" AC ")   + static_cast<String>(character->ac),
            String("Str ")   + static_cast<String>(character->strength) +
            String("  Dex ") + static_cast<String>(character->dexterity) +
            String("  Con ") + static_cast<String>(character->constitution),
            String("Int ")   + static_cast<String>(character->intelligence) +
            String("  Wis ") + static_cast<String>(character->wisdom) +
            String("  Cha ") + static_cast<String>(character->charisma),
            String("Fort ")  + static_cast<String>(character->fort) +
            String(" Ref ")  + static_cast<String>(character->ref) +
            String(" Will ") + static_cast<String>(character->will),
            String("Weapon: ") + character->equippedWeapons[0].name,
            String("              ") + getWeaponDetails(character),
            String("Armor: ") + character->equippedArmor[0].name
    };
}

Array<String> CharacterSheet::fillCharacterSheetSkills(const std::shared_ptr<Character> input){
    Array<String> output = {"Skill Name      Total  r  a  m"};
    
    int start;
    switch(mode){
        case SKILLS_1: start =0; break;
        case SKILLS_2: start =9; break;
        case SKILLS_3: start =18; break;
        case SKILLS_4: start =27; break;
        case STATS: jassertfalse; break;
    }
    auto end= std::clamp(start+9, 0, character->skills.size());
    
    for(auto i=start; i<end; ++i)
        output.add(character->skills.getReference(i).name);
    
    return output;
}

String CharacterSheet::getWeaponDetails(std::shared_ptr<Character> character){
    auto weapon = character->equippedWeapons[0];
    bool isMelee = weapon.melee.dieType != none;
    
    String attack = "(+" + static_cast<String>(character->baseAttackBonus + character->sizeMod + ((isMelee) ? abilityMod(character->strength) : abilityMod(character->dexterity))) + ")";
    
    String damage = " d" + static_cast<String>(dieToNum(weapon.melee.dieType)) + "+" +
        static_cast<String>(abilityMod((isMelee) ? character->strength : character->dexterity));
    
    String crit = Weapons::critToString.at(weapon.crit);
    
    return attack + "  " + damage + "  " + crit;
}

void CharacterSheet::buttonClicked(Button* button){
    switch(mode){
        case STATS:
            mode=SKILLS_1;
            modeSwitch.setButtonText("Skills");
            break;
        case SKILLS_1:
            mode=SKILLS_2;
            modeSwitch.setButtonText("Skills 2");
            break;
        case SKILLS_2:
            mode=SKILLS_3;
            modeSwitch.setButtonText("Skills 3");
            break;
        case SKILLS_3:
            mode=SKILLS_4;
            modeSwitch.setButtonText("Skills 4");
            break;
        case SKILLS_4:
            mode=STATS;
            modeSwitch.setButtonText("Stats");
            break;
    }
    
    repaint();
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
