//
//  Enemy.cpp
//  rpgax
//
//  Created by Kyle Winfield Burnham on 1/25/24.
//

#include "enemy.h"

// Constructors
Enemy::Enemy(){}
Enemy::Enemy(EnemyType type, int floorLevel){
    this->floorLevel = floorLevel;
    variance = 3;
    switch (type)
    {
        case pigeon:
            asciiArt = "<@\\";
            name = "Pigeon";
            description = "A giant, fat pigeon… it can't even fly!";
            weapon = Weapon(unarmed);
            strength = 62;
            dexterity = 50;
            intelligence = 50;
            faith = 50;
            armor = 0;
            resistance = 0;
            break;
        case goblin:
            asciiArt = "\\g\\";
            name = "Goblin";
            description = "A goblin trying to rob you of your life!";
            weapon = Weapon(dagger, floorLevel);
            strength = 63;
            dexterity = 74;
            intelligence = 65;
            faith = 70;
            armor = 0;
            resistance = 0;
            break;
        case drow:
            if (rand() % 2 == 0)
            {
                asciiArt = "}0{";
                name = "Drow Mage";
                description = "A dark elf mage with a funny hat!";
                weapon = Weapon(magicstaff, floorLevel);
                strength = 63;
                dexterity = 67;
                intelligence = 70;
                faith = 65;
                armor = 0;
                resistance = 1;
            }
            else
            {
                asciiArt = "^0^";
                name = "Drow Ranger";
                description = "A dark elf woodsman with a feather hat!";
                weapon = Weapon(bow, floorLevel);
                strength = 64;
                dexterity = 70;
                intelligence = 65;
                faith = 68;
                armor = 0;
                resistance = 0;
            }
            break;
        case slime:
            asciiArt = "[Œ]";
            description = "What is this thing..? It's made of slime and not letting you pass.";
            weapon = Weapon();
            // weapon = Weapon("It's body…", physical, 6, floorLevel, std::vector<WeaponMove>(WeaponMove("Pseudopod", 3, strength, 1)));
            strength = 90;
            dexterity = 0;
            intelligence = 0;
            faith = 0;
            armor = 10;
            resistance = 0;
            break;
        default:
            variance = 0;
            asciiArt = "\\ø/";
            name = "Enemy";
            description = "A lowly enemy… nothing but a foot soldier.";
            weapon = Weapon(unarmed);
            strength = 60;
            dexterity = 60;
            intelligence = 60;
            faith = 60;
            armor = 0;
            resistance = 0;
            break;
    }
    varyStats();
    
    hpMax = hp = 20 + ((floorLevel + 1) * 1.5) + (strength - 70) * 2;
    if (hpMax <= 0) { hpMax = hp = 1; }
    
    weapon.setEnemyIntelligenceModifier(intelligence);
    weapon.setEnemyFaithModifier(faith);
    chooseMove();
}
void Enemy::varyStats(){
    strength += (rand() % variance / 2) - (rand() % variance / 2);
    dexterity += (rand() % variance) - (rand() % variance);
    intelligence += (rand() % variance) - (rand() % variance);
    faith += (rand() % variance) - (rand() % variance);
    if (floorLevel > 0)
    {
        armor += ((rand() % floorLevel) - rand() % floorLevel) <= 0 ? 0 : (rand() % floorLevel);
        resistance += (rand() % floorLevel) <= 0 ? 0 : (rand() % floorLevel);
    }
} // This helps the constructor look prettier

// Accessors
std::string Enemy::getName() const{
    return name;
}
WeaponMove Enemy::getChosenMove(){
    chosenMove = weapon.getMoves().at(chosenMoveIndex);
    return chosenMove;
}

// Methods
void Enemy::chooseMove(){
    chosenMoveIndex = rand() % weapon.getMoves().size();
}
