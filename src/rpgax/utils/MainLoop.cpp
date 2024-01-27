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
    // Player player = Player(inquisitor, "Winfield");
    Player player = createNewPlayer();
    Enemy enemyGoblin = Enemy(goblin);
    
    cout << player.getWeapon().getPlayerIntelligenceModifier() << endl;
    
    // Fight Goblins Until Death
    string input = "";
    short chosenMoveIndex = -1;
    cout << chosenMoveIndex << endl;
    while (player.getHP() > 0)
    {
        input = "";
        chosenMoveIndex = -1;
        displayHUD(player, enemyGoblin);
        do
        {
            input = getLineFromPrompt("Select a move from <" + player.getWeapon().getName() + ">: ");
            for (short i = 0; i < player.getWeapon().getMoves().size(); i++)
            {
                if (isSubset(input, player.getWeapon().getMoves().at(i).getName()))
                {
                    chosenMoveIndex = i;
                    break;
                }
            }
            if (chosenMoveIndex < 0)
            {
                cout << "Please enter a valid move." << endl;
            }
        }
        while (chosenMoveIndex < 0);
        cout << "You chose: " << player.getWeapon().getMoves().at(chosenMoveIndex).getName() << "!" << endl;
        input = getLineFromPrompt("Pause... ");
    }
}
