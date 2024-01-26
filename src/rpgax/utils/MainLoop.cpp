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
    // Player player = Player(brute, "Winfield");
    Player player = createNewPlayer();
    Enemy enemyGoblin = Enemy(goblin);
    displayHUD(player, enemyGoblin);
}
