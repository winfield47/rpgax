//
//  Items.hpp
//  rpgax
//
//  Created by Kyle Winfield Burnham on 1/19/24.
//

#ifndef Items_hpp
#define Items_hpp

#include <string>

struct Apparel
{
    // Properties
    std::string name;
    int grade;
    // Constructors
    Apparel() : name(""), grade(0) {}
    Apparel(const std::string& n, int g) : name(n), grade(g) {}
};

struct Cloak
{
    // Properties
    std::string name;
    int grade;
    // Constructors
    Cloak() : name(""), grade(0) {}
    Cloak(const std::string& n, int g) : name(n), grade(g) {}
};

struct Potion
{
    // Properties
    std::string name;
    int grade;
    // Constructors
    Potion() : name(""), grade(0) {}
    Potion(const std::string& n, int g) : name(n), grade(g) {}
};

#endif /* Items_hpp */
