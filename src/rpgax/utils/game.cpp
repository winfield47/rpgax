//
//  Game.cpp
//  rpgax
//
//  Created by Kyle Winfield Burnham on 1/27/24.
//

#include "game.h"
#include <iostream>
#include <iomanip>

// Static Properties
std::string Game::input = "";
Player Game::player = Player();
Enemy Game::enemy = Enemy();
short Game::floor = 0;
bool Game::playerGoesFirst = true;
bool Game::playerIsPrinted = false;
bool Game::enemyIsPrinted = false;
PrintSpeed Game::playerPrintSpeed = normal;
PrintSpeed Game::universalPrintSpeed = normal;

// Constructors
Game::Game(){
    createNewPlayer();
    createNewEnemy();
}
Game::Game(const Player &player){
    this->player = player;
    createNewEnemy();
}
Game::Game(const Player &player, const Enemy &enemy){
    this->player = player;
    this->enemy = enemy;
}

// User Input
void Game::getSmartInput(const std::string &prompt){
    std::string smartInput = lowercase(getFirstWord(getLineFromPrompt(prompt)));
    if (smartInput == "")
    {
        if (prompt != "Continue...")
        {
            // Make the input always fail a check for anything
            input = "\1";
            return;
        }
    }
    input = smartInput;
}
void Game::createNewPlayer(){
    
    // Intro text
    const std::string introduction = "Here are the starting origins for your character:\n\n";
    
    // Player choices
    Origin inputOrigin;
    std::string inputName;
    
    char continueKey;
    bool hasDisplayedOriginsOnce = false;
    do
    {
        clearScreen();
        // Create the playable character origins for the user to browse
        printCharByChar(introduction, fast);

        std::vector<Player> playerOrigins =
        {
            Player(brute, "Brute"), Player(rogue, "Rogue"), Player(wizard, "Wizard"), Player(inquisitor, "Inquisitor"), Player(nomad, "Nomad")
        };
        
        for (size_t i = 0; i < playerOrigins.size(); i++)
        {
            Player p = playerOrigins.at(i);
            if (hasDisplayedOriginsOnce)
            {
                printCharByChar(p.getAsciiArt() + " " + p.getDescription(), fast);
            }
            else
            {
                printCharByChar(p.getAsciiArt() + " " + p.getDescription());
            }
            std::cout << "\t\n" << std::endl;
        }
        
        inputOrigin = getOriginFromPrompt();
        std::string originDescription = "";
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
        
        clearScreen();
        displayHUD(tempPlayerChoice);
        
        continueKey = getContinueKey("Do you want to play the " + getStringForOrigin(tempPlayerChoice.getOrigin()) + "? (Y/n): ");
        hasDisplayedOriginsOnce = true;
    }
    while (continueKey == 'n');
    inputName = getLineFromPrompt("Name: ");
    
    clearScreen();
    
    player = Player(inputOrigin, inputName);
    
}
Origin Game::getOriginFromPrompt(const std::string prompt){
    while (true)
    {
        pause();
        getSmartInput(prompt);
        
        if (isSubset(input, "brute") || input == "1")
        {
            return brute;
        }
        else if (isSubset(input, "rogue") || input == "2")
        {
            return rogue;
        }
        else if (isSubset(input, "wizard") || input == "3")
        {
            return wizard;
        }
        else if (isSubset(input, "inquisitor") || input == "4")
        {
            return inquisitor;
        }
        else if (isSubset(input, "nomad") || input == "5")
        {
            return nomad;
        }
        else
        {
            printCharByChar("Please enter a valid player origin.\n");
        }
    }
}

