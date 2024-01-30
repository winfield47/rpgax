//
//  Character.cpp
//  rpgax
//
//  Created by Kyle Winfield Burnham on 1/16/24.
//

#include "character.h"

// Constructors
Character::Character(){};
Character::Character(std::string asciiArt, int hp, WeaponType weaponType, int weaponGrade, int armor, int resistance, std::string description, int strength, int dexterity, int intelligence, int faith)
{
    this->asciiArt = asciiArt;
    this->hp = hp;
    this->hpMax = hp;
    this->armor = armor;
    this->resistance = resistance;
    this->description = description;
    this->weapon = Weapon(weaponType, weaponGrade);
    this->strength = strength;
    this->dexterity = dexterity;
    this->intelligence = intelligence;
    this->faith = faith;
}

// Accessors
std::string Character::getName() const{
    return description;
}
std::string Character::getAsciiArt() const{
    return asciiArt;
}
std::string Character::getDescription() const{
    return description;
}
const Weapon& Character::getWeapon() const{
    return weapon;
}
int Character::getHP() const{
    return hp;
}
int Character::getHPMax() const{
    return hpMax;
}
int Character::getArmor() const{
    return armor;
}
int Character::getResistance() const{
    return resistance;
}
int Character::getStrength() const{
    return strength;
}
int Character::getDexterity() const{
    return dexterity;
}
int Character::getIntelligence() const{
    return intelligence;
}
int Character::getFaith() const{
    return faith;
}

// Methods
void Character::takeDamage(int damageTaken){
    hp -= damageTaken;
    if (hp <= 0)
    {
        hp = 0;
    }
}
int Character::heal(int healthGained){
    hp += healthGained;
    if (hp >= hpMax)
    {
        healthGained += (hpMax - hp);
        hp = hpMax;
    }
    return healthGained;
}
