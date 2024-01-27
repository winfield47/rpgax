//
//  Character.hpp
//  rpgax
//
//  Created by Kyle Winfield Burnham on 1/16/24.
//

#ifndef Character_hpp
#define Character_hpp

#include "Weapon.hpp"

class Character
{
public:
    // Constructor
    Character();
    Character(std::string asciiArt, int hp, WeaponType weaponType, int weaponGrade, int armor, int resistance, std::string description, int strength, int dexterity, int intelligence, int faith);

    // Accessors
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
    
    // Methods
    void takeDamage(int);

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
};

#endif /* Character_hpp */
