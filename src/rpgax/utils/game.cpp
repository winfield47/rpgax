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
std::set<EnemyType> Game::enemyTypesSeen = {};
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
    if (prompt != "Continue...")
    {
        if (smartInput == "")
        {
            // Make the input always fail a check for anything
            input = "\1";
            return;
        }
    }
    input = smartInput;
}
void Game::createNewPlayer(){
    
    // Player choices
    Origin inputOrigin;
    std::string inputName;
    
    char continueKey = 'y';
    bool hasDisplayedOriginsOnce = false;
    
    std::vector<Player> playerOrigins =
    {
        Player(brute, "Brute"), Player(rogue, "Rogue"), Player(wizard, "Wizard"), Player(inquisitor, "Inquisitor"), Player(nomad, "Nomad")
    };
    
    do
    {
        clearScreen();
        if (hasDisplayedOriginsOnce)
        {
            printIntroductionParagraph(instant);
        }
        else
        {
            // Create the playable character origins for the user to browse
            printIntroductionParagraph(normal);
            pause();
        }
        
        // Spacing
        printCharByChar("\n\n");
        
        for (size_t i = 0; i < playerOrigins.size(); i++)
        {
            Player currentPlayerOrigin = playerOrigins.at(i);
            if (hasDisplayedOriginsOnce)
            {
                printCharByChar(" " + currentPlayerOrigin.getAsciiArt() + " " + currentPlayerOrigin.getDescription(), fast);
            }
            else
            {
                pause();
                printCharByChar(" " + currentPlayerOrigin.getAsciiArt(), slow);
                pause();
                printCharByChar(" " + currentPlayerOrigin.getDescription(), fast);
                pause();
            }
            std::cout << "\t\n" << std::endl;
        }
        
        inputOrigin = getOriginFromPrompt();
        std::string originDescription = "";
        switch (inputOrigin)
        {
            case brute:
                originDescription = "A tanky brute… you could take a hit.";
                break;
            case rogue:
                originDescription = "A quick rogue… you liked to strike first.";
                break;
            case wizard:
                originDescription = "A young wizard… you had hopes for powerful magic.";
                break;
            case inquisitor:
                originDescription = "An inquisitor… you were a vessel for a higher power.";
                break;
            default:
            case nomad:
                originDescription = "A nomad… an exiled wanderer from a forgotten land.";
                break;
        }
        Player originCharacter = Player(inputOrigin, originDescription);
        
        displayOrigin(originCharacter);
        
        continueKey = getContinueKey("Do you want to play the " + getStringForOrigin(originCharacter.getOrigin()) + "? (Y/n): ");
        hasDisplayedOriginsOnce = true;
    }
    while (continueKey == 'n');
    pause();
    printCharByChar("\nYou remember that you were a " + lowercase(getStringForOrigin(inputOrigin)) + "...", slow);
    pause();
    printCharByChar("\nThen suddenly", fast);
    pause();
    printCharByChar(", a name flutters past your thoughts...", slow);
    pause();
    inputName = getLineFromPrompt("\n\nWhat was your name? ");
    
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
void Game::printIntroductionParagraph(PrintSpeed printSpeed){
    std::string asciiSkeleton = R"(

    ,__
   (o o}
 ,--`Y'--._
/^':   ;'`~^
   / _ \
  \.' `|/
  `z' `k'

)";
    std::string asciiKnight = R"(

  / \
  | |
  |.|
  |.|
  |:|      __
,_|:|_,   /  )
  (Oo    / _I_
   +\ \  || __|
      \ \||___|
        \ /.:.\-\
         |.:. /-----\
         |___|::oOo::|
         /   |:<_T_>:|
        |_____\ ::: /
         | |  \ \:/
         | |   | |
         \ /   | \___
         / |   \_____\
         `-'

)";
    std::string asciiMushrooms = R"(

           ____
       _.-'78o `"`--._
   ,o888o.  .o888o,   ''-.
 ,88888P  `78888P..______.]
/_..__..----""        __.'
`-._       /""| _..-''
    "`-----\  `\
            |   ;.-""--..
            | ,8o.  o88. `.
            `;888P  `788P  :
      .o""-.|`-._         ./
     J88 _.-/    ";"-P----'
     `--'\`|     /  /
         | /     |  |
         \|     /   |akn
          `-----`---'

)";
    std::string asciiSouls = R"(
          ,
        .--')
       /    /
      |    /
   /`.\   (_.'\
   \          /
    '--. .---'
      ( " )
       '-'
                ,
                 \`-,      ,     =-
             .-._/   \_____)\
            ("              / =-
             '-;   ,_____.-'       =-
              /__.'

)";
    std::string asciiCandle = R"(

             .
           .....
       ..:::::::::..
    ..:::::: # ::::::..
  ..:::::: ====== :::::..
 ..::::: ========== ::::..
..::::: ==== |\ ==== ::::..
.::::: ==== /%#| ==== :::..
.::::: === |&@/ ==== :::::.
..::::: ===_\|_==== :::::..
 ..::::: /| .:. | :::::...
  ..:::: || .:. | ::::...
   ...:: (| .:. | ::....
     .... | .:. | ....

)";
    std::string asciiKeyboard = R"(

,---,---,---,---,---,---,---,---,---,---,---,---,---,-------,
| ~ | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | [ | ] | <-    |
|---'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-----|
| ->| | " | , | . | P | Y | F | G | C | R | L | / | = |  \  |
|-----',--',--',--',--',--',--',--',--',--',--',--',--'-----|
| Caps | A | O | E | U | I | D | H | T | N | S | - |  Enter |
|------'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'--------|
|        | ; | Q | J | K | X | B | M | W | V | Z |          |
|------,-',--'--,'---'---'---'---'---'---'-,-'---',--,------|
| ctrl |  | alt |                          | alt  |  | ctrl |
'------'  '-----'--------------------------'------'  '------'

)";
    std::string asciiRatDead = R"(

  ,,==.
 //    `
||      ,--~~~~-._ _(\--,_
 \\._,-~   \      '    *  `o
  `---~\( _/,___( /_/`---~~
        ``==-    `==-,

)";
    std::string asciiRat = R"(


               _     __,..---""-._                 ';-,
        ,    _/_),-"`             '-.                `\\
       \|.-"`    -_)                 '.                ||
       /`   a   ,                      \              .'/
       '.___,__/                 .-'    \_        _.-'.'
          |\  \      \         /`        _`""""""`_.-'
             _/;--._, >        |   --.__/ `""""""`
           (((-'  __//`'-......-;\      )
                (((-'       __//  '--. /
                          (((-'    __//
                                 (((-' jgs

)";
    clearScreen();
    if (printSpeed != instant)
    {
        // GAME RULES
        pause();
        printCharByChar("Welcome to rpgax!");
        pause();
        printCharByChar("\n-An ASCII RPG", slow);
        pause();
        printCharByChar(asciiCandle, lightning);
        pause();
        printCharByChar("When playing this game, please don't touch the keyboard while text is typing.");
        // pause();
        // printCharByChar(asciiKeyboard, lightning);
        pause();
        printCharByChar("\nThe text gets really messy if you do... [o_o]", slow);
        pause(2);
        printCharByChar("\n\nAlright, now that you know the rules, it's time to enter world of ASCII...", fast);
        pause();
        printCharByChar(asciiKnight, lightning);
        pause();
        printCharByChar("Press enter to begin...", fast);
        getSmartInput("");
        clearScreen();
        pause(2);
        
        // STORY BEGINNING (rat)
        printCharByChar("A rat is scuttling around the depths of a dark dungeon,");
        pause();
        printCharByChar("\ndesperately looking for anything to eat.");
        pause();
        printCharByChar(asciiRat, lightning);
        pause();
        printCharByChar("\nEventually, it finds something...");
        pause();
        printCharByChar("\nAn old dungeon cell with a ");
        pause();
        printCharByChar("lifeless body inside.", slow);
        pause();
        printCharByChar(asciiSkeleton, fast);
        pause(2);
        printCharByChar("However",slow);
        pause();
        printCharByChar(", an EARTHQUAKE displaces a stone in the wall.", fast);
        pause(1.5);
        printCharByChar("\nAnd the stone falls,");
        pause();
        printCharByChar(" killing the rat.");
        pause(1);
        printCharByChar(asciiRatDead, lightning);
        pause();
        printCharByChar("From within the dead rat", slow);
        pause();
        printCharByChar(", a bunch of", slow);
        pause();
        printCharByChar(" ...");
        printCharByChar("souls", slow);
        printCharByChar("...");
        pause();
        printCharByChar(" rush into the rotted corpse.", slow);
        pause();
        printCharByChar("\n\nContinue...");
        getSmartInput("");
        clearScreen();
        pause();
        
        // YOU WAKE UP
        printCharByChar("You wake up—", fast);
        pause();
        printCharByChar("GASPING", fast);
        printCharByChar(" for air!", slow);
        pause();
        clearScreen();
        pause();
        printCharByChar("You look around.", fast);
        pause();
        printCharByChar(asciiMushrooms, lightning);
        pause();
        printCharByChar("These mushrooms growing out of a rat's corpse,");
        pause();
        printCharByChar("\nare the only thing notable in this chamber.");
        pause();
        printCharByChar("\nLooks like the rat died weeks ago...");
        pause();
        printCharByChar(" gross...", slow);
        pause();
        printCharByChar("\nYou don't remember falling asleep here...");
        pause(1);
        printCharByChar("\nIn fact,", fast);
        pause(0.2);
        printCharByChar(" you don't remember anything at all...", slow);
        pause();
        printCharByChar("\n\nContinue...");
        getSmartInput("");
        clearScreen();
        
        // HOW LONG HAS IT BEEN...
        printCharByChar("It feels like you've been asleep for days...", fast);
        pause();
        printCharByChar("\n\nor has it been...");
        pause(1);
        printCharByChar(" years...", slow);
        pause(2);
        printCharByChar("\n\nContinue...");
        getSmartInput("");
        clearScreen();
        pause();
        
        // REMEMBERENCE
        printCharByChar("You look down at yourself.");
        pause();
        printCharByChar("\n\nYour flesh is rotting...", fast);
        pause(2);
        printCharByChar(" but there is no pain...", slow);
        pause();
        printCharByChar("\n\nThese clothes seem familiar to you",slow);
        pause(2);
        printCharByChar(",\nand an old memory washes over you in a wave of warmth.", slow);
        pause(3);
        printCharByChar("\nBut it fades as fast as a dream.", slow);
        pause(2);
        
        // SMELLING SOULS
        printCharByChar("\n\nThe smell of ", slow);
        pause();
        printCharByChar("...");
        printCharByChar("souls", slow);
        printCharByChar("...");
        pause();
        printCharByChar(" fills your mind.");
        pause(0.75);
        printCharByChar("\n\nYou can smell where they are.");
        pause();
        printCharByChar("\n\nThey're just up the stairs on the next floor.");
        pause(0.25);
        printCharByChar("\n\nYou can almost taste them.", fast);
        pause(0.25);
        printCharByChar("\n\nAll you'd have to do is take them.", fast);
        printCharByChar("\n\n\nALL YOU'D HAVE TO DO IS KILL THEM!!!", fast);
        clearScreen();
        printCharByChar("You try to shake the feeling...");
        pause(2);
        printCharByChar(" and think back to who you are...");
        printCharByChar("\n\nContinue...");
        getSmartInput("");
        clearScreen();
        pause();
        
        // CHOOSE ORIGIN
        printCharByChar("Who were you before this?");
        pause();
    }
    else
    {
        printCharByChar("With your flesh rotting and the smell of souls clouding your mind,", fast);
        printCharByChar("\nyou try desperately to remember who you were...", fast);
        pause();
    }
}
void Game::displayOrigin(const Player &originCharacter){
    clearScreen();
    pause();
    printCharByChar(originCharacter.getFullBlownASCII(), lightning);
    pause();
    printCharByChar("\n\"" + originCharacter.getDescription() + "\"");
    pause();
    printCharByChar("\n\nASCII Model: ", fast);
    pause();
    printCharByChar(originCharacter.getAsciiArt());
    pause();
    printCharByChar("\n\nStarting Stats/Gear:", slow);
    pause();
    printCharByChar("\n\n HP     : ", fast);
    pause();
    printCharByChar(std::to_string(originCharacter.getHP()) + "/" + std::to_string(originCharacter.getHPMax()));
    pause();
    printCharByChar("\n Weapon : ", fast);
    pause();
    printCharByChar(originCharacter.getWeapon().getName());
    pause();
    printCharByChar(" (" + std::to_string(originCharacter.getWeapon().getDamage()) + " " + ((originCharacter.getWeapon().getDamageType() == physical) ? "physical" : "magic") + " damage)");
    pause();
    printCharByChar("\n\n Souls  : ", fast);
    pause();
    printCharByChar(std::to_string(originCharacter.getSouls()));
    pause();
    printCharByChar("\n Potion : ", fast);
    pause();
    printCharByChar(originCharacter.getPotion().name);
    pause();
    std::cout << std::endl;
    if (originCharacter.getArmor() != 0)
    {
        printCharByChar(" Armor: ", fast);
        pause();
        printCharByChar(std::to_string(originCharacter.getArmor()));
        pause();
        std::cout << std::endl;
    }
    if (player.getResistance() != 0)
    {
        printCharByChar(" Resistance: ", fast);
        pause();
        printCharByChar(std::to_string(originCharacter.getResistance()));
        pause();
        std::cout << std::endl;
    }
    pause();
    printCharByChar("\n STR~", fast);
    pause();
    printCharByChar(std::to_string(originCharacter.getStrength()));
    pause();
    printCharByChar("  DEX~", fast);
    pause();
    printCharByChar(std::to_string(originCharacter.getDexterity()));
    pause();
    printCharByChar("  INT~", fast);
    pause();
    printCharByChar(std::to_string(originCharacter.getIntelligence()));
    pause();
    printCharByChar("  FAI~", fast);
    pause();
    printCharByChar(std::to_string(originCharacter.getFaith()));
    std::cout << std::endl << std::endl;
    pause();
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
        std::set<EnemyType>::iterator it = enemyTypesSeen.find(enemy.getType());
            if (it != enemyTypesSeen.end()) {
                // Enemy type is in the set
                universalPrintSpeed = fast;
            } else {
                // Enemy type is not in the set
                universalPrintSpeed = normal;
            }
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
    printCharByChar("\n", playerPrintSpeed);
    
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
        turnInfo += " is slower than you...";
    }
    else
    {
        turnInfo += " is faster than you!";
    }
    printWithFormattingHUD(" " + getStringAttributes(player), turnInfo, addPipes);
    
    // Display WEAPONS and MOVES
    printWithFormattingHUD("\n-" + player.getWeapon().getName() + ":", "-" + enemy.getWeapon().getName() + ":");
    printMovesWithFormattingHUD(player.getWeapon(), enemy);
    std::cout << std::endl;
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
        if (isSubset("is than you", rightString))
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
void Game::printGameOver(){
    clearScreen();
    std::string gameOverLiteral = R"(
      ____    _    __  __ _____         _____     _______ ____
     / ___|  / \  |  \/  | ____|       / _ \ \   / / ____|  _ \
    | |  _  / _ \ | |\/| |  _|        | | | \ \ / /|  _| | |_) |
    | |_| |/ ___ \| |  | | |___       | |_| |\ V / | |___|  _ <
     \____/_/   \_\_|  |_|_____|       \___/  \_/  |_____|_| \_\

    )";
    printCharByChar(gameOverLiteral, lightning);
    getSmartInput("Thanks for playing!");
    clearScreen();
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
            printGameOver();
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
        // GET A MOVE FROM PLAYER
        displayHUD(player, enemy);
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
        // Check for: <SpecialMoves>
        if (chosenMoveIndex < 0)
        {
            // POTION
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
                    printCharByChar("You don't have a potion...");
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
        else // IF A VALID <MOVE> HAS BEEN PICKED
        {
            WeaponMove chosenMove = player.getWeapon().getMoves().at(chosenMoveIndex);
            // Confirm weapon move
            continueKey = getContinueKey("Use <" + chosenMove.getName() + ">? (Y/n): ");
            if (continueKey == 'y')
            {
                // IF THE USER CONFIRMS THE <MOVE>
                std::cout << std::endl;
                dealWeaponMoveDamageAsCharacter1ToCharacter2(player, enemy, chosenMove);
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
    enemy.chooseNewMove();
    
    // Using enemy move
    dealWeaponMoveDamageAsCharacter1ToCharacter2(enemy, player, chosenMove);
    getSmartInput();
}
void Game::dealWeaponMoveDamageAsCharacter1ToCharacter2(const Character &character1, Character &character2, const WeaponMove chosenMove){
    std::string spacing = "\n";
    if (chosenMove.getDamagePercentage() != 0) // IF THE MOVE DOES DAMAGE
    {
        int damageDealt = 0;
        
        // FIGURE OUT HOW MUCH DMG TO DO TO CHARACTER_2
        
        if (chosenMove.getAmountOfChecks() > 0) // IF THERE ARE CHECKS
        {
            int checksSucceeded = 0;
            int randomNumberOutOf100 = rand() % 100;
            printCharByChar(character1.getName() + " used <" + chosenMove.getName() + ">: ");
            for (size_t i = 0; i < chosenMove.getAmountOfChecks() - 1; i++)
            {
                pause();
                if (getCharacterAttributeValue(character1, chosenMove.getUsedAttribute()) > randomNumberOutOf100)
                {
                    checksSucceeded += 1;
                    printCharByChar("[X]");
                }
                else
                {
                    printCharByChar("[ ]");
                }
                printCharByChar("~");
                randomNumberOutOf100 = rand() % 100;
            }
            pause();
            if (getCharacterAttributeValue(character1, chosenMove.getUsedAttribute()) > randomNumberOutOf100)
            {
                checksSucceeded += 1;
                printCharByChar("[X]");
            }
            else
            {
                printCharByChar("[ ]");
            }
            // now deal the damage from success of checks
            damageDealt = character1.getWeapon().getDamage(chosenMove) * ((static_cast<double>(checksSucceeded) / chosenMove.getAmountOfChecks()));
            pause();
        }
        else // IF THERE ARE NO CHECKS
        {
            spacing = "";
            damageDealt = character1.getWeapon().getDamage(chosenMove);
        }
        
        // Spacing
        std::cout << spacing;
        
        // DEAL THE DAMAGE DEALT
        if (character1.getWeapon().getDamageType() == physical)
        {
            int actualDamageDealt = damageDealt - character2.getArmor();
            if (actualDamageDealt < 0)
            {
                actualDamageDealt = 0;
            }
            character2.takeDamage(actualDamageDealt);
            printCharByChar(character1.getName() + " dealt ");
            pause();
            printCharByChar(std::to_string(actualDamageDealt));
            pause();
            printCharByChar(" damage", fast);
        }
        else // if magic damage
        {
            int actualDamageDealt = damageDealt - character2.getResistance();
            if (actualDamageDealt < 0)
            {
                actualDamageDealt = 0;
            }
            character2.takeDamage(actualDamageDealt);
            printCharByChar(character1.getName() + " dealt ");
            pause();
            printCharByChar(std::to_string(actualDamageDealt));
            pause();
            printCharByChar(" magic damage", fast);
        }
    }
    else // IF THE MOVE DOES NO DAMAGE (SOMETHING SPECIAL)
    {
        
    }
    pause();
    std::cout << std::endl;
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
    displayHUD(player, enemy);
    pause();
    printCharByChar("You defeated " + enemy.getName() + "!", fast);
    pause();
    int soulsHarvested = enemy.retrieveSoulsHeld();
    printCharByChar("\nSouls harvested: ", fast);
    pause();
    printCharByChar(std::to_string(enemy.retrieveSoulsHeld()));
    player.addSouls(soulsHarvested);
    pause();
    std::cout << std::endl;
    std::cout << std::endl;
    printCharByChar("In the next floor you see... ", fast);
    pause();
    floor++;
    enemyTypesSeen.insert(enemy.getType());
    createNewEnemy();
    printCharByChar(enemy.getName() + "...");
    pause();
    std::cout << std::endl;
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
int Game::getCharacterAttributeValue(const Character &character, const WeaponMoveAttribute weaponMoveAttribute){
    switch (weaponMoveAttribute)
    {
        case strength:
            return character.getStrength();
        case dexterity:
            return character.getDexterity();
        case intelligence:
            return character.getIntelligence();
        case faith:
            return character.getFaith();
        default:
            throw "getCharacterAttribute error";
    }
}
