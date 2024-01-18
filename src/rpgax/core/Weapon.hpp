//
//  Weapon.hpp
//  rpgax
//
//  Created by Kyle Winfield Burnham on 1/16/24.
//

#ifndef Weapon_hpp
#define Weapon_hpp

#include <string>

enum WeaponType
{
    physical, magic
};

class Weapon
{
private:
    std::string name;
    int damage;
    WeaponType type;
public:
    Weapon(std::string name = "none", int damage = 0, WeaponType type = physical);
    std::string getName() const;
    int getDamage() const;
    WeaponType getType() const;
};

#endif /* Weapon_hpp */
