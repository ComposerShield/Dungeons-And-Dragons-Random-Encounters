/*
  ==============================================================================

    

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    setSize (800, 600);
    LookAndFeel::getDefaultLookAndFeel().setDefaultSansSerifTypefaceName("Avenir Next");
    
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
    
    const auto textArray = (mode==STATS) ? fillCharacterSheetStats ()
                                         : fillCharacterSheetSkills();
    
    Array<String> skillNums;
    if(mode != STATS){
        for(auto skill : character->skills){
            skillNums.add((checkForNegative(skill.total()))       + "    " +
                          (checkForNegative(skill.ranks))         + "  "   +
                          (checkForNegative(skill.keyAbilityMod)) + "  "   +
                          (checkForNegative(skill.miscMod)));
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
        
        if (mode!=STATS && (i<skillStart()+9)){
            g.drawText(skillNums[static_cast<int>(i) + skillStart()], bounds.getX()+105, bounds.getY(), width-40, getHeight()*0.1, Justification::left);
            
        }
        
    }
    
    auto rect = Rectangle<float>(width * 0.75f, 0.05f, width*0.25f, height * 0.25);
    g.drawImage(characterImage, rect);
}

void CharacterSheet::resized(){
    modeSwitch.setBoundsRelative(0.75f, 0.85f, 0.2f, 0.1f);
}

Array<String> CharacterSheet::fillCharacterSheetStats() const{
    String description = getDescription();
    String newLineDescription;
    if(description.contains(" ")){
        newLineDescription = description.fromFirstOccurrenceOf(" ", false, false);
        description = description.replace(newLineDescription, "");
    }
    
    Array<String> stats{String("Race ")  + static_cast<String>(character->race),
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
                        String("              ") + getWeaponDetails(),
                        String("Armor: ") + character->equippedArmor[0].name,
                        String("Feats: ") + getFeatNames(),
                        String("Description: ") + description,
                        newLineDescription
    };
    

    return stats;
}

Array<String> CharacterSheet::fillCharacterSheetSkills() const{
    Array<String> output = {"Skill Name               Total   r   a   m"};
    
    const int start = skillStart();
    const auto end= std::clamp(start+9, 0, character->skills.size());
    
    for(auto i=start; i<end; ++i)
        output.add(character->skills.getReference(i).name);
    
    return output;
}

String CharacterSheet::getWeaponDetails() const{
    auto weapon = character->equippedWeapons[0];
    bool isMelee = weapon.melee.dieType != none;
    
    String attack = "(+" + static_cast<String>(character->baseAttackBonus + character->sizeMod + ((isMelee) ? abilityMod(character->strength) : abilityMod(character->dexterity))) + ")";
    
    String damage = " d" + static_cast<String>(dieToNum(weapon.melee.dieType)) + "+" +
        static_cast<String>(abilityMod((isMelee) ? character->strength : character->dexterity));
    
    String crit = Weapons::critToString.at(weapon.crit);
    
    return attack + "  " + damage + "  " + crit;
}

String CharacterSheet::getFeatNames() const{
    String output = "";
    for_indexed(auto& feat : character->feats){
        output += feat.name;
        if(i != character->feats.size()-1) output += ", ";
    }
    return output;
}

String CharacterSheet::getDescription() const{
    String output;
    for_indexed(auto& d : character->description)
        output += (i!=character->description.size()-1) ? (d + " ") : d;
    return output;
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

String CharacterSheet::checkForNegative(const int input) const{
    return (input<0) ? static_cast<String>(input) : " " + static_cast<String>(input);
}


//=============================HEADER_CONTROLS==================================

HeaderControls::HeaderControls() : generateButton("Generate"){
    logo = ImageCache::getFromMemory(BinaryData::dnd_logo_png, 472399);
    addAndMakeVisible(&monsterType);
    addAndMakeVisible(&numOfMonsters);
    addAndMakeVisible(&generateButton);
    
    for(const auto& [monster, monsterPtr] : Monsters::monsters)
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
