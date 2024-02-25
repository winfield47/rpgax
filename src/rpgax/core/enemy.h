//
//  Enemy.hpp
//  rpgax
//
//  Created by Kyle Winfield Burnham on 1/25/24.
//

#ifndef enemy_h
#define enemy_h

#include "character.h"

enum EnemyType {
    bird, goblin, drow, slime, undead, clergyman, ogre, hallowedarmor, noEnemyType
};

const int TOTAL_ENEMY_TYPES = static_cast<int>(noEnemyType) - 1;

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
    virtual std::string getName() const override;
    EnemyType getType() const;
    WeaponMove getChosenMove();
    int retrieveSoulsHeld();
    
    // Methods
    void chooseNewMove();
};

#endif /* Enemy_hpp */
