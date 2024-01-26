//
//  Enemy.hpp
//  rpgax
//
//  Created by Kyle Winfield Burnham on 1/25/24.
//

#ifndef Enemy_hpp
#define Enemy_hpp

#include "Character.hpp"

enum EnemyType {
    goblin, noEnemyType
};

class Enemy : public Character
{
private:
    int variance;
    int floorLevel;
public:
    Enemy(EnemyType type = noEnemyType, int floorLevel = 0); // default enemy is a Floor 0 Goblin
    void varyStats();
};

#endif /* Enemy_hpp */
