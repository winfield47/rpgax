//
//  MainLoop.cpp
//  rpgax
//
//  Created by Kyle Winfield Burnham on 1/25/24.
//

#include "MainLoop.hpp"
#include <iostream>
using namespace std;

void mainLoop(){
    
    // Initialize the Game
    // Game rpgax = Game(Player(nomad, "Winfield"), Enemy(goblin));
    Game rpgax = Game();
    
    // Fight Goblins Until Death (reverse pyramid development)
    while (rpgax.player.getHP() > 0)
    {
        rpgax.engageInCombat();
    }
}
