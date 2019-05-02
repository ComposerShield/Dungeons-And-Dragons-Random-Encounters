/*
  ==============================================================================

    Character.cpp
    Created: 19 Apr 2019 10:32:10pm
    Author:  Adam Shield

  ==============================================================================
*/

#include "Character.h"

Character::Character(Array<int> abilities, int baseAttack, int init){
    strength =      abilities[0];
    dexterity =     abilities[1];
    constitution =  abilities[2];
    intelligence =  abilities[3];
    wisdom =        abilities[4];
    charisma =      abilities[5];
    
    baseAttackBonus = baseAttack;
    baseInitiative = init;
    
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
    auto [numOfRolls, hitDie] = HD;
    auto total=miscHP;
    for (auto i=0;i<numOfRolls;i++)
        total+= random.nextInt(dieToNum(hitDie)) + abilityMod(constitution);
    return total;
}

//========================NPC=============================//

void NPC::finalizeNPC(){
    equippedWeapons.add(randomWeapon());
}

Weapons::Weapon NPC::randomWeapon(){
    return (random.nextBool()) ? preferredWeapons.highChance[random.nextInt(preferredWeapons.highChance.size())] //50 percent
     : (random.nextInt(50)<35) ? preferredWeapons.mediumChance[random.nextInt(preferredWeapons.mediumChance.size())] //35 percent
                               : preferredWeapons.lowChance[random.nextInt(preferredWeapons.lowChance.size())]; //15 percent
}

Armors::Armor NPC::randomArmor(){
    return (random.nextBool()) ? preferredArmor.highChance[random.nextInt(preferredArmor.highChance.size())] //50 percent
     : (random.nextInt(50)<35) ? preferredArmor.mediumChance[random.nextInt(preferredArmor.mediumChance.size())] //35 percent
                               : preferredArmor.lowChance[random.nextInt(preferredArmor.lowChance.size())]; //15 percent
}
