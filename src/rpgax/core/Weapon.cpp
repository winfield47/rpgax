//
//  Weapon.cpp
//  rpgax
//
//  Created by Kyle Winfield Burnham on 1/16/24.
//

#include "Weapon.hpp"
using namespace std;

WeaponMove::WeaponMove(int amountOfChecks, WeaponMoveAttribute usedAttribute, float percentageOfMainDamageAsDamage)
{
    this->amountOfChecks = amountOfChecks;
    this->usedAttribute = usedAttribute;
    if (this->usedAttribute == none)
    {
        this->percentageOfMainDamageAsDamage = 1;
    }
    else
    {
        this->percentageOfMainDamageAsDamage = percentageOfMainDamageAsDamage;
    }
}

Weapon::Weapon(WeaponType type, int grade)
{
    if (type == randomized)
    {
        type = static_cast<WeaponType>(rand() % TOTAL_WEAPON_TYPES);
    }
    this->type = type;
    this->name = weaponTypes[type];
    this->grade = grade;
    switch (type)
    {
        default:
        case zweihander:
            this->damageType = physical;
            this->damage = 12;
            // ADD MOVES
            break;
        case flail:
            this->damageType = physical;
            this->damage = 9;
            // ADD MOVES
            break;
        case estoc:
            this->damageType = physical;
            this->damage = 7;
            // ADD MOVES
            break;
        case bow:
            this->damageType = physical;
            this->damage = 7;
            // ADD MOVES
            break;
        case spellbook:
            this->damageType = magic;
            this->damage = 0;
            // ADD MOVES
            break;
        case magicstaff:
            this->damageType = magic;
            this->damage = 4;
            // ADD MOVES
            break;
        case talisman:
            this->damageType = magic;
            this->damage = 8;
            // ADD MOVES
            break;
        case lightningspear:
            this->damageType = magic;
            this->damage = 12;
            // ADD MOVES
            break;
        case unarmed:
            this->damageType = physical;
            this->damage = 5;
            this->grade = 0;
            // ADD MOVES
            break;
    }
    this->damage += grade;
    
}

string Weapon::getName() const
{
    return name;
}

int Weapon::getDamage() const
{
    return damage;
}

WeaponDamageType Weapon::getType() const
{
    return damageType;
}
