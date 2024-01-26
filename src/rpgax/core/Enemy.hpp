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
    goblin, slime, noEnemyType
};

class Enemy : public Character
{
private:
    // Properties
    int floorLevel;
    int variance;
    size_t moveChooser;
public:
    // Constructors
    Enemy();
    Enemy(EnemyType type, int floorLevel = 0); // default enemy should be a Floor 0 Goblin
    void varyStats();
    
    // Accessors
    size_t getMoveChooser() const;
};

#endif /* Enemy_hpp */
