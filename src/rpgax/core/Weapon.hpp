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



enum WeaponType
{
    zweihander, flail, estoc, dagger, bow, spellbook, magicstaff, talisman, lightningspear, unarmed, randomized, special
};

static const std::string weaponTypes[] =
{
    "Zweihander", "Flail", "Estoc", "Dagger", "Bow", "Spellbook", "Magic Staff", "Talisman", "Lightning Spear", "Unarmed"
};

enum WeaponDamageType
{
    physical, magic
};

class Weapon
{
private:
    // Properties
    std::string name;
    WeaponType type;
    WeaponDamageType damageType; // physical or magic
    int baseDamage; // base damage
    int grade; // this is a quality/rarity value for the weapon
    std::vector<WeaponMove> moves;
public:
    // Constructor
    Weapon();
    Weapon(WeaponType type, int grade = 0);
    Weapon(std::string name, WeaponDamageType damageType, int baseDamage, int grade, std::vector<WeaponMove> moves);
    
    // Accessors
    WeaponType getType() const;
    WeaponDamageType getDamageType() const;
    std::string getName() const;
    int getDamage() const; // weaponDamage + grade
    int getGrade() const;
    std::vector<WeaponMove> getMoves() const;
    
    // Public Property
    static const unsigned short TOTAL_WEAPON_TYPES = 8;
};

#endif /* Weapon_hpp */