// Property-to-String Converters
std::string Game::getStringHpAmrRes(const Character &character){
    std::string str = "HP~" + std::to_string(character.getHP()) + "/" + std::to_string(character.getHPMax());
    str += character.getArmor() == 0 ? "" : ", AMR~" + std::to_string(character.getArmor());
    str += character.getResistance() == 0 ? "" : ", RES~" + std::to_string(character.getResistance());
    return str;
}
std::string Game::getStringAttributes(const Character &character){
    std::string str = "STR~" + std::to_string(character.getStrength());
    str += ", DEX~" + std::to_string(character.getDexterity());
    str += ", INT~" + std::to_string(character.getIntelligence());
    str += ", FAI~" + std::to_string(character.getFaith());
    return str;
}
std::string Game::getStringForAttributeEnum(const int attrEnumIntValue){
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
std::string Game::getStringForAmountOfChecks(const int amountOfChecks){
    std::string str = "";
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
std::string Game::getStringForWeaponDamageType(const int type, const bool displayPhysical){
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
std::string Game::getStringForOrigin(const Origin origin){
    switch (origin) {
        default:
        case brute:
            return "Brute";
        case rogue:
            return "Rogue";
        case wizard:
            return "Wizard";
        case inquisitor:
            return "Inquisitor";
        case nomad:
            return "Nomad";
    }
}

// Display
void Game::displayHUD(const Player &player){
    std::cout << "Souls  : ";
    pause();
    printCharByChar(std::to_string(player.getSouls()) + "\n");
    std::cout << "Potion : ";
    pause();
    printCharByChar(player.getPotion().name + "\n\n");
    pause();
    printCharByChar("  " + player.getAsciiArt() + "\n");
    printCharByChar("\"" + player.getDescription() + "\"\n");
    std::cout << "STR~";
    printCharByChar(std::to_string(player.getStrength()));
    std::cout << "\tDEX~";
    printCharByChar(std::to_string(player.getDexterity()));
    std::cout << "\tINT~";
    printCharByChar(std::to_string(player.getIntelligence()));
    std::cout << "\tFAI~";
    printCharByChar(std::to_string(player.getFaith()));
    std::cout << std::endl;
    std::cout << "\nHP: ";
    pause();
    printCharByChar(std::to_string(player.getHP()) + "/" + std::to_string(player.getHPMax()) + "\n");
    std::cout << "Weapon: ";
    pause();
    printCharByChar(player.getWeapon().getName());
    printCharByChar(" (" + std::to_string(player.getWeapon().getDamage()) + " " + ((player.getWeapon().getDamageType() == physical) ? "physical" : "magic") + " damage)\n");
    if (player.getArmor() != 0)
    {
        std::cout << "Armor: ";
        pause();
        printCharByChar(std::to_string(player.getArmor()) + "\n");
    }
    if (player.getResistance() != 0)
    {
        std::cout << "Resistance: ";
        pause();
        printCharByChar(std::to_string(player.getResistance()) + "\n");
    }
    std::cout << std::endl;
}
void Game::displayHUD(const Player &player, const Enemy &enemy){

    // Clear the screen
    clearScreen();
    
    // Govern Print Speed
    if (enemyIsPrinted)
    {
        // Change Print Speed
        universalPrintSpeed = instant;
        playerPrintSpeed = instant;
        // Display Floor
        printCharByChar("Floor    : ", universalPrintSpeed);
        printCharByChar(std::to_string(floor), universalPrintSpeed);
        
        // Display Souls
        printCharByChar("\nSouls    : " + std::to_string(player.getSouls()), playerPrintSpeed);
    }
    else
    {
        // Change Print Speed
        universalPrintSpeed = normal;
        // Display Floor
        pause();
        printCharByChar("Floor    : ");
        pause();
        printCharByChar(std::to_string(floor));
        pause();
        
        // Display Souls
        printCharByChar("\nSouls    : ");
        pause();
        printCharByChar(std::to_string(player.getSouls()));
        pause();
    }
    // Display Potion
    printCharByChar("\n<Potion> : " + player.getPotion().name + "\n", playerPrintSpeed);
    
    // Spacing
    std::cout << std::endl;
    
    // Display ASCII ART
    printWithFormattingHUD("  " + player.getAsciiArt(), "  " + enemy.getAsciiArt(), addPipes);
    
    // Display DESCRIPTION
    std::string playerDescriptionDisplayStr = "\"" + player.getDescription() + "\"";
    std::string enemyDescriptionDisplayStr = "\"" + enemy.getDescription() + "\"";
    printWithFormattingHUD("\"" + player.getDescription() + "\"", "\"" + enemy.getDescription() + "\"", addVersus);
    
    // Display HP, WPN, AMR, RES
    printWithFormattingHUD(" " + getStringHpAmrRes(player), " " + getStringHpAmrRes(enemy), addPipes);
    
    // Display PLAYER ATTRIBUTES and TURN INFORMATION
    std::string turnInfo = " ";
    determineWhoGoesFirst();
    turnInfo += enemy.getName();
    if (playerGoesFirst)
    {
        turnInfo += " is slower than you…";
    }
    else
    {
        turnInfo += " is faster than you!";
    }
    printWithFormattingHUD(" " + getStringAttributes(player), turnInfo, addPipes);
    
    // Display WEAPONS and MOVES
    printWithFormattingHUD("\n-" + player.getWeapon().getName() + ":", "-" + enemy.getWeapon().getName() + ":");
    printMovesWithFormattingHUD(player.getWeapon(), enemy);
    enemyIsPrinted = true;
}
void Game::printWithFormattingHUD(const std::string &leftString, const std::string &rightString, const OptionSelectHUD optionSelectHUD){
    const int TOTAL_WIDTH = 40;
    unsigned int lengthOfLeftString = printCharByChar(leftString, playerPrintSpeed);
    std::cout << std::setw(TOTAL_WIDTH - lengthOfLeftString) << std::left << "";
    switch (optionSelectHUD) {
        case addPipes:
            printCharByChar(" |        | ", playerPrintSpeed);
            break;
            
        case addVersus:
            printCharByChar(" | VERSUS | ", playerPrintSpeed);
            break;
            
        default:
        case addNothing:
            std::cout << std::setw(13) << "";
            break;
    }
    if (!enemyIsPrinted)
    {
        if (isSubset("is than you!", rightString))
        {
            pause();
            printCharByChar(rightString, slow);
            pause();
        }
        else
        {
            printCharByChar(rightString, universalPrintSpeed);
        }
    }
    else
    {
        printCharByChar(rightString, universalPrintSpeed);
    }
    std::cout << std::endl;
}
void Game::printMovesWithFormattingHUD(const Weapon &playerWeapon, const Enemy &enemy){
    std::string leftString;
    std::string rightString;
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
        leftString = " <" + playerWeapon.getMoves().at(i).getName() + "> ";
        if (currentMove.getName() != "Heal")
        {
            if (currentMoveDamage != 0)
            {
                leftString += std::to_string(currentMoveDamage);
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
            leftString += std::to_string(playerWeapon.getPlayerFaithModifier()) + " HP";
        }
        
        // Enemy's NEXT INTENT MOVE display
        if (i == 0)
        {
            WeaponMove chosenMove = this->enemy.getChosenMove();
            int chosenMoveDamage = enemy.getWeapon().getDamage(chosenMove);
            rightString = " " + chosenMove.getName() + ", ";
            if (chosenMoveDamage != 0)
            {
                rightString += std::to_string(static_cast<int>(chosenMoveDamage));
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
            if (enemy.getHP() <= 0)
            {
                enemyDeathCleanUp();
            }
            else
            {
                performEnemyMove();
            }
        }
        else
        {
            performEnemyMove();
            if (player.getHP() > 0)
            {
                performPlayerMove();
            }
            if (enemy.getHP() <= 0)
            {
                enemyDeathCleanUp();
            }
        }
        if (player.getHP() <= 0)
        {
            printCharByChar("\n\nYou died...", slow);
            getSmartInput("");
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
        std::cout << std::endl;
        getSmartInput("Select a <Move>: ");
        for (short i = 0; i < player.getWeapon().getMoves().size(); i++)
        {
            // Find/assume which move the player selected
            if (isSubset(input, lowercase(player.getWeapon().getMoves().at(i).getName())))
            {
                chosenMoveIndex = i;
                break;
            }
            else if (isInt(input))
            {
                if (charToInt(input[0]) == i + 1)
                {
                    chosenMoveIndex = i;
                    break;
                }
            }
        }
        if (chosenMoveIndex < 0)
        {
            if (isSubset(input, "potion"))
            {
                if (player.getPotion().name != "None")
                {
                    // Confirm drinking potion
                    continueKey = getContinueKey("Drink healing potion? (Y/n): ");
                    if (continueKey == 'y')
                    {
                        printCharByChar(player.getName() + " drank the " + lowercase(player.getPotion().name) + " potion!");
                        pause();
                        printCharByChar("\n" + player.getName() + " healed " + std::to_string(player.heal(player.popPotion().grade)) + " HP");
                        pause();
                        std::cout << std::endl;
                    }
                }
                else
                {
                    printCharByChar("No potions…");
                    pause();
                    std::cout << std::endl;
                }
            }
            else
            {
                printCharByChar("Please enter a valid move.\n");
            }
            getSmartInput();
        }
        if (chosenMoveIndex >= 0)
        {
            WeaponMove chosenMove = player.getWeapon().getMoves().at(chosenMoveIndex);
            // Confirm weapon move
            continueKey = getContinueKey("Use " + chosenMove.getName() + "? (Y/n): ");
            if (continueKey == 'y')
            {
                printCharByChar(player.getName() + " dealt " + std::to_string(player.getWeapon().getDamage(chosenMove)) + ((player.getWeapon().getDamageType() == magic) ? " magic" : "") + " dmg");
                pause();
                std::cout << std::endl;
                if (chosenMove.getDamagePercentage() != 0)
                {
                    enemy.takeDamage(player.getWeapon().getDamage(chosenMove));
                }
                getSmartInput();
            }
            else
            {
                // PLAYER DID NOT WANT TO USE THAT MOVE
                chosenMoveIndex = -1;
            }
        }
    }
    while (chosenMoveIndex < 0);
}
void Game::performEnemyMove(){
    
    // Display HUD
    displayHUD(player, enemy);
    
    // What the enemy move choice is
    WeaponMove chosenMove = enemy.getChosenMove();
    enemy.chooseMove();
    int chosenMoveDamage = enemy.getWeapon().getDamage(chosenMove);
    
    // Deal damage
    player.takeDamage(chosenMoveDamage);
    
    // Display damage taken
    pause();
    printCharByChar("\n" + enemy.getName() + " dealt " + std::to_string(chosenMoveDamage) + (enemy.getWeapon().getDamageType() == magic ? " magic" : "") + " dmg");
    pause();
    std::cout << std::endl;
    getSmartInput();
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
        if ((enemy.getChosenMove().getAmountOfChecks() + enemy.getHP() + player.getSouls() + floor) % 2 == 0)
        {
            playerGoesFirst = false;
        }
        else
        {
            playerGoesFirst = true;
        }
    }
}
void Game::enemyDeathCleanUp(){
    pause();
    displayHUD(player, enemy);
    printCharByChar("\nYou defeated " + enemy.getName() + ".");
    pause();
    int soulsHarvested = enemy.retrieveSoulsHeld();
    printCharByChar("\nYou harvested " + std::to_string(enemy.retrieveSoulsHeld()) + " soul");
    if (soulsHarvested != 1)
    {
        printCharByChar("s");
    }
    printCharByChar("!");
    player.addSouls(soulsHarvested);
    pause();
    printCharByChar("\nIn the next floor you see... ");
    pause();
    floor++;
    createNewEnemy();
    printCharByChar(enemy.getName() + "...");
    pause();
    std::cout << std::endl << std::endl;
    getSmartInput();
}
void Game::createNewEnemy(){
    EnemyType newEnemyType = static_cast<EnemyType>(rand() % ((floor < TOTAL_ENEMY_TYPES ? floor : TOTAL_ENEMY_TYPES) + 1));
    enemy = Enemy(newEnemyType, floor);
    enemyIsPrinted = false;
    if (playerPrintSpeed == instant)
    {
        playerPrintSpeed = fast;
    }
}
