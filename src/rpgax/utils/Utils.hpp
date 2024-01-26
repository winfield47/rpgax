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

#endif /* Utils_hpp */
