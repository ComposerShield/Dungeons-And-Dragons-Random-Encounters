/*
  ==============================================================================

    Character.h
    Created: 19 Apr 2019 10:32:10pm
    Author:  Adam Shield

  ==============================================================================
*/

#pragma once

#include "Skills.h"
//#include "Feats.h"
#include "Items.h"
#include "Classes.h"
#include "array"
#include "optional"
#include "variant"

struct Feat;

class Character{
public:
    int strength, dexterity, constitution, intelligence, wisdom, charisma,
        baseFort, baseRef, baseWill, miscFort, miscRef, miscWill, sizeMod,
        baseAttackBonus, initiative, initMiscMod, hp, touchAC, touchACMisc,
        currentHP, meleeMiscBonus, rangedMiscBonus, baseHP, miscHP, ac,
        baseInitiative, characterLevel, fort, ref, will;
    
    constexpr int getLevel(){
        int sum{0};
        for(auto& thisClass : classes)
            sum += thisClass.level;
        return sum;
    }
    std::optional<int> casterLevel;
    Array<int*> abilityList{&strength, &dexterity, &constitution, &intelligence, &wisdom, &charisma};
    
    Character(Array<int> abilities, int baseAttack, int init, int HP);
    
    String race;
    Array<Class> classes;
    Array<String> description;
    struct EquippedWeapons : Array<Weapons::Weapon>{};
    ;
    struct EquippedArmor   : Array<Armors::Armor>{
        constexpr int addArmor()     const {
            int output=0;
            for (auto& armor : *this) output+=armor.ac;
            return output;
        }
    };
    
    EquippedWeapons equippedWeapons;
    EquippedArmor   equippedArmor;
    Array<Skill> skills = Skills::skillList;
    Array<Feat>  feats;
    Array<Weapons::Weapon> weaponProficiencies;
    Die HD = D8; //default
    
    void evaluateCharacterSheet();
    Skill& getSkill(String skill);
    
private:
    constexpr int abilityMod(int input) const {return static_cast<int>((input-10)/2);}
    constexpr int getFortitude() const {return baseFort + abilityMod(constitution) + miscFort;}
    constexpr int getReflex()    const {return baseRef  + abilityMod(dexterity)    + miscRef ;}
    constexpr int getWill()      const {return baseWill + abilityMod(wisdom)       + miscWill;}
    constexpr int getAC()        const {return equippedArmor.addArmor() + abilityMod(dexterity) + sizeMod; }
    constexpr int getTouchAC()   const {return abilityMod(dexterity) + sizeMod;}
    constexpr int rollForInitiative()  {return initiative + random.nextInt(2) + 1;};
    void randomize();
    void populateSkills(Array<std::pair<Skill, int>> skillList);
    
    Random random;
};


class NPC : public Character{
public:
    NPC(Array<int> abilities, int baseAttack, int init, int HP) : Character(abilities, baseAttack, init, HP){}
    Array<Weapons::Weapon> commonWeapons;
    Array<Armors::Armor>  commonArmor;
    double cr;
    
};

class PC : public Character{
    PC (Array<int> abilities, int baseAttack, int init, int HP) : Character(abilities, baseAttack, init, HP){}
};


struct Feat{
    String name;
    std::function<void(Character& character)> function;
    std::optional<String> prerequisiteFeat;
    std::optional<std::pair<Ability, int>> prerequisiteAbility;
    
    Feat(String Name, std::function<void(Character& character)> Function){
        name = Name;
        function = Function;
    }
    
    Feat(String Name, std::function<void(Character& character)> Function, Feat prereqFeat){
        name = Name;
        function = Function;
        prerequisiteFeat = prereqFeat.name;
    }
    
    Feat(String Name, std::function<void(Character& character)> Function, std::pair<Ability, int> prereqAbility){
        name = Name;
        function = Function;
        prerequisiteAbility = prereqAbility;
    }
};

