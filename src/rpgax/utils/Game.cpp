//
//  Game.cpp
//  rpgax
//
//  Created by Kyle Winfield Burnham on 1/27/24.
//

#include "Game.hpp"
#include <iostream>
#include <iomanip>

// Static Properties
std::string Game::input = "";
Player Game::player = Player();
Enemy Game::enemy = Enemy();
short Game::floor = 0;
bool Game::playerGoesFirst = true;

// Constructors
Game::Game(){
    createNewPlayer();
    createNewEnemy();
}
Game::Game(Player player, Enemy enemy){
    this->player = player;
    this->enemy = enemy;
}

// User Input
void Game::getSmartInput(const std::string &prompt){
    std::string smartInput = lowercase(getFirstWord(getLineFromPrompt(prompt)));
    if (prompt != "Continue…")
    {
        input = smartInput;
    }
}
void Game::createNewPlayer(){
    // Player choices
    Origin inputOrigin;
    std::string inputName;
    
    char continueKey;
    do
    {
        clearScreen();
        // Create the playable character origins for the user to browse
        std::cout << "Here are the starting origins for your character:\n" << std::endl;
        
        std::vector<Player> playerOrigins =
        {
            Player(brute, "Brute"), Player(rogue, "Rogue"), Player(wizard, "Wizard"), Player(inquisitor, "Inquisitor"), Player(nomad, "Nomad")
        };
        
        for (size_t i = 0; i < playerOrigins.size(); i++)
        {
            Player p = playerOrigins.at(i);
            std::cout << p.getAsciiArt() << " " << p.getDescription() << "\t\n" << std::endl;
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
        
        continueKey = getContinueKey("Do you want to play this class? (y/n): ");
    }
    while (continueKey == 'n');
    inputName = getLineFromPrompt("Name: ");
    
    clearScreen();
    
    player = Player(inputOrigin, inputName);
    
}
Origin Game::getOriginFromPrompt(const std::string prompt){
    while (true)
    {
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
            std::cout << "Please enter a valid player origin." << std::endl;
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

// Display
void Game::displayHUD(const Player &player){
    std::cout << "Souls : " << player.getSouls() << std::endl;
    std::cout << "Potion : " + player.getPotion().name << "\n" << std::endl;
    std::cout << "  " << player.getAsciiArt() <<std::endl;
    std::cout << "\"" << player.getDescription() << "\"" << std::endl;
    std::cout << "STR~" << player.getStrength();
    std::cout << "\tDEX~" << player.getDexterity();
    std::cout << "\tINT~" << player.getIntelligence();
    std::cout << "\tFAI~" << player.getFaith() << std::endl;
    std::cout << "\nHP: " << player.getHP() << "/" << player.getHPMax() << std::endl;
    std::cout << "Weapon: " << player.getWeapon().getName();
    std::cout << " (" << player.getWeapon().getDamage() << " " << ((player.getWeapon().getDamageType() == physical) ? "physical" : "magic") << " damage)" << std::endl;
    if (player.getArmor() != 0)
    {
        std::cout << "Armor: " << player.getArmor() << std::endl;
    }
    if (player.getResistance() != 0)
    {
        std::cout << "Resistance: " << player.getResistance() << std::endl;
    }
    std::cout << std::endl;
}
void Game::displayHUD(const Player &player, const Enemy &enemy){

    // Clear the screen
    clearScreen();
    
    // Display Souls
    std::cout << "Souls  : " + std::to_string(player.getSouls()) << std::endl;
    
    // Display Potion
    std::cout << "Potion : " + player.getPotion().name << std::endl;
    
    // Display Floor
    std::cout << floor << "F" << std::endl;
    
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
    printWithFormattingHUD("\n<" + player.getWeapon().getName() + ">", "<" + enemy.getWeapon().getName() + ">");
    printMovesWithFormattingHUD(player.getWeapon(), enemy);
}
void Game::printWithFormattingHUD(const std::string &leftString, const std::string &rightString, const OptionSelectHUD optionSelectHUD){
    const int TOTAL_WIDTH = 40;
    std::cout << std::setw(TOTAL_WIDTH) << std::left << leftString;
    switch (optionSelectHUD) {
        case addPipes:
            std::cout << std::right << std::setw(2) << "|" << std::setw(10) << "| ";
            break;
            
        case addVersus:
            std::cout << " | VERSUS | ";
            break;
            
        default:
        case addNothing:
            std::cout << std::setw(13) << "";
            break;
    }
    std::cout << std::setw(TOTAL_WIDTH) << std::left << rightString << std::endl;
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
        leftString = " " + playerWeapon.getMoves().at(i).getName() + ": ";
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
            WeaponMove chosenMove = enemy.getWeapon().getMoves().at(enemy.getMoveChooser());
            int chosenMoveDamage = enemy.getWeapon().getDamage(chosenMove);
            rightString = chosenMove.getName() + ": ";
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
                std::cout << "You defeated " + enemy.getName() + "… but here comes another enemy!" << std::endl;
                floor++;
                createNewEnemy();
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
            if (enemy.getHP() == 0)
            {
                std::cout << "You defeated " + enemy.getName() + "… but here comes another enemy!" << std::endl;
                floor++;
                createNewEnemy();
            }
        }
        if (player.getHP() <= 0)
        {
            std::cout << "You died…" << std::endl;
        }
        getSmartInput("Continue…");
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
                        std::cout << player.getName() << " drank the " << lowercase(player.getPotion().name) << " potion!" << std::endl;
                        std::cout << player.getName() << " healed " << player.heal(player.popPotion().grade) << " HP" << std::endl;
                    }
                }
                else
                {
                    std::cout << "No potions…" << std::endl;
                }
            }
            else
            {
                std::cout << "Please enter a valid move." << std::endl;
            }
            getSmartInput("Continue…");
        }
    }
    while (chosenMoveIndex < 0);
    WeaponMove chosenMove = player.getWeapon().getMoves().at(chosenMoveIndex);
    // Confirm weapon move
    continueKey = getContinueKey("Use " + chosenMove.getName() + "? (y/n): ");
    if (continueKey == 'y')
    {
        std::cout << player.getName() << " performed: " << chosenMove.getName() << "!" << std::endl;
        std::cout << player.getName() << " dealt " << player.getWeapon().getDamage(chosenMove) << ((player.getWeapon().getDamageType() == magic) ? " magic" : "") << " dmg" << std::endl;
        if (chosenMove.getDamagePercentage() != 0)
        {
            enemy.takeDamage(player.getWeapon().getDamage(chosenMove));
        }
        getSmartInput("Continue...");
    }
    else
    {
        // PLAYER DID NOT WANT TO USE THAT MOVE
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
    std::cout << "\n" << enemy.getName() << " dealt " << chosenMoveDamage << (enemy.getWeapon().getDamageType() == magic ? " magic" : "") << " dmg" << std::endl;
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
void Game::createNewEnemy(){
    enemy = Enemy(static_cast<EnemyType>(rand() % (floor + 1 < TOTAL_ENEMY_TYPES ? floor : TOTAL_ENEMY_TYPES)), floor);
}
