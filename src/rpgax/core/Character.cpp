//
//  Character.cpp
//  rpgax
//
//  Created by Kyle Winfield Burnham on 1/16/24.
//

#include "Character.hpp"
using namespace std;

Character::Character(string asciiArt, int hp, string description, string weaponName, int weaponDamage)
{
    this->asciiArt = asciiArt;
    this->hp = hp;
    this->description = description;
    this->weapon = Weapon(weaponName, weaponDamage);
}

string Character::getAsciiArt() const
{
    return asciiArt;
}

int Character::getHP() const
{
    return hp;
}

string Character::getDescription() const
{
    return description;
}

Weapon Character::getWeapon() const
{
    return weapon;
}
