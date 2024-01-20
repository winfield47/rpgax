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

void mainLoop();
void gameLoop();
void psuedoClearScreen();
char getContinueKey(std::string = "Continue? (y/n): ");
char lowercase(char);
std::string lowercase(std::string);
std::string getLineFromPrompt(std::string);
Origin getOrigin(std::string = "Select Origin: ");
Player createNewPlayer();

#endif /* Utils_hpp */
