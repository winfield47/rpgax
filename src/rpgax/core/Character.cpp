//
//  Character.cpp
//  rpgax
//
//  Created by Kyle Winfield Burnham on 1/16/24.
//

#include "Character.hpp"
using namespace std;

Character::Character(string asciiArt, int hp, int armor, int resistance, string description, string weaponName, int weaponDamage, WeaponType type, int strength, int dexterity, int intelligence, int faith)
{
    this->asciiArt = asciiArt;
    this->hp = hp;
    this->armor = armor;
    this->resistance = resistance;
    this->description = description;
    this->weapon = Weapon(weaponName, weaponDamage, type);
    this->strength = strength;
    this->dexterity = dexterity;
    this->intelligence = intelligence;
    this->faith = faith;
}

string Character::getAsciiArt() const {return asciiArt;}
string Character::getDescription() const {return description;}
const Weapon& Character::getWeapon() const {return weapon;}
int Character::getHP() const {return hp;}
int Character::getArmor() const {return armor;}
int Character::getResistance() const {return resistance;}
int Character::getStrength() const {return strength;}
int Character::getDexterity() const {return dexterity;}
int Character::getIntelligence() const {return intelligence;}
