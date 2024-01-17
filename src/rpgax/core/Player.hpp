//
//  Player.hpp
//  rpgax
//
//  Created by Kyle Winfield Burnham on 1/16/24.
//

#ifndef Player_hpp
#define Player_hpp

#include "Character.hpp"

class Player : public Character
{
private:
    int souls = 0;
    int strength = 75;
    int dexterity = 75;
    int intelligence = 75;
    int faith = 75;
    
public:
    Player();
};

#endif /* Player_hpp */
