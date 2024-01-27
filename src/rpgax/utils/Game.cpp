//
//  Game.cpp
//  rpgax
//
//  Created by Kyle Winfield Burnham on 1/27/24.
//

#include "Game.hpp"
#include <iostream>
#include <iomanip>
using namespace std;

// Static Properties
string Game::input = "";
Player Game::player = Player();
Enemy Game::enemy = Enemy();
short Game::floor = 0;
bool Game::playerGoesFirst = true;

// Constructors
Game::Game(){
    createNewPlayer();
    enemy = Enemy(goblin);
}
Game::Game(Player player, Enemy enemy){
    this->player = player;
    this->enemy = enemy;
}

// User Input
void Game::getSmartInput(const string &prompt){
    string smartInput = lowercase(getFirstWord(getLineFromPrompt(prompt)));
    if (prompt != "Continue…")
    {
        input = smartInput;
    }
}
void Game::createNewPlayer(){
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
                originDescription = "Brute… A strong warrior who can take a hit or two… or three!";
                break;
            case rogue:
                originDescription = "Rogue… A quick skirmisher that likes to strike first.";
                break;
            case wizard:
                originDescription = "Wizard… A weak mage with hopes of powerful magic.";
                break;
            case inquisitor:
                originDescription = "Inquisitor… A vessel for a higher power's will.";
                break;
            default:
            case nomad:
                originDescription = "Nomad… An exiled wanderer from a long-forgotten land.";
                break;
        }
        Player tempPlayerChoice = Player(inputOrigin, originDescription);
        
        psuedoClearScreen();\
        displayHUD(tempPlayerChoice);
        
        continueKey = getContinueKey("Do you want to play this class? (y/n): ");
    }
    while (continueKey == 'n');
    inputName = getLineFromPrompt("Name: ");
    
    psuedoClearScreen();
    
    player = Player(inputOrigin, inputName);
    
}
Origin Game::getOriginFromPrompt(const string prompt){
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

// Property-to-String Converters
string Game::getStringHpAmrRes(const Character &character){
    string str = "HP~" + to_string(character.getHP()) + "/" + to_string(character.getHPMax());
    str += character.getArmor() == 0 ? "" : ", AMR~" + to_string(character.getArmor());
    str += character.getResistance() == 0 ? "" : ", RES~" + to_string(character.getResistance());
    return str;
}
string Game::getStringAttributes(const Character &character){
    string str = "STR~" + to_string(character.getStrength());
    str += ", DEX~" + to_string(character.getDexterity());
    str += ", INT~" + to_string(character.getIntelligence());
    str += ", FAI~" + to_string(character.getFaith());
    return str;
}
string Game::getStringForAttributeEnum(const int attrEnumIntValue){
    switch (attrEnumIntValue) {
        case 0:
            return "STR";
            break;
        case 1:
            return "DEX";
            break;
        case 2:
            return "INT";
            break;
        case 3:
            return "FAI";
            break;
        default:
            return "";
            break;
    }
}
string Game::getStringForAmountOfChecks(const int amountOfChecks){
    string str = "";
    if (amountOfChecks > 0)
    {
        for (short i = 0; i < amountOfChecks - 1; i++)
        {
            str += "[]~";
        }
        str += "[]";
    }
    return str;
}
string Game::getStringForWeaponDamageType(const int type, const bool displayPhysical){
    switch (type)
    {
        case 0:
            if (displayPhysical)
            {
                return "physical";
            }
            else
            {
                return "";
            }
            break;
        case 1:
            if (displayPhysical)
            {
                return "magic";
            }
            else
            {
                return " magic";
            }
            break;
        default:
            return "";
            break;
    }
}

// Display
void Game::displayHUD(const Player &player){
    cout << "Souls : " << player.getSouls() << endl;
    cout << "Potion : " + player.getPotion().name << "\n" << endl;
    cout << "  " << player.getAsciiArt() <<endl;
    cout << "\"" << player.getDescription() << "\"" << endl;
    cout << "STR~" << player.getStrength();
    cout << "\tDEX~" << player.getDexterity();
    cout << "\tINT~" << player.getIntelligence();
    cout << "\tFAI~" << player.getFaith() << endl;
    cout << "\nHP: " << player.getHP() << "/" << player.getHPMax() << endl;
    cout << "Weapon: " << player.getWeapon().getName();
    cout << " (" << player.getWeapon().getDamage() << " " << ((player.getWeapon().getDamageType() == physical) ? "physical" : "magic") << " damage)" << endl;
    if (player.getArmor() != 0)
    {
        cout << "Armor: " << player.getArmor() << endl;
    }
    if (player.getResistance() != 0)
    {
        cout << "Resistance: " << player.getResistance() << endl;
    }
    cout << endl;
}
void Game::displayHUD(const Player &player, const Enemy &enemy){

    // Clear the screen
    psuedoClearScreen();
    
    // Display Souls
    cout << "Souls  : " + to_string(player.getSouls()) << endl;
    
    // Display Potion
    cout << "Potion : " + player.getPotion().name << endl;
    
    // Display Floor
    cout << floor << "F" << endl;
    
    // Spacing
    cout << endl;
    
    // Display ASCII ART
    printWithFormattingHUD("  " + player.getAsciiArt(), "  " + enemy.getAsciiArt(), addPipes);
    
    // Display DESCRIPTION
    string playerDescriptionDisplayStr = "\"" + player.getDescription() + "\"";
    string enemyDescriptionDisplayStr = "\"" + enemy.getDescription() + "\"";
    printWithFormattingHUD("\"" + player.getDescription() + "\"", "\"" + enemy.getDescription() + "\"", addVersus);
    
    // Display HP, WPN, AMR, RES
    printWithFormattingHUD(getStringHpAmrRes(player), getStringHpAmrRes(enemy), addPipes);
    
    // Display PLAYER ATTRIBUTES and TURN INFORMATION
    string turnInfo = "";
    determineWhoGoesFirst();
    if (playerGoesFirst)
    {
        turnInfo = player.getName();
    }
    else
    {
        turnInfo = enemy.getName();
    }
    turnInfo += " acted first!";
    printWithFormattingHUD(getStringAttributes(player), turnInfo, addPipes);
    
    // Display WEAPONS and MOVES
    printWithFormattingHUD("\n<" + player.getWeapon().getName() + ">", "<" + enemy.getWeapon().getName() + ">");
    printMovesWithFormattingHUD(player.getWeapon(), enemy);
}
void Game::printWithFormattingHUD(const string &leftString, const string &rightString, const OptionSelectHUD optionSelectHUD){
    const int TOTAL_WIDTH = 40;
    cout << setw(TOTAL_WIDTH) << left << leftString;
    switch (optionSelectHUD) {
        case addPipes:
            cout << right << setw(2) << "|" << setw(10) << "| ";
            break;
            
        case addVersus:
            cout << " | VERSUS | ";
            break;
            
        default:
        case addNothing:
            cout << setw(13) << "";
            break;
    }
    cout << setw(TOTAL_WIDTH) << left << rightString << endl;
}
void Game::printMovesWithFormattingHUD(const Weapon &playerWeapon, const Enemy &enemy){
    string leftString;
    string rightString;
    WeaponMove currentMove;
    int currentMoveDamage;
    for (size_t i = 0; i < playerWeapon.getMoves().size(); i++)
    {
        // Set both to nothing
        leftString = rightString = "";
        
        // Player's current move
        currentMove = playerWeapon.getMoves().at(i);
        currentMoveDamage = static_cast<int>(playerWeapon.getDamage() * currentMove.getDamagePercentage());
        
        // Creating the display string
        leftString = " " + playerWeapon.getMoves().at(i).getName() + ": ";
        if (currentMove.getName() != "Heal")
        {
            if (currentMoveDamage != 0)
            {
                leftString += to_string(currentMoveDamage);
                leftString += getStringForWeaponDamageType(playerWeapon.getDamageType()) + " dmg";
                if (currentMove.getAmountOfChecks() != 0)
                {
                    leftString += ", ";
                }
            }
            if (currentMove.getAmountOfChecks() != 0)
            {
                leftString += getStringForAmountOfChecks(playerWeapon.getMoves().at(i).getAmountOfChecks());
                leftString += " " + getStringForAttributeEnum(playerWeapon.getMoves().at(i).getUsedAttribute());
            }
        }
        else
        {
            leftString += to_string(playerWeapon.getPlayerFaithModifier()) + " HP";
        }
        
        // Enemy's NEXT INTENT MOVE display
        if (i == 0)
        {
            WeaponMove chosenMove = enemy.getWeapon().getMoves().at(enemy.getMoveChooser());
            int chosenMoveDamage = enemy.getWeapon().getDamage(chosenMove);
            rightString = chosenMove.getName() + ": ";
            if (chosenMoveDamage != 0)
            {
                rightString += to_string(static_cast<int>(chosenMoveDamage));
                rightString += getStringForWeaponDamageType(enemy.getWeapon().getDamageType()) + " dmg";
                if (chosenMove.getAmountOfChecks() != 0)
                {
                    rightString += ", ";
                }
            }
            if (chosenMove.getAmountOfChecks() != 0)
            {
                rightString += getStringForAmountOfChecks(chosenMove.getAmountOfChecks());
                rightString += " " + getStringForAttributeEnum(chosenMove.getUsedAttribute());
            }
        }
        printWithFormattingHUD(leftString, rightString);
    }
}

// Combat
void Game::engageInCombat(){
    while (player.getHP() > 0)
    {
        determineWhoGoesFirst();
        if (playerGoesFirst)
        {
            performPlayerMove();
            performEnemyMove();
        }
        else
        {
            performEnemyMove();
            performPlayerMove();
        }
    }
}
void Game::performPlayerMove(){
    char continueKey = ' ';
    short chosenMoveIndex = -1;
    input = "";
    chosenMoveIndex = -1;
    do
    {
        displayHUD(player, enemy);
        cout << endl;
        getSmartInput("Select a move from <" + player.getWeapon().getName() + ">: ");
        for (short i = 0; i < player.getWeapon().getMoves().size(); i++)
        {
            if (isSubset(input, lowercase(player.getWeapon().getMoves().at(i).getName())))
            {
                chosenMoveIndex = i;
                break;
            }
        }
        if (chosenMoveIndex < 0)
        {
            if (isSubset(input, "potion"))
            {
                if (player.getPotion().name != "None")
                {
                    // Confirm drinking potion
                    continueKey = getContinueKey("Drink healing potion? (y/n): ");
                    if (continueKey == 'y')
                    {
                        cout << player.getName() << " drank the " << lowercase(player.getPotion().name) << " potion!" << endl;
                        cout << player.getName() << " healed " << player.heal(player.popPotion().grade) << " HP" << endl;
                        getSmartInput("Continue…");
                    }
                }
                else
                {
                    cout << "No potions…" << endl;
                    getSmartInput("Continue…");
                }
            }
            else
            {
                cout << "Please enter a valid move." << endl;
                getSmartInput("Continue…");
            }
        }
    }
    while (chosenMoveIndex < 0);
    WeaponMove chosenMove = player.getWeapon().getMoves().at(chosenMoveIndex);
    // Confirm weapon move
    continueKey = getContinueKey("Use " + chosenMove.getName() + "? (y/n): ");
    if (continueKey == 'y')
    {
        cout << player.getName() << " performed: " << chosenMove.getName() << "!" << endl;
        cout << player.getName() << " dealt " << player.getWeapon().getDamage(chosenMove) << ((player.getWeapon().getDamageType() == magic) ? " magic" : "") << " dmg" << endl;
        if (chosenMove.getDamagePercentage() != 0)
        {
            enemy.takeDamage(player.getWeapon().getDamage(chosenMove));
            if (enemy.getHP() == 0)
            {
                cout << "You defeated the goblin… but here comes another one!" << endl;
                enemy = Enemy(goblin, ++floor);
            }
        }
        getSmartInput("Continue...");
    }
}
void Game::performEnemyMove(){
    
    // Display HUD
    displayHUD(player, enemy);
    
    // What the enemy move choice is
    WeaponMove chosenMove = enemy.getWeapon().getMoves().at(enemy.getMoveChooser());
    int chosenMoveDamage = enemy.getWeapon().getDamage(chosenMove);
    
    // Deal damage
    player.takeDamage(chosenMoveDamage);
    
    // Display damage taken
    cout << "\n" << enemy.getName() << " dealt " << chosenMoveDamage << (enemy.getWeapon().getDamageType() == magic ? " magic" : "") << " dmg" << endl;
    getSmartInput("Continue…");
}
void Game::determineWhoGoesFirst(){
    if (player.getDexterity() > enemy.getDexterity())
    {
        playerGoesFirst = true;
    }
    else if (player.getDexterity() < enemy.getDexterity())
    {
        playerGoesFirst = false;
    }
    else
    {
        if (enemy.getMoveChooser() % 2 == 0)
        {
            playerGoesFirst = false;
        }
        else
        {
            playerGoesFirst = true;
        }
    }
}
