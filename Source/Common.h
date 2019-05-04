/*
  ==============================================================================

    Common.h
    Created: 28 Apr 2019 7:23:51am
    Author:  Adam Shield

  ==============================================================================
*/

#pragma once
#define NA false
#define for_indexed(...) for_indexed_v(i, __VA_ARGS__)
#define for_indexed_v(v, ...) for(bool _i_ = true, _break_ = false; _i_;) for(size_t v = 0; _i_; _i_ = false) for(__VA_ARGS__) if(_break_) break; else for(bool _j_ = true; _j_;) for(_break_ = true; _j_; _j_ = false) for(bool _k_ = true; _k_; v++, _k_ = false, _break_ = false)

#include "../JuceLibraryCode/JuceHeader.h"
#include <optional>


enum DieType{
    D2,
    D3,
    D4,
    D6,
    D8,
    D10,
    D20,
    none
};

struct Die{
    int numOfDice;
    DieType dieType;
    
    Die(const DieType& die){
        numOfDice=0;
        dieType = die;
    }
    
    Die(int num, const DieType& die){
        numOfDice=num;
        dieType = die;
    }
    
    Die() = default;
    
};


constexpr int dieToNum(DieType& die){
    switch(die){
        case D2:  return 2;
        case D3:  return 3;
        case D4:  return 4;
        case D6:  return 6;
        case D8:  return 8;
        case D10: return 10;
        case D20: return 20;
        case none: return 0;
    }
}

constexpr int abilityMod(int input) {return static_cast<int>((input-10)/2);}



namespace MyFonts {
    
    static const Font& getCourierNew(){
        return (Font (Typeface::createSystemTypefaceFor (BinaryData::Courier_New_ttf,
                                                                         BinaryData::Courier_New_ttfSize)));
    }
    
    static const Font& getBaskerville(){
        return (Font (Typeface::createSystemTypefaceFor (BinaryData::Baskerville_ttc,
                                                         BinaryData::Baskerville_ttcSize)));
    }
    
}
