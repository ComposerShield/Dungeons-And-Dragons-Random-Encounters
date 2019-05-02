/*
  ==============================================================================

    Skills.h
    Created: 19 Apr 2019 10:58:24pm
    Author:  Adam Shield

  ==============================================================================
*/

#pragma once
#include "Common.h"

enum Ability{
    STR,
    DEX,
    CON,
    INT,
    WIS,
    CHA
};

struct Skill{
    String name;
    Ability keyAbility;
    int ranks;
    int miscMod;
    int keyAbilityMod;
    
    int abilityFromArray(const Array<int>& abilities){
        switch(keyAbility){
            case STR: return abilities[0];
            case DEX: return abilities[1];
            case CON: return abilities[2];
            case INT: return abilities[3];
            case WIS: return abilities[4];
            case CHA: return abilities[5];
        }
    }
    void calculateKeyAbilityMod(const int abilityVal){
        keyAbilityMod = abilityMod(abilityVal);
    }
    constexpr int abilityMod(int input) const {return static_cast<int>((input-10)/2);}
    constexpr int total(){return ranks+miscMod+keyAbilityMod;}
    Skill(String Name, Ability KeyAbility){name=Name; keyAbility = KeyAbility;}
};

namespace Skills {
    static Skill        appraise        ("appraise", INT),
                        balance         {"balance", DEX},
                        bluff           {"bluff", CHA},
                        climb           {"climb", STR},
                        concentration   {"concentration", CON},
                        craft           {"craft", INT},
                        decipher_script {"decipher script", INT},
                        diplomacy       {"diplomacy", CHA},
                        disable_device  {"disable_device", INT},
                        disguise        {"disguise", CHA},
                        escape_artist   {"escape artist", DEX},
                        forgery         {"forgery", INT},
                        gather_info     {"gather info", CHA},
                        handle_animal   {"handle animal", CHA},
                        heal            {"heal", WIS},
                        hide            {"hide", DEX},
                        intimidate      {"intimidate", CHA},
                        jump            {"jump", STR},
                        knowledge       {"knowledge", INT},
                        listen          {"listen", WIS},
                        move_silently   {"move silently", DEX},
                        open_lock       {"open lock", DEX},
                        perform         {"perform", CHA},
                        profession      {"profession", WIS},
                        ride            {"ride", DEX},
                        search          {"search", INT},
                        sense_motive    {"sense motive", WIS},
                        slight_of_hand  {"slight of hand", DEX},
                        spellcraft      {"spellcraft", INT},
                        spot            {"spot", WIS},
                        survival        {"survival", WIS},
                        swim            {"swim", STR},
                        tumble          {"tumble", DEX},
                        use_magic_dev   {"use magic dev", CHA},
                        use_rope        {"use rope", DEX};
    
    
    inline Array<Skill> skillList = {
        appraise,
        balance,
        bluff,
        climb,
        concentration,
        craft,
        decipher_script,
        diplomacy,
        disable_device,
        disguise,
        escape_artist,
        forgery,
        gather_info,
        handle_animal,
        heal,
        hide,
        intimidate,
        jump,
        knowledge,
        listen,
        move_silently,
        open_lock,
        perform,
        profession,
        ride,
        search,
        sense_motive,
        slight_of_hand,
        spellcraft,
        spot,
        survival,
        swim,
        tumble,
        use_magic_dev,
        use_rope
    };

}


