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
    
    // Constructors
    Game();
    Game(Player, Enemy);
    
    // User Input
    void getSmartInput(const std::string&);
    void createNewPlayer();
    Origin getOriginFromPrompt(std::string = "Inspect Origin: ");
    
    // Property-to-String Converters
    std::string getStringHpAmrRes(const Character&);
    std::string getStringAttributes(const Character&);
    std::string getStringForAttributeEnum(const int);
    std::string getStringForAmountOfChecks(const int);
    std::string getStringForWeaponDamageType(const int, const bool = false);
    
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
};

#endif /* Game_hpp */
