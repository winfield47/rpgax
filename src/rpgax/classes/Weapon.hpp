//
//  Weapon.hpp
//  rpgax
//
//  Created by Kyle Winfield Burnham on 1/16/24.
//

#ifndef Weapon_hpp
#define Weapon_hpp

#include <string>

class Weapon {
private:
    std::string name;
    int damage;
public:
    Weapon(std::string name, int damage);
    std::string getName();
    int getDamage();
};

#endif /* Weapon_hpp */
