//
//  main.cpp
//  rpgax
//
//  Created by Kyle Winfield Burnham on 1/11/24.
//

#include "utils/mainloop.h"
using namespace std;

int main(){
    srand(static_cast<unsigned int>(time(NULL)));
    char continueKey = 'y';
    while (continueKey == 'y')
    {
        clearScreen();
        // Initialize the Game
        // Game rpgax = Game(Player(brute, "Winfield"));
        Game rpgax = Game();
        
        // Fight Goblins Until Death (reverse pyramid development)
        while (rpgax.player.getHP() > 0)
        {
            rpgax.engageInCombat();
        }
        continueKey = getContinueKey("\nPlay again? (Y/n): ");
    }
    clearScreen();
    return 0;
}
