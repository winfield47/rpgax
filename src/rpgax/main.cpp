//
//  main.cpp
//  rpgax
//
//  Created by Kyle Winfield Burnham on 1/11/24.
//

#include <iostream>
#include "utils/MainLoop.hpp"
using namespace std;

int main()
{
    srand(static_cast<unsigned int>(time(NULL)));
    char continueKey = 'y';
    while (continueKey == 'y')
    {
        cout << "Welcome to rpgax!" << endl;
        mainLoop();
        continueKey = getContinueKey("Play again? (y/n): ");
    }
    return 0;
}
