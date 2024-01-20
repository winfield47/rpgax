//
//  Player.hpp
//  rpgax
//
//  Created by Kyle Winfield Burnham on 1/16/24.
//

#ifndef Player_hpp
#define Player_hpp

#include "Character.hpp"
#include "Items.hpp"

enum Origin
{
    brute, rogue, wizard, inquisitor, nomad
};

class Player : public Character
{
private:
    Origin origin;
    std::string name;
    int souls;
    int level;
    Apparel apparel;
    Cloak cloak;
    Potion potion;
public:
    Player();
    Player(Origin origin, std::string playerName);
};

#endif /* Player_hpp */
