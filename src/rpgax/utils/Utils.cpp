//
//  Utils.cpp
//  rpgax
//
//  Created by Kyle Winfield Burnham on 1/16/24.
//

#include "Utils.hpp"
#include <iostream>
#include <iomanip>
using namespace std;

void mainLoop()
{
    Player player = createNewPlayer();
    displayHUD(player);
}

void psuedoClearScreen()
{
    for (size_t i = 0; i < 20; i++)
    {
        cout << "\n";
    }
    cout << endl;
}

char getContinueKey(const string &prompt)
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

char lowercase(const char c)
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

string lowercase(const string &str)
{
    string lowerStr = "";
    for (char c: str)
    {
        lowerStr += lowercase(c);
    }
    
    return lowerStr;
}

string getLineFromPrompt(const string &prompt)
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

bool isSubset(const std::string &stringInQuestion, const std::string &superString) {
    
    bool currentCharIsInSuperString = false;
    for (char subChar : stringInQuestion)
    {
        currentCharIsInSuperString = false;
        for (char superChar : superString)
        {
            if (subChar == superChar)
            {
                currentCharIsInSuperString = true;
                break;
            }
        }
        if (!currentCharIsInSuperString)
        {
            return false;
        }
    }
    
    return true;
}

void displayHUD(const Player &player)
{
    cout << "\n\n\n  " << player.getAsciiArt() << endl;
    cout << "\"" << player.getDescription() << "\"" << endl;
    cout << "STR~" << player.getStrength();
    cout << "\tDEX~" << player.getDexterity();
    cout << "\tINT~" << player.getIntelligence();
    cout << "\tFAI~" << player.getFaith() << endl;
    cout << "\nHP : " << player.getHP() << "/" << player.getHPMax() << endl;
    cout << "Weapon : " << player.getWeapon().getName();
    cout << " (" << player.getWeapon().getDamage() << " " << ((player.getWeapon().getDamageType() == physical) ? "physical" : "magic") << " damage)" << endl;
    cout << "Armor : " << player.getArmor() << endl;
    cout << "Resistance : " << player.getResistance() << endl;
    cout << "\nStarting souls : " << player.getSouls() << endl;
    cout << endl;
}

void displayHUD(const Player &player, const Enemy &enemy)
{
    cout << "
    cout << "\n\n\n  " << player.getAsciiArt() << endl;
    cout << "\"" << player.getDescription() << "\"" << endl;
    cout << "STR~" << player.getStrength();
    cout << "\tDEX~" << player.getDexterity();
    cout << "\tINT~" << player.getIntelligence();
    cout << "\tFAI~" << player.getFaith() << endl;
    cout << "\nHP : " << player.getHP() << "/" << player.getHPMax() << endl;
    cout << "Weapon : " << player.getWeapon().getName();
    cout << " (" << player.getWeapon().getDamage() << " " << ((player.getWeapon().getDamageType() == physical) ? "physical" : "magic") << " damage)" << endl;
    cout << "Armor : " << player.getArmor() << endl;
    cout << "Resistance : " << player.getResistance() << endl;
    cout << "\nStarting souls : " << player.getSouls() << endl;
    cout << endl;
}

Origin getOriginFromPrompt(const string prompt)
{
    while (true)
    {
        string originStr = getLineFromPrompt(prompt);
        
        if (isSubset(originStr, "brute") || originStr == "1")
        {
            return brute;
        }
        else if (isSubset(originStr, "rogue") || originStr == "2")
        {
            return rogue;
        }
        else if (isSubset(originStr, "wizard") || originStr == "3")
        {
            return wizard;
        }
        else if (isSubset(originStr, "inquisitor") || originStr == "4")
        {
            return inquisitor;
        }
        else if (isSubset(originStr, "nomad") || originStr == "5")
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
        
        inputOrigin = getOriginFromPrompt();
        string originDescription = "";
        switch (inputOrigin)
        {
            case brute:
                originDescription = "A strong warrior who can take a hit or two.";
                break;
            case rogue:
                originDescription = "A quick skirmisher that likes to strike first.";
                break;
            case wizard:
                originDescription = "A weak mage with hopes of powerful magic.";
                break;
            case inquisitor:
                originDescription = "A vessel for a higher power's will.";
                break;
            default:
            case nomad:
                originDescription = "An exiled wanderer from a long-forgotten land.";
                break;
        }
        Player tempPlayerChoice = Player(inputOrigin, originDescription);
        
        psuedoClearScreen();
        //
        // vvv DISPLAY ORIGIN vvv
        //
        cout << "\n\n\n  " << tempPlayerChoice.getAsciiArt() << endl;
        cout << "\"" << tempPlayerChoice.getDescription() << "\"" << endl;
        cout << "STR~" << tempPlayerChoice.getStrength();
        cout << "\tDEX~" << tempPlayerChoice.getDexterity();
        cout << "\tINT~" << tempPlayerChoice.getIntelligence();
        cout << "\tFAI~" << tempPlayerChoice.getFaith() << endl;
        cout << "\nHP : " << tempPlayerChoice.getHP() << "/" << tempPlayerChoice.getHPMax() << endl;
        cout << "Weapon : " << tempPlayerChoice.getWeapon().getName();
        cout << " (" << tempPlayerChoice.getWeapon().getDamage() << " " << ((tempPlayerChoice.getWeapon().getDamageType() == physical) ? "physical" : "magic") << " damage)" << endl;
        cout << "Armor : " << tempPlayerChoice.getArmor() << endl;
        cout << "Resistance : " << tempPlayerChoice.getResistance() << endl;
        cout << "\nStarting souls : " << tempPlayerChoice.getSouls() << endl;
        cout << endl;
        //
        // ^^^ DISPLAY ORIGIN ^^^
        //
        
        continueKey = getContinueKey("Do you want to play this class? (y/n): ");
    }
    while (continueKey == 'n');
    inputName = getLineFromPrompt("Name: ");
    
    psuedoClearScreen();
    
    return Player(inputOrigin, inputName);
    
}
