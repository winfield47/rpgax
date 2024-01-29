//
//  WeaponMove.cpp
//  rpgax
//
//  Created by Kyle Winfield Burnham on 1/23/24.
//

#include "weaponmove.h"

// Constructors
WeaponMove::WeaponMove(){}
WeaponMove::WeaponMove(std::string name){
    this->name = name;
    this->amountOfChecks = 0;
    this->usedAttribute = noWeaponMoveAttribute;
    this->damagePercentage = 0.6;
}
WeaponMove::WeaponMove(std::string name, int amountOfChecks, WeaponMoveAttribute usedAttribute){
    this->name = name;
    this->amountOfChecks = amountOfChecks;
    this->usedAttribute = usedAttribute;
    this->damagePercentage = 1;
}
WeaponMove::WeaponMove(std::string name, int amountOfChecks, WeaponMoveAttribute usedAttribute, float damagePercentage){
    this->name = name;
    this->amountOfChecks = amountOfChecks;
    this->usedAttribute = usedAttribute;
    this->damagePercentage = damagePercentage;
}

// Accessors
std::string WeaponMove::getName() const{
    return name;
}
int WeaponMove::getAmountOfChecks() const{
    return amountOfChecks;
}
WeaponMoveAttribute WeaponMove::getUsedAttribute() const{
    return usedAttribute;
}
float WeaponMove::getDamagePercentage() const{
    return damagePercentage;
}
