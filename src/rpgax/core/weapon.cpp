//
//  Weapon.cpp
//  rpgax
//
//  Created by Kyle Winfield Burnham on 1/16/24.
//

#include "weapon.h"

int Weapon::playerIntelligenceModifier = 0;
int Weapon::playerFaithModifier = 0;
int Weapon::enemyIntelligenceModifier = 0;
int Weapon::enemyFaithModifier = 0;
std::deque<WeaponType> Weapon::last4RandomizedWeaponTypes = {};

// Constructors
Weapon::Weapon(){}
Weapon::Weapon(WeaponType type, int grade){
    if (type == randomized)
    {
        bool randomizing = true;
        while (randomizing)
        {
            // keep randomizing the type until we get one we haven't seen in the last 4 randomized types
            type = static_cast<WeaponType>(rand() % TOTAL_PLAYER_WEAPON_TYPES);
            if (last4RandomizedWeaponTypes.size() != 0)
            {
                for (WeaponType weaponType : last4RandomizedWeaponTypes)
                {
                    if (type == weaponType)
                    {
                        randomizing = true;
                        break;
                    }
                    else
                    {
                        randomizing = false;
                    }
                }
            }
            else
            {
                randomizing = false;
            }
        }
        last4RandomizedWeaponTypes.push_back(type);
        if (last4RandomizedWeaponTypes.size() > 4)
        {
            last4RandomizedWeaponTypes.pop_front();
        }
    }
    else if (type == special)
    {
        throw "WeaponType \"special\" cannot be used to create a standard grade weapon. Please use the other Weapon constructor.";
    }
    this->type = type;
    this->name = weaponTypes[type];
    this->grade = grade;
    switch (type)
    {
        default:
            throw "Weapon constructor created a bad WeaponType";
        case zweihander:
            this->damageType = physical;
            this->baseDamage = 11;
            this->baseDamage += grade;
            moves.push_back(WeaponMove("Pommel Strike")); // creates a 60% dmg 100% accuracy move
            moves.push_back(WeaponMove("Great Slash", 4, strength)); // name, checks, attr
            break;
        case flail:
            this->damageType = physical;
            this->baseDamage = 7;
            this->baseDamage += grade;
            moves.push_back(WeaponMove("Reckless Attack", 0, noWeaponMoveAttribute, 1)); // creates a 100% dmg 100% accuracy move
            break;
        case estoc:
            this->damageType = physical;
            this->baseDamage = 9;
            this->baseDamage += grade;
            moves.push_back(WeaponMove("Lunge", 2, dexterity, 1));
            // parry will block all damage AND reflect what would have been dealt to the attacker
            moves.push_back(WeaponMove("Riposte", 1, dexterity, 0)); // does no dmg, but has a special effect
            break;
        case dagger:
            this->damageType = physical;
            this->baseDamage = 2;
            this->baseDamage += grade;
            moves.push_back(WeaponMove("Assassinate", 1, dexterity, 1));
            moves.push_back(WeaponMove("Stab", 0, noWeaponMoveAttribute, 1));
            break;
        case bow:
            this->damageType = physical;
            this->baseDamage = 6;
            this->baseDamage += grade + grade / 2;
            moves.push_back(WeaponMove("Called Shot"));
            moves.push_back(WeaponMove("Triple Draw", 3, dexterity, 1));
            break;
        case spellbook:
            this->damageType = magic;
            this->baseDamage = 0;
            this->baseDamage = grade + (playerIntelligenceModifier * 2); // spell book gets damage from INT mod
            moves.push_back(WeaponMove("Magic Missile", 0, noWeaponMoveAttribute, 1));
            // Spellshield will increase resistance by up to the int mod for the combat
            moves.push_back(WeaponMove("Spellshield", 1, intelligence, 0)); // does no dmg, but has a special effect
            // oakskin will increase armor by up to the int mod for the combat
            moves.push_back(WeaponMove("Oakskin", 2, intelligence, 0)); // does no dmg, but has a special effect
            break;
        case magicstaff:
            this->damageType = magic;
            this->baseDamage = 7;
            this->baseDamage += grade + grade / 2;
            moves.push_back(WeaponMove("Ice Bolt", 2, intelligence, 0.8));
            moves.push_back(WeaponMove("Fireball", 5, intelligence, 1));
            moves.push_back(WeaponMove("Time Blast", 1, intelligence, 1.2));
            break;
        case talisman:
            this->damageType = magic;
            this->baseDamage = 8;
            this->baseDamage += grade;
            moves.push_back(WeaponMove("Judgement", 2, faith, 1));
            // heal will heal the user for: FAI mod + grade
            moves.push_back(WeaponMove("Heal", 0, noWeaponMoveAttribute, 0)); // does no dmg, but has a special effect
            break;
        case lightningspear:
            this->damageType = magic;
            this->baseDamage = 12;
            this->baseDamage += grade + playerFaithModifier / 2;
            moves.push_back(WeaponMove("Zap"));
            moves.push_back(WeaponMove("Smite", 2, faith, 1));
            break;
        case unarmed:
            this->grade = 1; // always have access to punch and kick
            this->damageType = physical;
            this->baseDamage = 5;
            moves.push_back(WeaponMove("Punch")); // creates a 60% dmg 100% accuracy move
            moves.push_back(WeaponMove("Kick", 2, strength)); // creates a kick move with 2 checks that use STR at 100% damage
            break;
        case talons:
            this->damageType = physical;
            this->baseDamage = 2;
            this->baseDamage += grade;
            moves.push_back(WeaponMove("Talons", 2, dexterity, 1));
            moves.push_back(WeaponMove("Pluck", 5, dexterity, 1.5));
            break;
        case ravenbook:
            this->damageType = physical;
            this->baseDamage = 2;
            this->baseDamage += enemyIntelligenceModifier; // 69 is the minimum INT for floor 0 -> 1 dmg
            this->baseDamage += grade;
            moves.push_back(WeaponMove("Fling (Pebble)"));
            moves.push_back(WeaponMove("Fling (Stuff)", 2, intelligence, 1));
            moves.push_back(WeaponMove("Fling (Glass)", 4, intelligence, 1.4));
            break;
        case goop:
            this->damageType = physical;
            this->baseDamage = 1;
            this->baseDamage += grade;
            moves.push_back(WeaponMove("Pseudopod", 4, dexterity, 1));
            moves.push_back(WeaponMove("Touch", 1, dexterity, 2));
            break;
        case ghoulweapon:
            this->damageType = physical;
            this->baseDamage = 5;
            this->baseDamage += grade;
            moves.push_back(WeaponMove("Scratch"));
            moves.push_back(WeaponMove("Bite", 1, dexterity, 1));
            moves.push_back(WeaponMove("Flurry", 5, strength, 1.5));
            break;
        case giantclub:
            this->damageType = physical;
            this->baseDamage = 18;
            this->baseDamage += grade;
            moves.push_back(WeaponMove("Stumble", 0, noWeaponMoveAttribute, 0.1));
            moves.push_back(WeaponMove("Clobber", 5, strength, 1));
            moves.push_back(WeaponMove("Trip", 1, dexterity, 0.6));
            moves.push_back(WeaponMove("Wall Clank", 1, intelligence, 0.6));
            break;
        case hallowedarmorweapon:
            this->damageType = physical;
            this->baseDamage = 10;
            this->baseDamage += grade;
            moves.push_back(WeaponMove("Flail"));
            moves.push_back(WeaponMove("Tackle", 1, strength, 0.8));
            moves.push_back(WeaponMove("Pound", 2, dexterity, 0.9));
            moves.push_back(WeaponMove("Slam", 4, strength, 1));
            break;
    }
    
    // Have weapon moves become unlocked with higher weapon grades (i.e. Spellbook unlocks Oakskin at Grade 2)
    while (moves.size() > this->grade + 1)
    {
        moves.pop_back();
    }
}
Weapon::Weapon(std::string name, WeaponDamageType damageType, int baseDamage, int grade, std::vector<WeaponMove> moves){
    this->name = name;
    this->type = special;
    this->damageType = damageType;
    this->baseDamage = baseDamage;
    this->grade = grade;
    this->moves = moves;
}

