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
    int level;
    int souls; // This is the currency AND the resource for leveling up in the game
    int vigor; // This is the name for "EXPERIENCE" in this game since you consum souls to become vigorous
    Apparel apparel;
    Cloak cloak;
    Potion potion;
public:
    Player();
    Player(Origin origin, std::string playerName);
    Origin getOrigin() const;
    int getSouls() const;
    int getLevel() const;
    Apparel getApparel() const;
    Cloak getCloak() const;
    Potion getPotion() const;
    int spendSouls(int);
    void consumeSouls(int);
    void addSouls(int);
    void replaceApparel(Apparel);
    void replaceCloak(Cloak);
    void replacePotion(Potion);
    Potion popPotion(Potion);
};

#endif /* Player_hpp */
