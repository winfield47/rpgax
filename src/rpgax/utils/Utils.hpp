//
//  Utils.hpp
//  rpgax
//
//  Created by Kyle Winfield Burnham on 1/16/24.
//

#ifndef Utils_hpp
#define Utils_hpp

#include "../core/Player.hpp"
#include <string>

// Loops
void mainLoop();

// General
void psuedoClearScreen();
char getContinueKey(const std::string& = "Continue? (y/n): ");
char lowercase(const char);
std::string lowercase(const std::string&);
std::string getLineFromPrompt(const std::string&);
bool isSubset(const std::string&, const std::string&);

// Game
void displayHUD(const Player&);
void displayHUD(Player, Character);
Origin getOriginFromPrompt(std::string = "Inspect Origin: ");
Player createNewPlayer();

#endif /* Utils_hpp */
