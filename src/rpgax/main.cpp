//
//  main.cpp
//  rpgax
//
//  Created by Kyle Winfield Burnham on 1/11/24.
//

#include "utils/game.h"

int main(){
    
    srand(static_cast<unsigned int>(time(NULL)));
    clearScreen();
    
    // Initialize the Game
    Game rpgax = Game(Player(nomad, "Winfield"));
    //Game rpgax = Game();
    
    // Fight Goblins Until Death (reverse pyramid development)
    while (rpgax.player.getHP() > 0)
    {
        rpgax.engageInCombat();
    }
    
    clearScreen();
    return 0;
}
