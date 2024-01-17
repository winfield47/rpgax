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
    Character(std::string asciiArt, int hp, int armor, int resistance, std::string description, std::string weaponName, int weaponDamage);

    // Accessors
    std::string getAsciiArt() const;
    int getHP() const;
    std::string getDescription() const;
    const Weapon& getWeapon() const;

protected:
    // Common attributes
    std::string asciiArt;
    int hp;
    int armor;
    int resistance;
    std::string description;
    Weapon weapon;
};

#endif /* Character_hpp */
