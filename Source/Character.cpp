/*
  ==============================================================================

    Character.cpp
    Created: 19 Apr 2019 10:32:10pm
    Author:  Adam Shield

  ==============================================================================
*/

#include "Character.h"

Character::Character(Array<int> abilities, int baseAttack, int init, int HP){
    strength =      abilities[0];
    dexterity =     abilities[1];
    constitution =  abilities[2];
    intelligence =  abilities[3];
    wisdom =        abilities[4];
    charisma =      abilities[5];
    
    baseAttackBonus = baseAttack;
    baseInitiative = init;
    hp = HP;
    
}

void Character::evaluateCharacterSheet(){
    abilityList = {&strength, &dexterity, &constitution, &intelligence, &wisdom, &charisma};
    Array<int*> resetList{&miscHP, &miscWill, &miscRef, &miscFort, &initMiscMod, &meleeMiscBonus, &rangedMiscBonus};
    for(auto * val : resetList) *val=0;
    
    
    randomize();
    for(auto& feat : feats) feat.function;
    for(auto& skill : skills){
        skill.calculateKeyAbilityMod(skill.abilityFromArray(abilitiesAsArray()));
        //String abilityName = skill.abilityFromArray(abilitiesAsArray());
        //skill.keyAbilityMod = skill.calculateKeyAbilityMod(<#int abilityVal#>)
    }
    
    
    hp = getHP();
    ac = getAC();
    initiative = getInitiative();
    
    fort = getFortitude();
    ref = getReflex();
    will = getWill();
    
}

Skill& Character::getSkill(String skillName){
    for(auto& skill : skills)
        if(skill.name==skillName)
            return skill;
    return Skills::jump;
}

void Character::populateSkills(Array<std::pair<Skill, int>> skillList){
    for(auto [skillToEdit, val] : skillList){
        Skill& skill = getSkill(skillToEdit.name);
        skill.ranks = val;
    }
}

void Character::randomize(){
    //ABILITIES
    for(auto* ability : abilityList)
        *ability += random.nextInt((*ability)/5 + 1);
    //HP
    hp = rollHD();
}

int Character::rollHD() const{
    auto [hitDie, numOfRolls] = HD;
    auto total=0;
    for (auto i=0;i<numOfRolls;i++)
        total+= random.nextInt(dieToNum(hitDie)) + abilityMod(constitution);
    return total;
}

//========================NPC==============================

void NPC::finalizeNPC(){
    equippedWeapons.add(randomWeapon());
}

Weapons::Weapon NPC::randomWeapon(){
    return commonWeapons[random.nextInt(commonWeapons.size())];
}
