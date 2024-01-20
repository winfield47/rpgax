//
//  Utils.cpp
//  rpgax
//
//  Created by Kyle Winfield Burnham on 1/16/24.
//

#include "../core/Player.hpp"
#include "Utils.hpp"
#include <iostream>
using namespace std;

void mainLoop()
{
    char continueKey = 'y';
    while (continueKey == 'y')
    {
        cout << "Welcome to rpgax!" << endl;
        gameLoop();
        continueKey = getContinueKey("Play again? (y/n): ");
    }
}

void gameLoop()
{
    string originStr = getLineFromPrompt("Origin: ");
    
    Player player;
    Origin playerOrigin;
    
    if (originStr == "nomad")
    {
        playerOrigin = nomad;
    }
    else
    {
        cout << "you will play as nomad anyways" << endl;
        playerOrigin = inquisitor;
    }
    
    string playerName = getLineFromPrompt("Name: ");
    
    player = Player(playerOrigin, playerName);
    
    cout << player.getAsciiArt() << endl;
    
}

char getContinueKey(string prompt)
{
    char input;
    bool good;
    
    do {
        cout << prompt;
        cin >> input;
        
        if (cin)
        {
            if (input == 'y' || input == 'n' || input == 'Y' || input == 'N')
            {
                good = true;
            }
            else
            {
                good = false;
                cout << "Please use 'y' or 'n' to answer." << endl;
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else
        {
            good = false;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "That doesn't make sense!" << endl;
        }
    } while (!good);
    
    cout << endl;
    return input;
}

char lowercase(char c)
{
    char lowerChar;
    if (c <= 'Z' && c >= 'A')
    {
        lowerChar = c + ('a' - 'A');
    }
    else
    {
        lowerChar = c;
    }
    return lowerChar;
}

string lowercase(string str)
{
    string lowerStr = "";
    for (char c: str)
    {
        lowerStr += lowercase(c);
    }
    
    return lowerStr;
}

string getLineFromPrompt(string prompt)
{
    string line;
    cout << prompt;
    getline(cin, line);
    if (cin.bad())
    {
        cout << "You broke the code!" << endl;
        return "";
    }
    return line;
}
