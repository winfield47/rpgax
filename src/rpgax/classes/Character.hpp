//
//  Character.hpp
//  rpgax
//
//  Created by Kyle Winfield Burnham on 1/16/24.
//

#ifndef Character_hpp
#define Character_hpp

#include "Weapon.hpp"

class Character {
public:
    // Accessible Attributes
    Weapon weapon;
    
    // Constructor
    Character(std::string asciiArt, int hp, Weapon weapon, std::string description);

    // Virtual destructor to ensure proper cleanup
    virtual ~Character();

    // Common methods
    void displayInfo() const;

    // Accessors
    std::string getArt() const;
    int getHP() const;
    std::string getDescription();

protected:
    // Common attributes
    std::string asciiArt;
    int hp;
    std::string description;
};

#endif /* Character_hpp */
