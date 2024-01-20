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

static const unsigned short TOTAL_WEAPON_TYPES = 8;

enum WeaponType
{
    zweihander, flail, estoc, bow, spellbook, magicstaff, talisman, lightningspear, unarmed, randomized
};

static const std::string weaponTypes[] =
{
    "Zweihander", "Flail", "Estoc", "Bow", "Spellbook", "Magic Staff", "Talisman", "Lightning Spear", "Unarmed"
};

enum WeaponMoveAttribute
{
    strength, dexterity, intelligence, faith, none
};

enum WeaponDamageType
{
    physical, magic
};

struct WeaponMove
{
    // Properties
    std::string name;
    int amountOfChecks;
    WeaponMoveAttribute usedAttribute;
    float percentageOfMainDamageAsDamage; // 0 -> 1 :: 0% -> 100%
    // if usedAttribute == none, accuracy will be 100%
    
    // Constructors
    WeaponMove(std::string name);
    WeaponMove(std::string name, int amountOfChecks, WeaponMoveAttribute usedAttribute, float percentageOfMainDamageAsDamage);
};

class Weapon
{
private:
    WeaponType type;
    std::string name;
    WeaponDamageType damageType; // physical or magic
    int damage; // base damage
    int grade; // this is a quality/rarity value for the weapon
    std::vector<WeaponMove> moves;
public:
    Weapon(WeaponType type = unarmed, int grade = 0);
    WeaponDamageType getDamageType() const;
    std::string getName() const;
    int getDamage() const;
    int getGrade() const;
};

#endif /* Weapon_hpp */
