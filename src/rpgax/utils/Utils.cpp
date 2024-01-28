//
//  Utils.cpp
//  rpgax
//
//  Created by Kyle Winfield Burnham on 1/16/24.
//

#include "Utils.hpp"
#include <iostream>
#include <iomanip>
#include <stdlib.h>

// DISPLAY
void clearScreen(){
    // If neither of the clear functions DONT work, they will go in the if statements
    if (system("clear"))
    {
        if (system("cls"))
        {
            // back up clear function
            for (size_t i = 0; i < 20; i++)
            {
                std::cout << "\n";
            }
            std::cout << std::endl;
        }
    }
}

// USER INPUT
char getContinueKey(const std::string &prompt){
    std::string input;
    while (true)
    {
        input = lowercase(getFirstWord(getLineFromPrompt(prompt)));
        if (input == "y" || input == "")
        {
            std::cout << std::endl;
            return 'y';
        }
        else if (input == "n")
        {
            std::cout << std::endl;
            return 'n';
        }
        else
        {
            std::cout << "Please use 'y' or 'n' to answer." << std::endl;
        }
    }
}
std::string getLineFromPrompt(const std::string &prompt){
    std::string line;
    std::cout << prompt;
    getline(std::cin, line);
    if (std::cin.bad())
    {
        std::cout << "You broke the code!" << std::endl;
        return "";
    }
    return line;
}

// STRING MANIPULATION
char lowercase(const char c){
    char lowerChar;
    if (c <= 'Z' && c >= 'A')
    {
        lowerChar = c + ('a' - 'A');
    }
    else
    {
        lowerChar = c;
    }
    return lowerChar;
}
std::string lowercase(const std::string &str){
    std::string lowerStr = "";
    for (char c: str)
    {
        lowerStr += lowercase(c);
    }
    
    return lowerStr;
}
char uppercase(char c){
    char upperChar;
    if (c <= 'z' && c >= 'a')
    {
        upperChar = c - ('a' - 'A');
    }
    else
    {
        upperChar = c;
    }
    return upperChar;
}
std::string uppercase(std::string str){
    std::string upperStr = "";
    for (char c: str)
    {
        upperStr += uppercase(c);
    }
    
    return upperStr;
}
std::string capitalize(std::string str){
    str[0] = uppercase(str[0]);
    return str;
}
std::string getFirstWord(std::string str){
    std::string returnString = "";
    bool isPastBeginningWhiteSpace = false;
    for (char c: str)
    {
        if (!isPastBeginningWhiteSpace)
        {
            if (c != ' ')
            {
                isPastBeginningWhiteSpace = true;
                returnString += c;
            }
        }
        else
        {
            if (c == ' ')
            {
                break;
            }
            returnString += c;
        }
    }
    return returnString;
}
bool isSubset(const std::string &stringInQuestion, const std::string &superString){
    bool currentCharIsInSuperString = false;
    for (char subChar : stringInQuestion)
    {
        currentCharIsInSuperString = false;
        for (char superChar : superString)
        {
            if (subChar == superChar)
            {
                currentCharIsInSuperString = true;
                break;
            }
        }
        if (!currentCharIsInSuperString)
        {
            return false;
        }
    }
    
    return true;
}
