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
    // Game rpgax = Game(Player(wizard, "Winfield")); // Testing
    Game rpgax = Game();
    
    // Fight Enemies Until Death (reverse pyramid development)
    while (rpgax.player.getHP() > 0)
    {
        rpgax.engageInCombat();
    }
    return 0;
}
