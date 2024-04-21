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
    Game rpgax = Game();
    rpgax.play();
    
    return 0;
}
