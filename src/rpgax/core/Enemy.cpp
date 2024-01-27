//
//  Enemy.cpp
//  rpgax
//
//  Created by Kyle Winfield Burnham on 1/25/24.
//

#include "Enemy.hpp"
using namespace std;

// Constructors
Enemy::Enemy() {}
Enemy::Enemy(EnemyType type, int floorLevel)
{
    this->floorLevel = floorLevel;
    variance = 3;
    switch (type)
    {
        default:
            asciiArt = "\\ø/";
            name = "Enemy";
            description = "A lowly enemy.";
            weapon = Weapon();
            strength = 70;
            dexterity = 70;
            intelligence = 70;
            faith = 70;
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
            faith = 75;
            armor = 0;
            resistance = 0;
            break;
        case slime:
            asciiArt = "OOZ";
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
    }
    varyStats();
    
    hpMax = hp = 20 + ((floorLevel + 1) * 1.5) + (strength - 70) * 2;
    
    moveChooser = rand() % weapon.getMoves().size();
    weapon.setCharacterIntelligenceModifier(intelligence);
    weapon.setCharacterFaithModifier(faith);
}
void Enemy::varyStats() // This helps the constructor look prettier
{
    strength += (rand() % variance / 2) - (rand() % variance / 2);
    dexterity += (rand() % variance) - (rand() % variance);
    intelligence += (rand() % variance) - (rand() % variance);
    faith += (rand() % variance) - (rand() % variance);
    if (floorLevel > 0)
    {
        armor += ((rand() % floorLevel) - rand() % floorLevel) <= 0 ? 0 : (rand() % floorLevel);
        resistance += (rand() % floorLevel) <= 0 ? 0 : (rand() % floorLevel);
    }
}

// Accessors
size_t Enemy::getMoveChooser() const
{
    return moveChooser;
}
string Enemy::getName() const
{
    return name;
}
