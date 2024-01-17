//
//  Weapon.cpp
//  rpgax
//
//  Created by Kyle Winfield Burnham on 1/16/24.
//

#include "Weapon.hpp"
using namespace std;

Weapon::Weapon(string name, int damage)
{
    this->name = name;
    this->damage = damage;
}

string Weapon::getName() const
{
    return name;
}

int Weapon::getDamage() const
{
    return damage;
}
