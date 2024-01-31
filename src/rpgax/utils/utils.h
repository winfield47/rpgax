//
//  Utils.hpp
//  rpgax
//
//  Created by Kyle Winfield Burnham on 1/16/24.
//

#ifndef utils_h
#define utils_h

#include <string>

enum OptionSelectHUD
{
    addPipes, addVersus, addNothing
};

enum PrintSpeed
{
    instant = 0, lightning = 1, faster = 10, fast = 25, normal = 50, slow = 75
};

// Display
void clearScreen();
unsigned int printCharByChar(const std::string&, const PrintSpeed milliseconds = normal);
void pause(const double seconds = 0.5);

// User Input
char getContinueKey(const std::string& = "Continue? (Y/n): ");
std::string getLineFromPrompt(const std::string&);

// String Manipulation
char lowercase(const char);
std::string lowercase(const std::string&);
char uppercase(char);
std::string uppercase(const std::string&);
std::string capitalize(const std::string&);
std::string getFirstWord(const std::string&);
bool isSubset(const std::string&, const std::string&);
bool isInt(const std::string&);
int charToInt(const char&);

#endif /* Utils_hpp */
