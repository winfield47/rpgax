//
//  Character.hpp
//  rpgax
//
//  Created by Kyle Winfield Burnham on 1/16/24.
//

#ifndef character_h
#define character_h

#include "weapon.h"

enum PlayerStatus
{
    nostatus, spellshield, oakskin, parrying
};

class Character
{
public:
    // Constructor
    Character();
    Character(std::string asciiArt, int hp, WeaponType weaponType, int weaponGrade, int armor, int resistance, std::string description, int strength, int dexterity, int intelligence, int faith);

    // Accessors
    virtual std::string getName() const;
    std::string getAsciiArt() const;
    std::string getDescription() const;
    const Weapon& getWeapon() const;
    int getHP() const;
    int getHPMax() const;
    virtual int getArmor() const;
    virtual int getResistance() const;
    int getStrength() const;
    int getDexterity() const;
    int getIntelligence() const;
    int getFaith() const;
    std::string getHighestAttribute() const;
    PlayerStatus getStatus() const;
    
    // Methods
    void takeDamage(int);
    int heal(int);
    void enterStatus(PlayerStatus);
    void exitStatus();
    void exitStatus(PlayerStatus);

protected:
    // Common attributes
    std::string asciiArt;
    std::string description;
    Weapon weapon;
    int hp;
    int hpMax;
    int armor;
    int resistance;
    int strength;
    int dexterity;
    int intelligence;
    int faith;
    PlayerStatus status;
};

#endif /* Character_hpp */
