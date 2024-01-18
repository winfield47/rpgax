//
//  Weapon.cpp
//  rpgax
//
//  Created by Kyle Winfield Burnham on 1/16/24.
//

#include "Weapon.hpp"
using namespace std;

Weapon::Weapon(string name, int damage, WeaponType type)
{
    this->name = name;
    this->damage = damage;
    this->type = type;
}

string Weapon::getName() const
{
    return name;
}

int Weapon::getDamage() const
{
    return damage;
}

WeaponType Weapon::getType() const
{
    return type;
}
