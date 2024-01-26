//
//  Enemy.cpp
//  rpgax
//
//  Created by Kyle Winfield Burnham on 1/25/24.
//

#include "Enemy.hpp"
using namespace std;

Enemy::Enemy(EnemyType type, int floorLevel)
{
    this->floorLevel = floorLevel;
    switch (type)
    {
        default:
            variance = 0;
            asciiArt = "\\ø/";
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
            variance = 3;
            asciiArt = "\\g/";
            description = "A goblin trying to rob you of your life!";
            weapon = Weapon(dagger, floorLevel);
            strength = 64;
            dexterity = 74;
            intelligence = 65;
            faith = 75;
            armor = 0;
            resistance = 0;
            break;
    }
    varyStats();
    
    hpMax = hp = 20 + (floorLevel * 1.5) + (strength - 70) * 2;
}

void Enemy::varyStats()
{
    strength += (rand() % variance) - (rand() % variance);
    dexterity += (rand() % variance) - (rand() % variance);
    intelligence += (rand() % variance) - (rand() % variance);
    faith += (rand() % variance) - (rand() % variance);
    armor += ((rand() % floorLevel) - rand() % floorLevel) <= 0 ? 0 : (rand() % floorLevel);
    resistance += (rand() % floorLevel) <= 0 ? 0 : (rand() % floorLevel);
}
