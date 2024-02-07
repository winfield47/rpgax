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
bool Game::playerRanFromFight = false;
PrintSpeed Game::playerPrintSpeed = fast;
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
        // Create the playable character origins for the user to browse
        if (hasDisplayedOriginsOnce)
        {
            printIntroductionParagraph(instant);
        }
        else
        {
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
                printCharByChar(" " + currentPlayerOrigin.getAsciiArt());
                pause(0.2);
                printCharByChar(" " + currentPlayerOrigin.getDescription(), fast);
                pause(0.3);
            }
            std::cout << "\t\n" << std::endl;
        }
        
        inputOrigin = getOriginFromPrompt();
        std::string originDescription = "";
        switch (inputOrigin)
        {
            case brute:
                originDescription = "A tanky brute who can take a hit.";
                break;
            case rogue:
                originDescription = "A quick rogue that strikes first.";
                break;
            case wizard:
                originDescription = "A young wizard with hopes for powerful magic.";
                break;
            case inquisitor:
                originDescription = "An inquisitor, a vessel for a higher power.";
                break;
            default:
            case nomad:
                originDescription = "A nomad… an exiled wanderer from a forgotten land.";
                break;
        }
        Player originCharacter = Player(inputOrigin, originDescription);
        
        displayOrigin(originCharacter, hasDisplayedOriginsOnce);
        
        continueKey = getContinueKey("Is this who you remember yourself to be? (Y/n): ");
        hasDisplayedOriginsOnce = true;
    }
    while (continueKey == 'n');
    clearScreen();
    printCharByChar("You remember that you were a " + lowercase(getStringForOrigin(inputOrigin)) + "...");
    pause();
    printCharByChar("\nThen suddenly", fast);
    pause();
    printCharByChar(", a name flutters past your thoughts...");
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
                return " phys";
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
    std::string asciiCastle = R"(

                             -|             |-
         -|                  [-_-_-_-_-_-_-_-]                  |-
         [-_-_-_-_-]          |             |          [-_-_-_-_-]
          | o   o |           [  0   0   0  ]           | o   o |
           |     |    -|       |           |       |-    |     |
           |     |_-___-___-___-|         |-___-___-___-_|     |
           |  o  ]              [    0    ]              [  o  |
           |     ]   o   o   o  [ _______ ]  o   o   o   [     | ----__________
_____----- |     ]              [ ||||||| ]              [     |
           |     ]              [ ||||||| ]              [     |
       _-_-|_____]--------------[_|||||||_]--------------[_____|-_-_
      ( (__________------------_____________-------------_________) )

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
        // CHECK IF PLAYER IS A RETURNER
        if (getContinueKey("Is this your first time playing rpgax? (Y/n): ") == 'y')
        {
            clearScreen();
            // GAME RULES
            pause();
            printCharByChar("Welcome to rpgax!");
            pause();
            printCharByChar("\n-The Roguelike ASCII RPG");
            pause();
            printCharByChar(asciiCastle, lightning);
            pause();
            printCharByChar("When playing this game, please don't touch the keyboard while text is typing.");
            pause();
            printCharByChar("\nIt'll ruin your inputs, and C++ won't let me stop you from doing it [o_o]");
            pause(1.5);
            printCharByChar("\n\nAlright, now that you know the rules, it's time to enter world of ASCII", fast);
            pause();
            printCharByChar(asciiKnight, lightning);
            pause();
            printCharByChar("Press Enter to begin...", fast);
            getSmartInput("");
            clearScreen();
            
            // Does the player WANT to read the intro story?
            if (getContinueKey("Do you like stories? (Y/n): ") == 'y')
            {
                // STORY BEGINNING (rat)
                clearScreen();
                pause(2);
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
                clearScreen();
                printCharByChar("With your flesh rotting and the smell of souls clouding your mind,", fast);
                printCharByChar("\nyou try desperately to remember who you were before all this...", fast);
                pause();
            }
        }
        else
        {
            // THE PLAYER HAS PLAYED BEFORE AND SKIPPED IT ALL
            clearScreen();
            printCharByChar("With your flesh rotting and the smell of souls clouding your mind,", fast);
            printCharByChar("\nyou try desperately to remember who you were...", fast);
            pause();
        }
    }
    else
    {
        printCharByChar("With your flesh rotting and the smell of souls clouding your mind,", faster);
        printCharByChar("\nyou try desperately to remember who you were...", faster);
        pause();
    }
}
void Game::displayOrigin(const Player &originCharacter, bool hasDisplayedOriginsOnce){
    clearScreen();
    pause();
    if (hasDisplayedOriginsOnce)
    {
        PrintSpeed currentPrintSpeed = faster;
        printCharByChar(originCharacter.getFullBlownASCII(), lightning);
        pause();
        printCharByChar("\n\"" + originCharacter.getDescription() + "\"", fast);
        pause();
        printCharByChar("\n\nASCII Model: ", currentPrintSpeed);
        printCharByChar(originCharacter.getAsciiArt(), currentPrintSpeed);
        printCharByChar("\n\nStarting Stats/Gear:", currentPrintSpeed);
        printCharByChar("\n\n HP     : ", currentPrintSpeed);
        printCharByChar(std::to_string(originCharacter.getHP()) + "/" + std::to_string(originCharacter.getHPMax()), currentPrintSpeed);
        printCharByChar("\n Weapon : ", currentPrintSpeed);
        printCharByChar(originCharacter.getWeapon().getName(), currentPrintSpeed);
        printCharByChar(" (" + std::to_string(originCharacter.getWeapon().getDamage(originCharacter.getWeapon().getMoves().at(0))) + " " + ((originCharacter.getWeapon().getDamageType() == physical) ? "physical" : "magic") + " damage)", currentPrintSpeed);
        if (originCharacter.getArmor() != 0)
        {
            printCharByChar("\n Armor  : ", currentPrintSpeed);
            printCharByChar(std::to_string(originCharacter.getArmor()), currentPrintSpeed);
        }
        if (originCharacter.getResistance() != 0)
        {
            printCharByChar("\n Resist : ", currentPrintSpeed);
            printCharByChar(std::to_string(originCharacter.getResistance()), currentPrintSpeed);
        }
        printCharByChar("\n\n Souls  : ", currentPrintSpeed);
        printCharByChar(std::to_string(originCharacter.getSouls()), currentPrintSpeed);
        printCharByChar("\n Potion : ", currentPrintSpeed);
        printCharByChar((originCharacter.getPotion().grade != 0 ? std::to_string(originCharacter.getPotion().grade) + " " : "") + originCharacter.getPotion().name, currentPrintSpeed);
        std::cout << std::endl;
        printCharByChar("\n STR~", currentPrintSpeed);
        printCharByChar(std::to_string(originCharacter.getStrength()), currentPrintSpeed);
        printCharByChar("  DEX~", currentPrintSpeed);
        printCharByChar(std::to_string(originCharacter.getDexterity()), currentPrintSpeed);
        printCharByChar("  INT~", currentPrintSpeed);
        printCharByChar(std::to_string(originCharacter.getIntelligence()), currentPrintSpeed);
        printCharByChar("  FAI~", currentPrintSpeed);
        printCharByChar(std::to_string(originCharacter.getFaith()), currentPrintSpeed);
    }
    else
    {
        printCharByChar(originCharacter.getFullBlownASCII(), lightning);
        pause();
        printCharByChar("\n\"" + originCharacter.getDescription() + "\"", fast);
        pause();
        printCharByChar("\n\nASCII Model: ", fast);
        printCharByChar(originCharacter.getAsciiArt(), fast);
        pause();
        printCharByChar("\n\nStarting Stats/Gear:", fast);
        pause();
        printCharByChar("\n\n HP     : ", fast);
        printCharByChar(std::to_string(originCharacter.getHP()) + "/" + std::to_string(originCharacter.getHPMax()), fast);
        pause();
        printCharByChar("\n Weapon : ", fast);
        printCharByChar(originCharacter.getWeapon().getName(), fast);
        pause();
        printCharByChar(" (" + std::to_string(originCharacter.getWeapon().getDamage(originCharacter.getWeapon().getMoves().at(0))) + " " + ((originCharacter.getWeapon().getDamageType() == physical) ? "physical" : "magic") + " damage)", fast);
        pause();
        if (originCharacter.getArmor() != 0)
        {
            printCharByChar("\n Armor  : ", fast);
            printCharByChar(std::to_string(originCharacter.getArmor()), fast);
            pause();
        }
        if (originCharacter.getResistance() != 0)
        {
            printCharByChar("\n Resist : ", fast);
            printCharByChar(std::to_string(originCharacter.getResistance()), fast);
            pause();
        }
        printCharByChar("\n\n Souls  : ", fast);
        printCharByChar(std::to_string(originCharacter.getSouls()), fast);
        pause();
        printCharByChar("\n Potion : ", fast);
        printCharByChar((originCharacter.getPotion().grade != 0 ? std::to_string(originCharacter.getPotion().grade) + " " : "") + originCharacter.getPotion().name, fast);
        pause();
        printCharByChar("\n\n STR~", fast);
        printCharByChar(std::to_string(originCharacter.getStrength()), fast);
        printCharByChar("  DEX~", fast);
        printCharByChar(std::to_string(originCharacter.getDexterity()), fast);
        printCharByChar("  INT~", fast);
        printCharByChar(std::to_string(originCharacter.getIntelligence()), fast);
        printCharByChar("  FAI~", fast);
        printCharByChar(std::to_string(originCharacter.getFaith()), fast);
        pause();
    }
    std::cout << std::endl << std::endl;
    pause();
}
void Game::displayCamp(PrintSpeed currentPrintSpeed){
    std::string asciiCamp = R"(
                          __,--'\
                    __,--'    :. \.
               _,--'              \`.
              /|\       `          \ `.
             / | \        `:        \  `/
            / '|  \        `:.       \
           / , |   \                  \
          /    |:   \              `:. \
         /| '  |     \ :.           _,-'`.
       \' |,  / \   ` \ `:.     _,-'_|jrei`/
          '._;   \ .   \   `_,-'_,-'
        \'    `- .\_   |\,-'_,-'
               `--|_,`'
                            `/
)";
    if (currentPrintSpeed == instant)
    {
        printCharByChar(asciiCamp, instant);
    }
    else
    {
        printCharByChar(asciiCamp, lightning);
        pause();
    }
    printCharByChar("Actions:", currentPrintSpeed);
    printCharByChar("\n <Rest>", currentPrintSpeed);
    printCharByChar("\n <Level Up>", currentPrintSpeed);
    printCharByChar("\n <Visit Campfire>", currentPrintSpeed);
    printCharByChar("\n <Continue>\n\n", currentPrintSpeed);
    
}
void Game::displayShop(PrintSpeed currentPrintSpeed){
    std::string asciiShop = R"(
jgs     ______
       /     /\
      /     /  \
     /_____/----\_
    "     "             "Hello traveller,
 _ ___                     I'll trade anything for souls!"
(@))_))                              \
                      (              \  (}}}.
                       )                v,v))
                      (  (              \=_/'
                          )             ,'-'.
                    (    (  ,,      _.__|/ /|
                     ) /\ -((------((_|___/ |
                   (  // | (`'      ((  `'--|
                 _ -.;_/ \\--._      \\ \-._/.
                (_;-// | \ \-'.\    <_,\_\`--'|
                ( `.__ _  ___,')      <_,-'__,'
                 `'(_ )_)(_)_)'       jrei

)";
    if (currentPrintSpeed == instant)
    {
        printCharByChar(asciiShop, instant);
    }
    else
    {
        printCharByChar(asciiShop, lightning);
        pause();
    }
    printCharByChar("Actions:", currentPrintSpeed);
    printCharByChar("\n <Trade>", currentPrintSpeed);
    printCharByChar("\n <Go to Tent>\n\n", currentPrintSpeed);
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
    }
    // Display Souls
    printCharByChar("\nSouls    : " + std::to_string(player.getSouls()), playerPrintSpeed);
    
    // Display Potion
    printCharByChar("\n<Potion> : " + player.getPotion().name + (player.getPotion().grade != 0 ? " (Grade " + std::to_string(player.getPotion().grade) + ")" : "") + "\n", playerPrintSpeed);
   
    // Spacing
    printCharByChar("\n", playerPrintSpeed);
    
    // Display ASCII ART
    printWithFormattingHUD("  " + player.getAsciiArt(), "  " + enemy.getAsciiArt(), addPipes);
    
    // Display DESCRIPTION
    std::string playerDescriptionDisplayStr = "\"" + player.getDescription() + "\"";
    std::string enemyDescriptionDisplayStr = "\"" + enemy.getDescription() + "\"";
    printWithFormattingHUD("\"" + player.getDescription() + "\"", "\"" + enemy.getDescription() + "\"", addVersus);
    
    // Display HP, AMR, RES
    printWithFormattingHUD(" " + getStringHpAmrRes(player), " " + getStringHpAmrRes(enemy), addPipes);
    
    // Display PLAYER ATTRIBUTES and TURN INFORMATION
    std::string turnInfo = " ";
    determineWhoGoesFirst();
    turnInfo += enemy.getName();
    if (playerGoesFirst)
    {
        turnInfo += " is slower than you!";
    }
    else
    {
        turnInfo += " is faster than you!";
    }
    printWithFormattingHUD(" " + getStringAttributes(player), turnInfo, addPipes);
    
    // Display WEAPONS and <MOVES>
    printWithFormattingHUD("\n-Weapon: " + player.getWeapon().getName(), "-Enemy Intent (" + enemy.getWeapon().getName() + "):");
    printMovesWithFormattingHUD(player.getWeapon(), enemy);
    
    // Display <DEFAULT MOVES>
    printCharByChar(" <Dodge>", playerPrintSpeed);
    printCharByChar("\n <Run> []~[] DEX", playerPrintSpeed);
    
    // Spacing
    std::cout << std::endl << std::endl;
    pause();
    enemyIsPrinted = true;
}
void Game::printWithFormattingHUD(const std::string &leftString, const std::string &rightString, const OptionSelectHUD optionSelectHUD){
    const int TOTAL_WIDTH = 36;
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
            printCharByChar(rightString);
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
void Game::printMovesWithFormattingHUD(const Weapon &playerWeapon){
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
            if (currentMoveDamage != 0 || currentMove.getName() == "Magic Missile")
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
            // if the move is Heal
            int healAmount =playerWeapon.getPlayerFaithModifier();
            if (healAmount < 0)
            {
                healAmount = 0;
            }
            leftString += std::to_string(healAmount) + " HP";
        }
        printWithFormattingHUD(leftString, "");
    }
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
            else if (currentMove.getName() == "Magic Missile")
            {
                leftString += std::to_string(currentMoveDamage);
                leftString += getStringForWeaponDamageType(playerWeapon.getDamageType()) + " dmg";
            }
            if (currentMove.getAmountOfChecks() != 0)
            {
                leftString += getStringForAmountOfChecks(playerWeapon.getMoves().at(i).getAmountOfChecks());
                leftString += " " + getStringForAttributeEnum(playerWeapon.getMoves().at(i).getUsedAttribute());
            }
        }
        else
        {
            // if the move is Heal
            int healAmount = playerWeapon.getPlayerFaithModifier();
            if (healAmount < 0)
            {
                healAmount = 0;
            }
            leftString += std::to_string(healAmount) + " HP";
        }
        
        // Enemy's NEXT INTENT MOVE display
        if (i == 0 && enemy.getHP() > 0)
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
            if (chosenMove.getName() == "Heal")
            {
                // if the move is Heal
                int healAmount = enemy.getFaith() - 70;
                if (healAmount < 0)
                {
                    healAmount = 0;
                }
                leftString += std::to_string(healAmount) + " HP";
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

// Camp
void Game::camp(){
    PrintSpeed currentPrintSpeed = fast;
    while (1)
    {
        clearScreen();
        printCharByChar(player.getName() + " HP: " + std::to_string(player.getHP()) + "/" + std::to_string(player.getHPMax()), currentPrintSpeed);
        displayCamp(currentPrintSpeed);
        getSmartInput("Select an <Action>: ");
        
        if (isSubset(input, "rest"))
        {
            printCharByChar("\n" + player.getName() + " rested to " + std::to_string(player.getHPMax()) + " HP!", fast);
            player.heal(player.getHPMax());
            std::cout << std::endl;
            getSmartInput();
            currentPrintSpeed = instant;
        }
        else if (isSubset(input, "level up"))
        {
            
            currentPrintSpeed = instant;
        }
        else if (isSubset(input, "visit campfire"))
        {
            shop();
            currentPrintSpeed = fast;
        }
        else if (isSubset(input, "continue"))
        {
            if (getContinueKey("Are you sure you want to leave camp? (Y/n): "))
            {
                break;
            }
        }
        else
        {
            printCharByChar("Please enter a valid <Action>\n", fast);
            getSmartInput();
            currentPrintSpeed = instant;
        }
    }
}
void Game::shop(){
    PrintSpeed currentPrintSpeed = fast;
    while (1)
    {
        clearScreen();
        printCharByChar("Souls: " + std::to_string(player.getSouls()));
        displayShop(currentPrintSpeed);
        getSmartInput("Select an <Action>: ");
        
        if (isSubset(input, "trade"))
        {
            printCharByChar("shopping!", fast);
            std::cout << std::endl;
            getSmartInput();
        }
        else if (isSubset(input, "go to tent"))
        {
            break;
        }
        else
        {
            printCharByChar("Please enter a valid <Action>\n", fast);
            getSmartInput();
        }
        currentPrintSpeed = instant;
    }
}

// Combat
void Game::engageInCombat(){
    determineWhoGoesFirst();
    while (player.getHP() > 0)
    {
        if (playerGoesFirst)
        {
            performPlayerMove();
            // Did the player run?
            if (playerRanFromFight)
            {
                runFromFight();
            }
            // or kill the enemy?
            else if (enemy.getHP() <= 0)
            {
                enemyDeathCleanUp();
                return;
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
            // did the player run
            if (playerRanFromFight)
            {
                runFromFight();
            }
            // or kill the enemy?
            else if (enemy.getHP() <= 0)
            {
                enemyDeathCleanUp();
                return;
            }
        }
        // if player killed enemy with a parry, check for that case
        if (enemy.getHP() <= 0)
        {
            enemyDeathCleanUp();
            return;
        }
    }
    printCharByChar("\n\nYou died...", slow);
    getSmartInput("");
    printGameOver();
}
void Game::performPlayerMove(){
    player.stopDodging();
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
                    continueKey = getContinueKey("Drink healing potion for " + std::to_string(player.getPotion().grade) + " HP? (Y/n): ");
                    if (continueKey == 'y')
                    {
                        std::cout << std::endl;
                        printCharByChar(player.getName() + " drank the " + lowercase(player.getPotion().name) + " potion!", fast);
                        pause();
                        printCharByChar("\n" + player.getName() + " healed " + std::to_string(player.heal(player.popPotion().grade)) + " HP", fast);
                        pause();
                        std::cout << std::endl;
                        getSmartInput();
                    }
                }
                else
                {
                    printCharByChar("You don't have a potion...");
                    pause();
                    std::cout << std::endl;
                    getSmartInput();
                }
            }
            // DODGE
            else if (isSubset(input, "dodge"))
            {
                // Confirm the user wants to dodge
                if (getContinueKey("Attempt to <Dodge> the enemy's next attack? (Y/n): ") == 'y')
                {
                    std::cout << std::endl;
                    player.startDodging();
                    printCharByChar(player.getName() + " is watching " + enemy.getName() + " carefully", fast);
                    pause();
                    printCharByChar("\n" + player.getName() + " will take 0 damage if " + enemy.getName() + " fails a [Check]...", fast);
                    pause();
                    enemy.exitStatus(parrying);
                    std::cout << std::endl;
                    getSmartInput();
                    return;
                }
            }
            else if (isSubset(input, "run"))
            {
                // Confirm the user wants to dodge
                if (getContinueKey("\nAttempt to <Run> from this fight? (Y/n): ") == 'y')
                {
                    // See if they succeed
                    int checksSucceeded = 0;
                    int randomNumberOutOf100 = rand() % 100;
                    printCharByChar(player.getName() + " tried to <Run>: ");
                    pause();
                    if (getCharacterAttributeValue(player, dexterity) > randomNumberOutOf100)
                    {
                        checksSucceeded += 1;
                        printCharByChar("[X]~", slow);
                    }
                    else
                    {
                        printCharByChar("[ ]~", slow);
                    }
                    randomNumberOutOf100 = rand() % 100;
                    pause();
                    if (getCharacterAttributeValue(player, dexterity) > randomNumberOutOf100)
                    {
                        checksSucceeded += 1;
                        printCharByChar("[X]", slow);
                    }
                    else
                    {
                        printCharByChar("[ ]", slow);
                    }
                    // DID THE PLAYER RUN?
                    if (checksSucceeded == 2)
                    {
                        printCharByChar("\nSuccess!", fast);
                        pause();
                        printCharByChar("\n\n" + player.getName() + " ran from the fight!");
                        playerRanFromFight = true;
                    }
                    else
                    {
                        printCharByChar("\nFailure...", fast);
                    }
                    pause();
                    std::cout << std::endl;
                    getSmartInput();
                    return;
                }
            }
            else if (isSubset(input, "drop weapon"))
            {
                if (player.getWeapon().getName() != "Unarmed")
                {
                    // Confirm the user wants to drop their weapon
                    if (getContinueKey("Are you sure you want to drop your weapon? (Y/n): ") == 'y')
                    {
                        // REALLY Confirm the user wants to drop their weapon
                        std::cout << std::endl;
                        if (getContinueKey("Just to double check, do you want to keep your weapon? (Y/n): ") == 'n')
                        {
                            std::cout << std::endl;
                            printCharByChar(player.getName() + " dropped the " + player.getWeapon().getName(), fast);
                            player.replaceWeapon(Weapon(unarmed));
                            pause();
                            std::cout << std::endl;
                            getSmartInput();
                        }
                    }
                }
                else
                {
                    printCharByChar("Please enter a valid move.\n");
                    getSmartInput();
                }
            }
            else
            {
                printCharByChar("Please enter a valid move.\n");
                getSmartInput();
            }
        }
        else // IF A VALID <MOVE> HAS BEEN PICKED
        {
            WeaponMove chosenMove = player.getWeapon().getMoves().at(chosenMoveIndex);
            // Confirm weapon move
            continueKey = getContinueKey("Perform <" + chosenMove.getName() + ">? (Y/n): ");
            if (continueKey == 'y')
            {
                // IF THE USER CONFIRMS THE <MOVE>
                std::cout << std::endl;
                setupWeaponMoveDamageAsCharacter1ToCharacter2(player, enemy, chosenMove);
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
    
    // Passing the turn back to the Player
    enemy.exitStatus(parrying);
}
void Game::performEnemyMove(){
    
    // Display HUD
    displayHUD(player, enemy);
    
    // What the enemy move choice is
    WeaponMove chosenMove = enemy.getChosenMove();
    enemy.chooseNewMove();
    
    // Using enemy move
    setupWeaponMoveDamageAsCharacter1ToCharacter2(enemy, player, chosenMove);
    getSmartInput();
    
    // Passing the turn back to the Player
    player.exitStatus(parrying);
}
void Game::setupWeaponMoveDamageAsCharacter1ToCharacter2(Character &character1, Character &character2, const WeaponMove chosenMove){
    std::string spacing = "\n";
    if (chosenMove.getDamagePercentage() != 0) // IF THE MOVE DOES DAMAGE
    {
        int damageDealt = 0;
        
        // FIGURE OUT HOW MUCH DMG TO DO TO CHARACTER_2
        
        if (chosenMove.getAmountOfChecks() > 0) // IF THERE ARE CHECKS
        {
            int checksSucceeded = rollWeaponChecks(character1, chosenMove);
            // is the enemy attacking the player?
            if (character1.getAsciiArt() == enemy.getAsciiArt()) // this will only be true if it is currently the enemy's move
            {
                // check to see if the player is dodging
                if (player.isDodging())
                {
                    // now check to see if the enemy missed a: [X]
                    if (checksSucceeded < chosenMove.getAmountOfChecks())
                    {
                        // PLAYER DODGED
                        pause();
                        printCharByChar("\n" + player.getName() + " dodged the attack!", fast);
                        pause();
                        std::cout << std::endl;
                        return;
                    }
                    else
                    {
                        std::cout << std::endl;
                        pause();
                        printCharByChar(player.getName() + " couldn't dodge the attack", fast);
                        pause();
                        std::cout << std::endl;
                    }
                }
            }
            // now deal the damage from success of checks
            damageDealt = character1.getWeapon().getDamage(chosenMove) * ((static_cast<double>(checksSucceeded) / chosenMove.getAmountOfChecks()));
            // Assassinate pierces armor
            if (chosenMove.getName() == "Assassinate" && damageDealt > 0)
            {
                damageDealt += character2.getArmor();
                printCharByChar("\nThe attack ignored your Armor!");
            }
            pause();
        }
        else // IF THERE ARE NO CHECKS
        {
            spacing = "";
            // is the enemy attacking the player?
            if (character1.getAsciiArt() == enemy.getAsciiArt()) // this will only be true if it is currently the enemy's move
            {
                // check to see if the player is dodging
                if (player.isDodging())
                {
                    pause();
                    printCharByChar(player.getName() + " can't dodge an infallible attack", fast);
                    pause();
                    std::cout << std::endl;
                }
            }
            damageDealt = character1.getWeapon().getDamage(chosenMove);
        }
        
        // Spacing
        std::cout << spacing;
        
        // DEAL THE DAMAGE DEALT
        finishDamageDealt(character1, character2, damageDealt);
    }
    else // IF THE MOVE DOES NO DAMAGE (SOMETHING SPECIAL)
    {
        pause();
        if (chosenMove.getName() == "Heal")
        {
            // HEAL
            int healAmount = (character1.getFaith() - 70) < 0 ? 0 : (character1.getFaith() - 70);
            printCharByChar(character1.getName() + " casted <Heal>!", fast);
            pause();
            printCharByChar("\n" + character1.getName() + " healed " + std::to_string(character1.heal(healAmount)) + " HP", fast);
        }
        else if (chosenMove.getName() == "Spellshield")
        {
            // SPELLSHIELD
            int checksSucceeded = rollWeaponChecks(character1, chosenMove);
            if (checksSucceeded == chosenMove.getAmountOfChecks())
            {
                character1.enterStatus(spellshield);
                printCharByChar("\nSuccess!", fast);
                pause();
                printCharByChar("\n" + character1.getName() + " is now Spellshielded!", fast);
            }
            else
            {
                printCharByChar("\nFailure...", fast);
            }
        }
        else if (chosenMove.getName() == "Oakskin")
        {
            // OAKSKIN
            int checksSucceeded = rollWeaponChecks(character1, chosenMove);
            if (checksSucceeded == chosenMove.getAmountOfChecks())
            {
                character1.enterStatus(oakskin);
                printCharByChar("\nSuccess!", fast);
                pause();
                printCharByChar("\n" + character1.getName() + " now has Oakskin!", fast);
            }
            else
            {
                printCharByChar("\nFailure...", fast);
            }
        }
        else if (chosenMove.getName() == "Riposte")
        {
            // PARRY
            int checksSucceeded = rollWeaponChecks(character1, chosenMove);
            if (checksSucceeded == chosenMove.getAmountOfChecks())
            {
                character1.enterStatus(parrying);
                printCharByChar("\nSuccess!", fast);
                pause();
                printCharByChar("\n" + character1.getName() + " will attempt to parry the enemy's next attack!", fast);
            }
            else
            {
                printCharByChar("\nFailure...", fast);
            }
        }
    }
    pause();
    std::cout << std::endl;
}
void Game::finishDamageDealt(Character &character1, Character &character2, int damageDealt){
    if (character1.getWeapon().getDamageType() == physical)
    {
        int actualDamageDealt = damageDealt - character2.getArmor();
        if (actualDamageDealt <= 0)
        {
            actualDamageDealt = 0;
        }
        if (character2.getStatus() == parrying && actualDamageDealt != 0)
        {
            character1.takeDamage(actualDamageDealt);
            printCharByChar(character2.getName() + " parried!", fast);
            pause();
            std::cout << std::endl;
            printCharByChar(std::to_string(actualDamageDealt));
            pause();
            printCharByChar(" damage was dealt to " + character1.getName() + " instead", fast);
        }
        else
        {
            character2.takeDamage(actualDamageDealt);
            printCharByChar(character1.getName() + " dealt ", fast);
            pause();
            printCharByChar(std::to_string(actualDamageDealt));
            pause();
            printCharByChar(" damage", fast);
        }
    }
    else // if magic damage
    {
        int actualDamageDealt = damageDealt - character2.getResistance();
        if (actualDamageDealt <= 0)
        {
            actualDamageDealt = 0;
        }
        if (character2.getStatus() == parrying && actualDamageDealt != 0)
        {
            character1.takeDamage(actualDamageDealt);
            printCharByChar(character2.getName() + " parried!", fast);
            pause();
            std::cout << std::endl;
            printCharByChar(std::to_string(actualDamageDealt));
            pause();
            printCharByChar(" magic damage was dealt to " + character1.getName() + " instead", fast);
        }
        else
        {
            character2.takeDamage(actualDamageDealt);
            printCharByChar(character1.getName() + " dealt ", fast);
            pause();
            printCharByChar(std::to_string(actualDamageDealt));
            pause();
            printCharByChar(" magic damage", fast);
        }
    }
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
        if ((player.getSouls() + floor + enemy.getIntelligence() + player.getName().length()) % 2 == 0)
        {
            playerGoesFirst = true;
        }
        else
        {
            playerGoesFirst = false;
        }
    }
}
void Game::enemyDeathCleanUp(){
    // CLEAR STATUS
    player.exitStatus();
    
    // DISPLAY HUD
    displayHUD(player, enemy);
    pause();
    
    // "DEFEATED ENEMY"
    printCharByChar("You defeated " + enemy.getName() + "!", fast);
    enemyTypesSeen.insert(enemy.getType());
    floor++;
    createNewEnemy();
    pause();
    
    // "HARVESTED SOULS"
    int soulsHarvested = enemy.retrieveSoulsHeld();
    printCharByChar("\nSouls harvested: ", fast);
    pause();
    printCharByChar(std::to_string(enemy.retrieveSoulsHeld()));
    player.addSouls(soulsHarvested);
    pause();
    std::cout << std::endl;
    
    // "YOU FOUND LOOT"
    unsigned short valueThatPicksItemDropped = rand() % 100;
    unsigned short valueThatPicksWeaponDropped = rand() % 100;
    
    // ITEM GRADE ALGORITHM
    int newItemGrade = floor + (rand() % (floor - (floor / 2) + 2)) - (rand() % (floor - (floor / 2) + 2));
    if (newItemGrade < 1)
    {
        newItemGrade = 1;
    }
    
    // WEAPON
    if (valueThatPicksWeaponDropped < 75)
    {
        Weapon newWeapon = Weapon(randomized, newItemGrade);
        printCharByChar("\nYou found a weapon!", fast);
        pause();
        printCharByChar("\n-" + newWeapon.getName() + ":\n", fast);
        printMovesWithFormattingHUD(newWeapon);
        pause();
        if (getContinueKey("\nDo you want to replace your " + player.getWeapon().getName() + " (Grade " + std::to_string(player.getWeapon().getGrade()) + ") with " + newWeapon.getName() + " (Grade " + std::to_string(newWeapon.getGrade()) + ")? (Y/n): ") == 'y')
        {
            player.replaceWeapon(newWeapon);
        }
    }
    
    // ITEMS
    if (valueThatPicksItemDropped < 75)
    {
        // POTION
        if (valueThatPicksItemDropped < 25)
        {
            int newPotionGrade = floor + static_cast<int>(enemy.getType()) + (player.getHPMax() / player.getHP()) + (rand() % (floor * (floor / 2) + 1)) + 1;
            Potion newPotion = Potion("Healing", newPotionGrade);
            printCharByChar("\nYou found a Grade " + std::to_string(newPotion.grade) + ", Healing Potion!", fast);
            pause();
            // Confirm drinking potion
            char continueKey = ' ';
            if (player.getPotion().name == "None")
            {
                continueKey = getContinueKey("\nDo you want this potion? (Y/n): ");
            }
            else
            {
                continueKey = getContinueKey("\nSwap out the potion you currently have? (Y/n): ");
            }
            if (continueKey == 'y')
            {
                if (player.getPotion().grade != 0 && player.getHP() < player.getHPMax())
                {
                    if (getContinueKey("\nDo you want to drink your current potion for " + std::to_string(player.getPotion().grade) + " HP? (Y/n): ") == 'y')
                    {
                        printCharByChar(player.getName() + " drank the " + lowercase(player.getPotion().name) + " potion!", fast);
                        pause();
                        printCharByChar("\n" + player.getName() + " healed " + std::to_string(player.heal(player.popPotion().grade)) + " HP", fast);
                        pause();
                    }
                }
                printCharByChar("\nYou took the Grade " + std::to_string(newPotion.grade) + ", Healing Potion!", fast);
                player.replacePotion(newPotion);
                std::cout << std::endl;
            }
        }
        // APPAREL
        else if (valueThatPicksItemDropped < 50)
        {
            Apparel newApparel = Apparel("Apparel", newItemGrade);
            printCharByChar("\nYou found Apparel with " + std::to_string(newApparel.grade) + " Armor!", fast);
            printCharByChar("\nYou currently have Apparel with " + std::to_string(player.getArmor()) + " Armor.", fast);
            pause();
            if (getContinueKey("\nSwap out what you're currently wearing? (Y/n): ") == 'y')
            {
                player.replaceApparel(newApparel);
            }
        }
        // CLOAK
        else
        {
            Cloak newCloak = Cloak("Cloak", newItemGrade);
            printCharByChar("\nYou found a Cloak with " + std::to_string(newCloak.grade) + " Resist!", fast);
            printCharByChar("\nYou currently have a Cloak with " + std::to_string(player.getResistance()) + " Resist.", fast);
            pause();
            if (getContinueKey("\nSwap out what you're currently wearing? (Y/n): ") == 'y')
            {
                player.replaceCloak(newCloak);
            }
        }
    }
    
    // "NEXT FLOOR SEE"
    std::cout << std::endl;
    printCharByChar("In the next floor you see ", fast);
    pause();
    printCharByChar(enemy.getName() + "!");
    pause();
    
    // CHECK IF PLAYER WANTS TO USE POTION
    if (player.getPotion().grade != 0 && player.getHP() < player.getHPMax())
    {
        // Confirm drinking potion
        if (getContinueKey("\nWould you like to drink your healing potion for " + std::to_string(player.getPotion().grade) + " HP? (Y/n): ") == 'y')
        {
            printCharByChar(player.getName() + " drank the " + lowercase(player.getPotion().name) + " potion!", fast);
            pause();
            printCharByChar("\n" + player.getName() + " healed " + std::to_string(player.heal(player.popPotion().grade)) + " HP", fast);
            pause();
        }
    }
    
    // "CONTINUE"
    enemyIsPrinted = false;
    std::cout << std::endl;
    getSmartInput();
}
void Game::runFromFight(){
    
    // CLEAR STATUS
    player.exitStatus();
    playerRanFromFight = false;
    
    // DISPLAY HUD
    displayHUD(player, enemy);
    pause();
    
    // "ESCAPED ENEMY"
    printCharByChar("You escaped from " + enemy.getName() + "!", fast);
    enemyTypesSeen.insert(enemy.getType());
    createNewEnemy();
    pause();
    
    // "NEXT FLOOR SEE"
    std::cout << std::endl;
    printCharByChar("In the next floor you see ", fast);
    pause();
    floor++;
    printCharByChar(enemy.getName() + "!");
    pause();
    
    // "CONTINUE"
    enemyIsPrinted = false;
    std::cout << std::endl;
    getSmartInput();
}
void Game::createNewEnemy(){
    int chosenEnemyIndex = 0;
    if (floor <= TOTAL_ENEMY_TYPES)
    {
        chosenEnemyIndex = floor;
    }
    else
    {
        chosenEnemyIndex = rand() % (TOTAL_ENEMY_TYPES + 1);
    }
    EnemyType newEnemyType = static_cast<EnemyType>(chosenEnemyIndex);
    enemy = Enemy(newEnemyType, floor);
    if (playerPrintSpeed == instant)
    {
        // Change Print Speed
        std::set<EnemyType>::iterator it = enemyTypesSeen.find(enemy.getType());
        if (it != enemyTypesSeen.end()) {
            // Enemy type is in the set
            playerPrintSpeed = faster;
        } else {
            // Enemy type is not in the set
            playerPrintSpeed = fast;
        }
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
int Game::rollWeaponChecks(Character &character, const WeaponMove chosenMove){
    int checksSucceeded = 0;
    int randomNumberOutOf100 = rand() % 100;
    printCharByChar(character.getName() + " used <" + chosenMove.getName() + ">: ");
    for (size_t i = 0; i < chosenMove.getAmountOfChecks() - 1; i++)
    {
        pause();
        if (getCharacterAttributeValue(character, chosenMove.getUsedAttribute()) > randomNumberOutOf100)
        {
            checksSucceeded += 1;
            printCharByChar("[X]", slow);
        }
        else
        {
            printCharByChar("[ ]", slow);
        }
        printCharByChar("~");
        randomNumberOutOf100 = rand() % 100;
    }
    pause();
    if (getCharacterAttributeValue(character, chosenMove.getUsedAttribute()) > randomNumberOutOf100)
    {
        checksSucceeded += 1;
        printCharByChar("[X]", slow);
    }
    else
    {
        printCharByChar("[ ]", slow);
    }
    return checksSucceeded;
}
