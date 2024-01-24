//
//  Weapon.hpp
//  rpgax
//
//  Created by Kyle Winfield Burnham on 1/16/24.
//

#ifndef Weapon_hpp
#define Weapon_hpp

#include <string>
#include <vector>
#include "WeaponMove.hpp"

static const unsigned short TOTAL_WEAPON_TYPES = 8;

enum WeaponType
{
    zweihander, flail, estoc, bow, spellbook, magicstaff, talisman, lightningspear, unarmed, randomized
};

static const std::string weaponTypes[] =
{
    "Zweihander", "Flail", "Estoc", "Bow", "Spellbook", "Magic Staff", "Talisman", "Lightning Spear", "Unarmed"
};

enum WeaponDamageType
{
    physical, magic
};

class Weapon
{
private:
    std::string name;
    WeaponType type;
    WeaponDamageType damageType; // physical or magic
    int baseDamage; // base damage
    int grade; // this is a quality/rarity value for the weapon
    std::vector<WeaponMove> moves;
public:
    Weapon(WeaponType type = unarmed, int grade = 0);
    WeaponType getType() const;
    WeaponDamageType getDamageType() const;
    std::string getName() const;
    int getDamage() const; // weaponDamage + grade
    int getGrade() const;
    std::vector<WeaponMove> getMoves() const;
};

#endif /* Weapon_hpp */
