//
//  Enemy.hpp
//  rpgax
//
//  Created by Kyle Winfield Burnham on 1/25/24.
//

#ifndef enemy_h
#define enemy_h

#include "character.h"

const int TOTAL_ENEMY_TYPES = 2;

enum EnemyType {
    pigeon, goblin, drow, slime, noEnemyType
};

class Enemy : public Character
{
private:
    // Properties
    std::string name;
    EnemyType type;
    int floorLevel;
    int variance;
    size_t chosenMoveIndex;
    WeaponMove chosenMove;
public:
    // Constructors
    Enemy();
    Enemy(EnemyType type, int floorLevel = 0); // default enemy should be a Floor 0 Goblin
    void varyStats();
    
    // Accessors
    std::string getName() const;
    EnemyType getType() const;
    WeaponMove getChosenMove();
    int retrieveSoulsHeld();
    
    // Methods
    void chooseMove();
};

#endif /* Enemy_hpp */
