//
//  MainLoop.cpp
//  rpgax
//
//  Created by Kyle Winfield Burnham on 1/25/24.
//

#include "MainLoop.hpp"
#include <iostream>

void mainLoop()
{
    Player player = Player(inquisitor, "Winfield");
    // Player player = createNewPlayer();
    Enemy enemyGoblin = Enemy(goblin, 2);
    displayHUD(player, enemyGoblin);
}
