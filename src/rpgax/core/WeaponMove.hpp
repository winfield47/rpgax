//
//  WeaponMove.hpp
//  rpgax
//
//  Created by Kyle Winfield Burnham on 1/23/24.
//

#ifndef WeaponMove_hpp
#define WeaponMove_hpp

#include <string>

enum WeaponMoveAttribute
{
    strength, dexterity, intelligence, faith, none
};

class WeaponMove
{
private:
    // Properties
    std::string name;
    int amountOfChecks;
    WeaponMoveAttribute usedAttribute;
    float damagePercentage; // 0 -> 1 :: 0% -> 100%
    // if usedAttribute == none, accuracy SHOULD be 100%
    
public:
    // Constructors
    WeaponMove(std::string name); // 0 amountOfChecks, none usedAttribute, 0.6 damagePercentage
    WeaponMove(std::string name, int amountOfChecks, WeaponMoveAttribute usedAttribute); // 1 damagePercentage
    WeaponMove(std::string name, int amountOfChecks, WeaponMoveAttribute usedAttribute, float damagePercentage);
    
    // Accessors
    std::string getName() const;
    int getAmountOfChecks() const;
    WeaponMoveAttribute getUsedAttribute() const;
    float getDamagePercentage() const;
    
    
};

#endif /* WeaponMove_hpp */
