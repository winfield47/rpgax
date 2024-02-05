//
//  Weapon.hpp
//  rpgax
//
//  Created by Kyle Winfield Burnham on 1/16/24.
//

#ifndef weapon_h
#define weapon_h

#include <string>
#include <vector>
#include "weaponmove.h"

enum WeaponType
{
    zweihander,
    flail,
    estoc,
    dagger,
    bow,
    spellbook,
    magicstaff,
    talisman,
    lightningspear,
    unarmed,
    talons,
    ravenbook,
    ghoulweapon,
    giantclub,
    randomized,
    special
};

static const std::string weaponTypes[] =
{
    "Zweihander",
    "Flail",
    "Estoc",
    "Dagger",
    "Bow",
    "Spellbook",
    "Magic Staff",
    "Talisman",
    "Lightning Spear",
    "Unarmed",
    "Talons",
    "Raven's Spellbook",
    "Ghoul Weapon",
    "Giant Club"
};

enum WeaponDamageType
{
    physical, magic
};

class Weapon
{
private:
    // Static Properties
    static int playerIntelligenceModifier; // this is for keeping track of how much damage the spell book magic missile does
    static int playerFaithModifier; // this is for keeping track of how much healing the talisman does
    static int enemyIntelligenceModifier; // this is for keeping track of how much damage the spell book magic missile does
    static int enemyFaithModifier; // this is for keeping track of how much healing the talisman does
    
    // Properties
    std::string name;
    WeaponType type;
    WeaponDamageType damageType; // physical or magic
    int baseDamage; // base damage
    int grade; // this is a quality/rarity value for the weapon
    std::vector<WeaponMove> moves;
public:
    // Public Property
    static const unsigned short TOTAL_PLAYER_WEAPON_TYPES = 9;
    
    // Constructor
    Weapon();
    Weapon(WeaponType type, int grade = 0);
    Weapon(std::string name, WeaponDamageType damageType, int baseDamage, int grade, std::vector<WeaponMove> moves);
    
    // Accessors
    static int getPlayerIntelligenceModifier();
    static int getPlayerFaithModifier();
    static int getEnemyIntelligenceModifier();
    static int getEnemyFaithModifier();
    WeaponType getType() const;
    WeaponDamageType getDamageType() const;
    std::string getName() const;
    int getDamage() const; // weaponDamage + grade
    int getDamage(const WeaponMove&) const;
    int getGrade() const;
    std::vector<WeaponMove> getMoves() const;
    
    // Setters
    static void setPlayerIntelligenceModifier(int);
    static void setPlayerFaithModifier(int);
    static void setEnemyIntelligenceModifier(int);
    static void setEnemyFaithModifier(int);
};

#endif /* Weapon_hpp */
