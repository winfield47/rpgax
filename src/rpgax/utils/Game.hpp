//
//  Game.hpp
//  rpgax
//
//  Created by Kyle Winfield Burnham on 1/27/24.
//

#ifndef Game_hpp
#define Game_hpp

#include "Utils.hpp"

class Game
{
public:
    // Properties
    static std::string input;
    static Player player;
    static Enemy enemy;
    static short floor;
    static bool playerGoesFirst;
    static bool playerIsPrinted;
    static bool enemyIsPrinted;
    static PrintSpeed playerPrintSpeed;
    static PrintSpeed universalPrintSpeed;
    
    // Constructors
    Game();
    Game(const Player&);
    Game(const Player&, const Enemy&);
    
    // User Input
    void getSmartInput(const std::string& = "Continue...");
    void createNewPlayer();
    Origin getOriginFromPrompt(std::string = "Choose an origin to inspect: ");
    
    // Property-to-String Converters
    std::string getStringHpAmrRes(const Character&);
    std::string getStringAttributes(const Character&);
    std::string getStringForAttributeEnum(const int);
    std::string getStringForAmountOfChecks(const int);
    std::string getStringForWeaponDamageType(const int, const bool = false);
    std::string getStringForOrigin(const Origin);
    
    // Display
    void displayHUD(const Player&);
    void displayHUD(const Player&, const Enemy&);
    void printWithFormattingHUD(const std::string&, const std::string&, const OptionSelectHUD optionSelectHUD = addNothing);
    void printMovesWithFormattingHUD(const Weapon&, const Enemy&);
    
    // Combat
    void engageInCombat();
    void performPlayerMove();
    void performEnemyMove();
    void determineWhoGoesFirst();
    void enemyDeathCleanUp();
    void createNewEnemy();
};

#endif /* Game_hpp */
