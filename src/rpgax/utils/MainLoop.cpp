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
    Game game = Game(Player(wizard, "Winfield"), Enemy(goblin));
    
    // Fight Goblins Until Death (reverse pyramid development)
    game.engageInCombat();
    
}
