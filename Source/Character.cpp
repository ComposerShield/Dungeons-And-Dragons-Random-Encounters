/*
  ==============================================================================

    Character.cpp
    Created: 19 Apr 2019 10:32:10pm
    Author:  Adam Shield

  ==============================================================================
*/

#include "Character.h"
#include "Feats.h"

Character::Character(Array<uint8> abilities, uint8 baseAttack, int init){
    strength =      abilities[0];
    dexterity =     abilities[1];
    constitution =  abilities[2];
    intelligence =  abilities[3];
    wisdom =        abilities[4];
    charisma =      abilities[5];
    
    baseAttackBonus = baseAttack;
    baseInitiative = init;
    
    populateSkillMap();
    featList.reset(new Array<Feat>(Feats::featList));
}

void Character::evaluateCharacterSheet(){
    abilityList = {&strength, &dexterity, &constitution, &intelligence, &wisdom, &charisma};

    for(auto val : {&miscHP, &miscWill, &miscRef, &miscFort})
        resetVal(val);
    for(auto val : {&initMiscMod, &meleeMiscBonus, &rangedMiscBonus})
        resetVal(val);
    
    randomize();
    for(auto& feat : *feats) feat.function;
    for(auto& skill : skills){
        skill.calculateKeyAbilityMod(skill.abilityFromArray(abilitiesAsArray()));
    }
    
    
    ac = getAC();
    initiative = getInitiative();
    
    fort = getFortitude();
    ref = getReflex();
    will = getWill();
    
    activateFeats();
}

Skill& Character::getSkill(String skillName) const{
    for(auto& skill : skills)
        if(skill.name==skillName)
            return skill;
    return Skills::jump;
}

void Character::populateSkillMods(Array<std::pair<Skill, int>> skillList) const{
    for(auto& [skillToEdit, val] : skillList){
        Skill& skill = getSkill(skillToEdit.name);
        skill.ranks = val;
    }
}

void Character::activateFeats(){
    for(auto feat : *feats)
        feat.function(this);
}

void Character::randomize(){
    //ABILITIES
    for(auto* ability : abilityList)
        *ability += random.nextInt((*ability)/6 + 1) * ( random.nextBool() ? 1 : -1 );
    //HP
    hp = rollHD();

}

constexpr int Character::rollHD() const{
    const auto [numOfRolls, hitDie] = HD;
    auto total=miscHP;
    for (auto i=0;i<numOfRolls;i++)
        total+= random.nextInt(dieToNum(hitDie))+1 + abilityMod(constitution);
    return total;
}

bool Character::checkPrerequisites(Prerequisite& prerequisite){
    return std::visit([this](auto& prerequisite)->bool{
        using T = std::decay_t<decltype(prerequisite)>;
        
        if constexpr (std::is_same_v<T, Feat>){
            for(auto& feat : *feats)
                if(feat.name==prerequisite.name)
                    return true;
        }
        else if constexpr (std::is_same_v<T, AbilityVal>){
            auto [ability, min] = prerequisite;
            if(min<=abilityFromArray(ability))
                return true;
        }
        else return false;
        
        return false;
    }, prerequisite);
}

//========================NPC=============================//

void NPC::finalizeNPC(){
    equippedWeapons.add(getRandomFromPref(preferredWeapons));
    equippedArmor.add(getRandomFromPref(preferredArmor));
    for(auto i=0; i<startingFeatRanks;++i)
        feats->add(getRandomFromPref(preferredFeats));
    populateSkillRanks();
    
}

template<typename t>
t NPC::getRandomFromPref(const Preferred<t>& pref) const{
    
    return grabFromPrefList(  (random.nextBool()) ?     pref.highChance //50 percent
                            : (random.nextInt(50)<35) ? pref.mediumChance //35 percent
                                                      : pref.lowChance ); //15 percent
}

template<typename t>
t NPC::grabFromPrefList(Array<t> list) const{
    if(list.size()==0){
        if constexpr (std::is_same_v<t, Skill>)
            return randomSkill();
        else if constexpr (std::is_same_v<t, Weapons::Weapon>)
            return grabFromPrefList(defaultWeapons);
        else if constexpr (std::is_same_v<t, Feat>)
            return grabFromPrefList(*featList);
        else{
            jassertfalse;
            return t();
        }
    }
    
    else return list[random.nextInt(list.size())];
    
};



void NPC::populateSkillRanks(){
    setSkillRankCap();
    
    for(int i = startingSkillRanks; i>0 ; --i){
        Skill  skill;
        
        //Prevent from going over skillcap.
        do{
            skill = getRandomFromPref(preferredSkills);
        }while(skill.ranks >= skillRankCap);
            
        Skill* skillPtr = skillMap[skill.name];
        skillPtr->incrementRank();
    }
}
