//
//  Player.hpp
//  rpgax
//
//  Created by Kyle Winfield Burnham on 1/16/24.
//

#ifndef Player_hpp
#define Player_hpp

#include "Character.hpp"

enum Origin
{
    brute, rogue, wizard, inquisitor, nomad
};

class Player : public Character
{
private:
    Origin origin;
    int souls;
    int level;
public:
    Player();
};

#endif /* Player_hpp */
