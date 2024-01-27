//
//  Utils.cpp
//  rpgax
//
//  Created by Kyle Winfield Burnham on 1/16/24.
//

#include "Utils.hpp"
#include <iostream>
#include <iomanip>
using namespace std;

// DISPLAY
void psuedoClearScreen(){
    for (size_t i = 0; i < 20; i++)
    {
        cout << "\n";
    }
    cout << endl;
}

// USER INPUT
char getContinueKey(const string &prompt){
    char input;
    bool good;
    
    do {
        cout << prompt;
        cin >> input;
        
        if (cin)
        {
            if (input == 'y' || input == 'n' || input == 'Y' || input == 'N')
            {
                good = true;
            }
            else
            {
                good = false;
                cout << "Please use 'y' or 'n' to answer." << endl;
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else
        {
            good = false;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "That doesn't make sense!" << endl;
        }
    } while (!good);
    
    cout << endl;
    return input;
}
string getLineFromPrompt(const string &prompt){
    string line;
    cout << prompt;
    getline(cin, line);
    if (cin.bad())
    {
        cout << "You broke the code!" << endl;
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
string lowercase(const string &str){
    string lowerStr = "";
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
string uppercase(string str){
    string upperStr = "";
    for (char c: str)
    {
        upperStr += uppercase(c);
    }
    
    return upperStr;
}
string capitalize(string str){
    str[0] = uppercase(str[0]);
    return str;
}
string getFirstWord(string str){
    string returnString = "";
    for (char c: str)
    {
        if (c == ' ')
        {
            break;
        }
        returnString += c;
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
