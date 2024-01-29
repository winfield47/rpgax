#!/bin/bash

# Compile C++ files
cd src/rpgax/
g++ -o ../rpgax.out -std=c++11 core/weaponmove.cpp core/weapon.cpp core/character.cpp core/player.cpp core/enemy.cpp utils/utils.cpp utils/game.cpp utils/mainloop.cpp main.cpp
cd ../../

# Check if compilation was successful
if [ $? -eq 0 ]; then
    # Run the generated a.out file
    src/./rpgax.out
else
    echo "Compilation failed. Exiting."
fi

