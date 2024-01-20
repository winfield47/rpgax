//
//  Player.cpp
//  rpgax
//
//  Created by Kyle Winfield Burnham on 1/16/24.
//

#include "Player.hpp"
using namespace std;

Player::Player()
{
    
}

Player::Player(Origin origin, string playerName)
{
    this->origin = origin;
    name = playerName;
    description = "You";
    level = 0;
    weapon = Weapon();
    apparel = Apparel();
    cloak = Cloak();
    potion = Potion();
    
    switch (origin) {
            
        case brute:
            asciiArt = "|O|";//   |O|
            strength = 75;
            dexterity = 69;
            intelligence = 65;
            faith = 71;
            souls = 2;
            weapon = Weapon();
            apparel = Apparel("Hide", 2);
            break;
            
        case rogue:
            asciiArt = "`0~";//   `0~
            strength = 68;
            dexterity = 75;
            intelligence = 67;
            faith = 70;
            souls = 5;
            weapon = Weapon();
            apparel = Apparel("Leather", 1);
            cloak = Cloak("Tattered", 1);
            break;
        
        case wizard:
            asciiArt = ")^(";//   )^(
            strength = 65;
            dexterity = 72;
            intelligence = 75;
            faith = 68;
            souls = 4;
            weapon = Weapon();
            cloak = Cloak("Hooded", 2);
            potion = Potion("Healing", 5);
            break;
            
        case inquisitor:
            asciiArt = "/?\\";//   /?\         /
            strength = 72;
            dexterity = 65;
            intelligence = 68;
            faith = 75;
            souls = 1;
            weapon = Weapon();
            apparel = Apparel("Leather", 1);
            cloak = Cloak("Tattered", 1);
            potion = Potion("Healing", 5);
            break;
            
        case nomad:
        default:
            asciiArt = "\\o/";//   \o/
            strength = 70;
            dexterity = 70;
            intelligence = 70;
            faith = 70;
            souls = 22;
            break;
    }
    
    hp = (strength - 70) * 2;
    
    
    //asciiArt;
    //description;
    //weapon;
    //hp;
    //armor;
    //resistance;
    //strength;
    //dexterity;
    //intelligence;
    //faith;
    
}