// Accessors
int Weapon::getPlayerIntelligenceModifier(){
    return playerIntelligenceModifier;
}
int Weapon::getPlayerFaithModifier(){
    return playerFaithModifier;
}
int Weapon::getEnemyIntelligenceModifier(){
    return enemyIntelligenceModifier;
}
int Weapon::getEnemyFaithModifier(){
    return enemyFaithModifier;
}
std::string Weapon::getName() const{
    return name;
}
WeaponType Weapon::getType() const{
    return type;
}
WeaponDamageType Weapon::getDamageType() const{
    return damageType;
}
int Weapon::getDamage() const{
    if (baseDamage <= 0)
    {
        return 0;
    }
    return baseDamage;
}
int Weapon::getDamage(const WeaponMove &move) const{
    int totalDamage = move.getDamagePercentage() * baseDamage;
    if (totalDamage < 0)
    {
        totalDamage = 0;
    }
    return totalDamage;
}
int Weapon::getGrade() const{
    return grade;
}
std::vector<WeaponMove> Weapon::getMoves() const{
    return moves;
}

// Setters
void Weapon::setPlayerIntelligenceModifier(int currentIntelligenceModifier){
    playerIntelligenceModifier = currentIntelligenceModifier - 70;
}
void Weapon::setPlayerFaithModifier(int currentFaithModifier){
    playerFaithModifier = currentFaithModifier - 70;
}
void Weapon::setEnemyIntelligenceModifier(int currentIntelligenceModifier){
    enemyIntelligenceModifier = currentIntelligenceModifier - 70;
}
void Weapon::setEnemyFaithModifier(int currentFaithModifier){
    enemyFaithModifier = currentFaithModifier - 70;
}
