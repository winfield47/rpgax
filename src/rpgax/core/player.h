//
//  Player.hpp
//  rpgax
//
//  Created by Kyle Winfield Burnham on 1/16/24.
//

#ifndef player_h
#define player_h

#include "character.h"
#include "items.h"

enum Origin
{
    brute, rogue, wizard, inquisitor, nomad
};

class Player : public Character
{
private:
    // Properties
    Origin origin;
    int level;
    int souls; // This is the currency AND the resource for leveling up in the game
    int vigor; // This is the name for "EXPERIENCE" in this game since you consum souls to become vigorous
    Apparel apparel;
    Cloak cloak;
    Potion potion;
public:
    // Constructors
    Player();
    Player(Origin origin, std::string playerName);
    
    // Accessors
    std::string getName() const;
    Origin getOrigin() const;
    int getSouls() const;
    int getLevel() const;
    virtual int getArmor() const override;
    virtual int getResistance() const override;
    Apparel getApparel() const;
    Cloak getCloak() const;
    Potion getPotion() const;
    
    // Methods
    int spendSouls(int);
    void consumeSouls(int);
    void addSouls(int);
    void replaceApparel(Apparel);
    void replaceCloak(Cloak);
    void replacePotion(Potion);
    Potion popPotion();
};

#endif /* Player_hpp */
