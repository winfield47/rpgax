//
//  Game.hpp
//  rpgax
//
//  Created by Kyle Winfield Burnham on 1/27/24.
//

#ifndef game_h
#define game_h

#include "../utils/utils.h"
#include "player.h"
#include "enemy.h"
#include <set>

class Game
{
private:
    // Properties
    static std::string input;
    static Player player;
    static Enemy enemy;
    static std::set<EnemyType> enemyTypesSeen;
    static std::deque<Weapon> shopWeapons;
    static short floor;
    static short lastCampFloor;
    static bool playerGoesFirst;
    static bool playerIsPrinted;
    static bool enemyIsPrinted;
    static bool playerRanFromFight;
    static bool nextFloorIsCamp;
    static bool playerHasNotRestedYet;
    static bool playerHasNotTradedYet;
    static PrintSpeed playerPrintSpeed;
    static PrintSpeed universalPrintSpeed;
    
public:
    // Constructors
    Game();
    Game(const Player&);
    Game(const Player&, const Enemy&);
    
    // User Input
    void getSmartInput(const std::string& = "\nContinue...");
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
    void printIntroductionParagraph(PrintSpeed);
    void displayOrigin(const Player&, bool);
    void displayCamp(PrintSpeed);
    void displayShop(PrintSpeed, std::deque<Weapon>);
    void displayLevelUpScreen(PrintSpeed);
    void displayHUD(const Player&, const Enemy&);
    void printWithFormattingHUD(const std::string&, const std::string&, const OptionSelectHUD optionSelectHUD = addNothing);
    void printMovesWithFormattingHUD(const Weapon&);
    void printMovesWithFormattingHUD(const Weapon&, const Enemy&);
    void printGameOver();
    
    // Game Loop
    void play();
    
    // Camp
    void camp();
    void ingestSouls();
    void trade();
    void makeShopItems();
    
    // Combat
    void engageInCombat();
    void performPlayerMove();
    void performEnemyMove();
    void setupWeaponMoveDamageAsCharacter1ToCharacter2(Character&, Character&, const WeaponMove);
    void finishDamageDealt(Character&, Character&, int);
    void determineWhoGoesFirst();
    void enemyDeathCleanUp();
    void runFromFight();
    void createNewEnemy();
    int getCharacterAttributeValue(const Character&, const WeaponMoveAttribute);
    int rollWeaponChecks(Character&, const WeaponMove);
};

#endif /* Game_hpp */
