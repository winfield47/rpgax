//
//  Utils.cpp
//  rpgax
//
//  Created by Kyle Winfield Burnham on 1/16/24.
//

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
    Player player = createNewPlayer();
    
    
    // display hug (needs to be a function)
    cout << endl;
    cout << "Souls: " << player.getSouls() << endl;
    cout << endl;
    cout << "  " << player.getAsciiArt() << endl;
    cout << "HP : " << player.getHP() << "/" << player.getHPMax() << endl;
    cout << "Weapon : " << player.getWeapon().getName() << " (Grade " << player.getWeapon().getGrade() << ")" << endl;
    cout << "\"" << player.getDescription() << "\"" << endl;
    cout << endl;
    
}

void psuedoClearScreen()
{
    for (size_t i = 0; i < 50; i++)
    {
        cout << "\n";
    }
    cout << endl;
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

Origin getOrigin(string prompt)
{
    while (true)
    {
        string originStr = getLineFromPrompt(prompt);
        
        if (lowercase(originStr) == "brute")
        {
            return brute;
        }
        else if (lowercase(originStr) == "rogue")
        {
            return rogue;
        }
        else if (lowercase(originStr) == "wizard")
        {
            return wizard;
        }
        else if (lowercase(originStr) == "inquisitor")
        {
            return inquisitor;
        }
        else if (lowercase(originStr) == "nomad")
        {
            return nomad;
        }
        else
        {
            cout << "Please enter a valid player origin." << endl;
        }
    }
}

Player createNewPlayer()
{
    // Player choices
    Origin inputOrigin;
    string inputName;
    
    char continueKey;
    do
    {
        psuedoClearScreen();
        // Create the playable character origins for the user to browse
        cout << "Here are the starting origins for your character:\n" << endl;
        
        vector<Player> playerOrigins =
        {
            Player(brute, "Brute"), Player(rogue, "Rogue"), Player(wizard, "Wizard"), Player(inquisitor, "Inquisitor"), Player(nomad, "Nomad")
        };
        
        for (size_t i = 0; i < playerOrigins.size(); i++)
        {
            Player p = playerOrigins.at(i);
            cout << p.getAsciiArt() << " " << p.getDescription() << "\t" << endl << endl;
        }
        
        inputOrigin = getOrigin();
        Player tempPlayerChoice = Player(inputOrigin, "Starting stats:");
        
        psuedoClearScreen();
        cout << "\n\n\n  " << tempPlayerChoice.getAsciiArt() << endl;
        cout << "\"" << tempPlayerChoice.getDescription() << "\"" << endl;
        cout << "HP : " << tempPlayerChoice.getHP() << "/" << tempPlayerChoice.getHPMax() << endl;
        cout << "Weapon : " << tempPlayerChoice.getWeapon().getName();
        cout << " (" << tempPlayerChoice.getWeapon().getDamage() << " " << ((tempPlayerChoice.getWeapon().getDamageType() == physical) ? "physical" : "magic") << " damage)" << endl;
        cout << "Armor : " << tempPlayerChoice.getArmor() << endl;
        cout << "Resistance : " << tempPlayerChoice.getResistance() << endl;
        cout << "STR~" << tempPlayerChoice.getStrength();
        cout << "\tDEX~" << tempPlayerChoice.getDexterity();
        cout << "\tINT~" << tempPlayerChoice.getIntelligence();
        cout << "\tFAI~" << tempPlayerChoice.getFaith();
        cout << "\n\nStarting souls : " << tempPlayerChoice.getSouls() << endl;
        cout << endl;
        
        continueKey = getContinueKey("Are you sure you want to play this class? (y/n): ");
    }
    while (continueKey == 'n');
    inputName = getLineFromPrompt("Name: ");
    
    psuedoClearScreen();
    
    return Player(inputOrigin, inputName);
    
}
