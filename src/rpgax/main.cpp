//
//  main.cpp
//  rpgax
//
//  Created by Kyle Winfield Burnham on 1/11/24.
//

#include <iostream>
#include "utils/Utils.hpp"
using namespace std;

int main()
{
    srand(static_cast<unsigned int>(time(NULL)));
    mainLoop();
    return 0;
}
