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
    initiative = init;
    hp = HP;
}

void Character::evaluateCharacterSheet(){
    
}


