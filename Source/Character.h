/*
  ==============================================================================

    Character.h
    Created: 19 Apr 2019 10:32:10pm
    Author:  Adam Shield

  ==============================================================================
*/

#pragma once

#include "Skills.h"
#include "Items.h"
#include "Classes.h"
#include "array"
#include "optional"
#include "variant"
#include "Common.h"

struct Feat;

class Character{
public:
    int strength, dexterity, constitution, intelligence, wisdom, charisma,
        baseFort, baseRef, baseWill, miscFort, miscRef, miscWill, sizeMod,
        baseAttackBonus, initiative, initMiscMod, hp, touchAC, touchACMisc,
        currentHP, meleeMiscBonus, rangedMiscBonus, miscHP{0}, ac, grapple,
    baseInitiative, characterLevel{1}, fort, ref, will, skillRankCap;
    
    constexpr int getLevel(){
        int sum{0};
        for(auto& thisClass : classes)
            sum += thisClass.level;
        return sum;
    }
    std::optional<int> casterLevel;
    Array<int*> abilityList;
    
    Character(Array<int> abilities, int baseAttack, int init);
    virtual ~Character(){};
    
    String race;
    Array<Class> classes;
    Array<String> description;
    struct EquippedWeapons : Array<Weapons::Weapon>{};
    
    struct EquippedArmor   : Array<Armors::Armor>{
        constexpr int addArmor()     const {
            int output=0;
            for (auto& armor : *this) output+=armor.ac;
            return output;
        }
    };
    
    EquippedWeapons equippedWeapons;
    EquippedArmor   equippedArmor;
    const Array<Skill> skills = Skills::skillList;
    std::map<String, Skill&> skillMap;
    Array<Feat>  feats;
    Array<Weapons::Weapon> weaponProficiencies;
    Die HD{1, D8}; //default
    
    
    std::pair<void*, int> characterImageData;
    Image characterImage;
    
    Skill& getSkill(String skill);
    void evaluateCharacterSheet();
    
    virtual Image getImage() = 0;
    
private:
    constexpr int getFortitude()  const {return baseFort + abilityMod(constitution) + miscFort;}
    constexpr int getReflex()     const {return baseRef  + abilityMod(dexterity)    + miscRef ;}
    constexpr int getWill()       const {return baseWill + abilityMod(wisdom)       + miscWill;}
    constexpr int getAC()         const {return equippedArmor.addArmor() + abilityMod(dexterity) + sizeMod; }
    constexpr int getTouchAC()    const {return abilityMod(dexterity) + sizeMod;}
    constexpr int getInitiative() const {return baseInitiative + initMiscMod;}
    constexpr int getGrapple()    const {return baseAttackBonus + abilityMod(strength) + sizeMod;}
    constexpr int rollForInitiative()   {return initiative + random.nextInt(2) + 1;};
    
    int rollHD() const;
    Array<int> abilitiesAsArray() const {return {strength, dexterity, constitution, intelligence, wisdom, charisma};};
    void randomize();
    void populateSkills(Array<std::pair<Skill, int>> skillList);
    void populateSkillMap(){for(auto& skill : skills) skillMap.insert({skill.name, skill});}
    virtual void setSkillRankCap(){skillRankCap = 4 + characterLevel-1;};
 
protected:
    mutable Random random;
    Skill& randomSkill(){return skills.getReference(0);}
    Array<Weapons::Weapon> defaultWeapons{Weapons::gauntlet, Weapons::unarmed, Weapons::dagger};
};


class NPC : public Character{
private:
    template<typename t>
    struct Preferred{
        Array<t> highChance;
        Array<t> mediumChance;
        Array<t> lowChance;
        
        Preferred() = default;
        void fill(Array<t> high,Array<t> med,Array<t> low){
            highChance = high;
            mediumChance = med;
            lowChance = low;
        }
        void singlePrefArray(Array<t> high){
            highChance = high;
        }
    };
    
protected:
    struct PreferredWeapons : public Preferred<Weapons::Weapon>{};
    struct PreferredArmor   : public Preferred<Armors::Armor>{};
    struct PreferredFeats   : public Preferred<Feat>{};
    struct PreferredSkills  : public Preferred<Skill>{};
    
public:
    NPC(Array<int> abilities, int baseAttack, int init) : Character(abilities, baseAttack, init){}
    virtual ~NPC(){};
    PreferredWeapons preferredWeapons;
    PreferredArmor  preferredArmor;
    PreferredSkills preferredSkills;
    PreferredFeats  preferredFeats;
    double cr;
    
private:
    
    template<typename t>
    t getRandomFromPref(const Preferred<t>&);
    
    template<typename t>
    t grabFromPrefList(Array<t> list);
    
    void setSkillRankCap() override {skillRankCap = 4 + static_cast<int>(cr);};
    
protected:
    void finalizeNPC();
};

class PC : public Character{
    PC (Array<int> abilities, int baseAttack, int init) : Character(abilities, baseAttack, init){}
    virtual ~PC(){};
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

