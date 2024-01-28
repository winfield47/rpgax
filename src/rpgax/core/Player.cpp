//
//  Player.cpp
//  rpgax
//
//  Created by Kyle Winfield Burnham on 1/16/24.
//

#include "Player.hpp"

// Constructors
Player::Player(){}
Player::Player(Origin origin, std::string playerName){
    this->origin = origin;
    description = playerName;
    level = 0;
    vigor = 0;
    armor = 0;
    resistance = 0;
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
            weapon = Weapon(zweihander);
            apparel = Apparel("Hide", 2);
            break;
            
        case rogue:
            asciiArt = "`0~";//   `0~
            strength = 68;
            dexterity = 75;
            intelligence = 67;
            faith = 70;
            souls = 5;
            weapon = Weapon(estoc);
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
            weapon.setPlayerIntelligenceModifier(intelligence);
            weapon = Weapon(spellbook);
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
            weapon = Weapon(talisman);
            apparel = Apparel("Leather", 1);
            cloak = Cloak("Tattered", 1);
            potion = Potion("Healing", 5);
            break;
            
        default:
        case nomad:
            asciiArt = "\\o/";//   \o/
            strength = 70;
            dexterity = 70;
            intelligence = 70;
            faith = 70;
            souls = 22;
            weapon = Weapon(unarmed);
            break;
    }
    
    hpMax = hp = 20 + (strength - 70) * 2;
    armor = apparel.grade;
    resistance = cloak.grade;
    weapon.setPlayerIntelligenceModifier(intelligence);
    weapon.setPlayerFaithModifier(faith);
    
}

// Accessors
std::string Player::getName() const{
    return description;
}
Origin Player::getOrigin() const{
    return origin;
}
int Player::getSouls() const{
    return souls;
}
int Player::getLevel() const{
    return level;
}
int Player::getArmor() const{
    return armor;
}
int Player::getResistance() const{
    return resistance;
}
Apparel Player::getApparel() const{
    return apparel;
}
Cloak Player::getCloak() const{
    return cloak;
}
Potion Player::getPotion() const{
    return potion;
}

// Methods
int Player::spendSouls(int soulsSpent){
    souls -= soulsSpent;
    return soulsSpent;
}
void Player::consumeSouls(int soulsSpent){
    souls -= soulsSpent;
    vigor += soulsSpent;
}
void Player::addSouls(int soulsAdded){
    souls += soulsAdded;
}
void Player::replaceApparel(Apparel newApparel){
    apparel = newApparel;
    armor = apparel.grade;
}
void Player::replaceCloak(Cloak newCloak){
    cloak = newCloak;
    resistance = cloak.grade;
}
void Player::replacePotion(Potion newPotion){
    potion = newPotion;
}
Potion Player::popPotion(){
    Potion usedPotion = potion;
    potion = Potion();
    return usedPotion;
}
