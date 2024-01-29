//
//  Items.hpp
//  rpgax
//
//  Created by Kyle Winfield Burnham on 1/19/24.
//

#ifndef items_h
#define items_h

#include <string>

struct Apparel
{
    // Properties
    std::string name;
    int grade;
    // Constructors
    Apparel() : name("None"), grade(0) {}
    Apparel(const std::string& n, int g) : name(n), grade(g) {}
};

struct Cloak
{
    // Properties
    std::string name;
    int grade;
    // Constructors
    Cloak() : name("None"), grade(0) {}
    Cloak(const std::string& n, int g) : name(n), grade(g) {}
};

struct Potion
{
    // Properties
    std::string name;
    int grade;
    // Constructors
    Potion() : name("None"), grade(0) {}
    Potion(const std::string& n, int g) : name(n), grade(g) {}
};

#endif /* Items_hpp */
