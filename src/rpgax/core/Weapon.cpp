//
//  Weapon.cpp
//  rpgax
//
//  Created by Kyle Winfield Burnham on 1/16/24.
//

#include "Weapon.hpp"

int Weapon::playerIntelligenceModifier = 0;
int Weapon::playerFaithModifier = 0;
int Weapon::enemyIntelligenceModifier = 0;
int Weapon::enemyFaithModifier = 0;

// Constructors
Weapon::Weapon(){}
Weapon::Weapon(WeaponType type, int grade){
    if (type == randomized)
    {
        type = static_cast<WeaponType>(rand() % TOTAL_WEAPON_TYPES);
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
        case zweihander:
            this->damageType = physical;
            this->baseDamage = 12;
            this->baseDamage += grade;
            moves.push_back(WeaponMove("Pommel Strike")); // creates a 60% dmg 100% accuracy move
            moves.push_back(WeaponMove("Great Slash", 4, strength)); // name, checks, attr
            break;
        case flail:
            this->damageType = physical;
            this->baseDamage = 8;
            this->baseDamage += grade;
            moves.push_back(WeaponMove("Reckless Attack", 0, noWeaponMoveAttribute, 1)); // creates a 100% dmg 100% accuracy move
            break;
        case estoc:
            this->damageType = physical;
            this->baseDamage = 9;
            this->baseDamage += grade;
            moves.push_back(WeaponMove("Lunge"));
            // parry will block all damage AND reflect what would have been dealt to the attacker
            moves.push_back(WeaponMove("Parry", 1, dexterity, 0)); // does no dmg, but has a special effect
            break;
        case dagger:
            this->damageType = physical;
            this->baseDamage = 2;
            this->baseDamage += grade * 2;
            moves.push_back(WeaponMove("Stab"));
            moves.push_back(WeaponMove("Assassinate", 1, dexterity, 1));
            break;
        case bow:
            this->damageType = physical;
            this->baseDamage = 6;
            this->baseDamage += grade;
            moves.push_back(WeaponMove("Called Shot"));
            moves.push_back(WeaponMove("Triple Draw", 1, dexterity, 1));
            break;
        case spellbook:
            this->damageType = magic;
            this->baseDamage = 0 + playerIntelligenceModifier; // spell book gets damage from INT mod
            moves.push_back(WeaponMove("Magic Missile", 0, noWeaponMoveAttribute, 1));
            // Spellshield will increase resistance by up to the int mod for the combat
            moves.push_back(WeaponMove("Spellshield", 3, intelligence, 0)); // does no dmg, but has a special effect
            // oakskin will increase armor by up to the int mod for the combat
            moves.push_back(WeaponMove("Oakskin", 3, intelligence, 0)); // does no dmg, but has a special effect
            break;
        case magicstaff:
            this->damageType = magic;
            this->baseDamage = 4;
            this->baseDamage += grade * 2;
            moves.push_back(WeaponMove("Fireball", 5, intelligence, 1));
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
            this->baseDamage += grade;
            moves.push_back(WeaponMove("Zap"));
            moves.push_back(WeaponMove("Smite", 2, faith, 1));
            break;
        case unarmed:
            this->damageType = physical;
            this->baseDamage = 5;
            this->grade = 1;
            moves.push_back(WeaponMove("Punch")); // creates a 60% dmg 100% accuracy move
            moves.push_back(WeaponMove("Kick", 2, strength)); // creates a kick move with 2 checks that use STR at 100% damage
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
    return baseDamage;
}
int Weapon::getDamage(WeaponMove &move) const{
    return move.getDamagePercentage() * baseDamage;
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
