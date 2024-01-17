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
    // Accessible attributes
    Weapon weapon;
    
    // Constructor
    Character(std::string asciiArt, int hp, std::string description, std::string weaponName, int weaponDamage);

    // Common methods
    void displayInfo() const;

    // Accessors
    std::string getAsciiArt() const;
    int getHP() const;
    std::string getDescription() const;
    Weapon getWeapon() const;

protected:
    // Common attributes
    std::string asciiArt;
    int hp;
    std::string description;
};

#endif /* Character_hpp */
