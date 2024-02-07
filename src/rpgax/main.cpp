//
//  main.cpp
//  rpgax
//
//  Created by Kyle Winfield Burnham on 1/11/24.
//

#include "core/game.h"

int main(){
    
    srand(static_cast<unsigned int>(time(NULL)));
    clearScreen();
    
    // Initialize the Game
    // Game rpgax = Game(Player(brute, "Winfield")); // Testing
    Game rpgax = Game();
    
    // First stop: camp!
    rpgax.camp();
    
    // Fight Enemies Until Death (reverse pyramid development)
    rpgax.engageInCombat();
    return 0;
}
