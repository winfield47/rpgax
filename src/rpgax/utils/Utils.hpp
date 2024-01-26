//
//  Utils.hpp
//  rpgax
//
//  Created by Kyle Winfield Burnham on 1/16/24.
//

#ifndef Utils_hpp
#define Utils_hpp

#include "../core/Player.hpp"
#include "../core/Enemy.hpp"
#include <string>

enum OptionSelectHUD
{
    addPipes, addVersus, addNothing
};

// Display
void psuedoClearScreen();
void displayHUD(const Player&);
void displayHUD(const Player&, const Enemy&);
void printWithFormattingHUD(const std::string&, const std::string&, const OptionSelectHUD optionSelectHUD = addNothing);
void printMovesWithFormattingHUD(const Weapon&, const Enemy&);

// User Input
char getContinueKey(const std::string& = "Continue? (y/n): ");
std::string getLineFromPrompt(const std::string&);

// String Manipulation
char lowercase(const char);
std::string lowercase(const std::string&);
bool isSubset(const std::string&, const std::string&);

// Game
Origin getOriginFromPrompt(std::string = "Inspect Origin: ");
Player createNewPlayer();
std::string getStringHpAmrRes(const Character&);
std::string getStringAttributes(const Character&);
std::string getStringForAttributeEnum(const int);
std::string getStringForAmountOfChecks(const int);
std::string getStringForWeaponDamageType(const int, const bool = false);

#endif /* Utils_hpp */
