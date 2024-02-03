//
//  Enemy.cpp
//  rpgax
//
//  Created by Kyle Winfield Burnham on 1/25/24.
//

#include "enemy.h"

// Constructors
Enemy::Enemy(){}
Enemy::Enemy(EnemyType type, int floorLevel){
    this->type = type;
    this->floorLevel = floorLevel;
    status = nostatus;
    variance = 3;
    int variant = 0;
    switch (type)
    {
        case bird:
            variant = rand() % 3;
            switch (variant) {
                case 0:
                    asciiArt = "<@\\";
                    name = "Pigeon";
                    description = "A bigger, weirdly muscular pigeon!";
                    weapon = Weapon(unarmed);
                    strength = 62;
                    dexterity = 50;
                    intelligence = 50;
                    faith = 50;
                    armor = 0;
                    resistance = 0;
                    break;
                case 1:
                    asciiArt = "<¢\\"; // ¡™£¢∞§¶•ªº–≠œ∑´®†¥¨ˆøπ“‘«åß∂ƒ©˙∆˚¬…æΩ≈ç√∫˜µ≤≥÷⁄€‹›ﬁﬂ‡°·‚—±Œ„´‰ˇÁ¨ˆØ∏”’»ÅÍÎÏ˝ÓÔÒÚÆ¸˛Ç◊ı˜Â¯˘¿``
                    name = "Crow";
                    description = "A crow with Ray-Bans!";
                    weapon = Weapon(unarmed, floorLevel / 2);
                    strength = 60;
                    dexterity = 71;
                    intelligence = 50;
                    faith = 50;
                    armor = 0;
                    resistance = 0;
                    break;
                case 2:
                    asciiArt = "∑C\\";
                    name = "Raven";
                    description = "A raven standing on a spellbook!";
                    intelligence = 74;
                    weapon.setEnemyIntelligenceModifier(intelligence);
                    weapon = Weapon(ravenbook, floorLevel / 10);
                    strength = 61;
                    dexterity = 50;
                    faith = 50;
                    armor = 0;
                    resistance = 0;
                    break;
                default:
                    throw "creating bird bad case";
            }
            break;
        case goblin:
            asciiArt = "\\g\\";
            name = "Goblin";
            description = "A goblin trying to rob you of your life!";
            weapon = Weapon(dagger, floorLevel);
            strength = 63;
            dexterity = 74;
            intelligence = 65;
            faith = 70;
            armor = 0;
            resistance = 0;
            break;
        case drow:
            if (rand() % 2 == 0)
            {
                asciiArt = "}0{";
                name = "Drow Mage";
                description = "A dark elf mage with a funny hat!";
                weapon = Weapon(magicstaff, floorLevel);
                strength = 63;
                dexterity = 67;
                intelligence = 70;
                faith = 65;
                armor = 0;
                resistance = 1;
            }
            else
            {
                asciiArt = "^0^";
                name = "Drow Ranger";
                description = "A dark elf woodsman with a feather hat!";
                weapon = Weapon(bow, floorLevel);
                strength = 64;
                dexterity = 70;
                intelligence = 65;
                faith = 68;
                armor = 0;
                resistance = 0;
            }
            break;
        case clergyman:
            if (rand() % 2 == 0)
            {
                asciiArt = "/+\\";
                name = "Holy Knight";
                description = "A slightly emaciated paladin!";
                weapon = Weapon(lightningspear, floorLevel);
                strength = 64;
                dexterity = 63;
                intelligence = 69;
                faith = 72;
                armor = 4;
                resistance = 1;
            }
            else
            {
                asciiArt = "†O\\";
                name = "Cleric";
                description = "A slightly pudgy priest eating rations!";
                weapon = Weapon(talisman, floorLevel);
                strength = 63;
                dexterity = 64;
                intelligence = 71;
                faith = 74;
                armor = 0;
                resistance = 4;
            }
            break;
        case ghoul:
            asciiArt = "•∆•";
            name = "Ghoul";
            description = "A corpse walking around like it owns place!";
            weapon = Weapon(ghoulweapon, floorLevel - 2);
            strength = 63;
            dexterity = 72;
            intelligence = 40;
            faith = 0;
            armor = 0;
            resistance = 1;
            break;
        default:
            variance = 0;
            asciiArt = "\\ø/";
            name = "Enemy";
            description = "A lowly enemy… nothing but a foot soldier.";
            weapon = Weapon(unarmed);
            strength = 60;
            dexterity = 60;
            intelligence = 60;
            faith = 60;
            armor = 0;
            resistance = 0;
            break;
    }
    varyStats();
    
    hpMax = hp = (20 + ((floorLevel + 1) * 1.5) + (strength - (70 + (floorLevel / 2))) * 2) - (rand() % (1 + floorLevel / 2));
    if (hpMax <= 0) { hpMax = hp = 1; }
    
    weapon.setEnemyIntelligenceModifier(intelligence);
    weapon.setEnemyFaithModifier(faith);
    chooseNewMove();
}
void Enemy::varyStats(){
    if (floorLevel > 0)
    {
        int maxValue = floorLevel + 1;
        int randomValueForArmor = rand();
        int randomValueForResistance = rand();
        armor += ((randomValueForArmor % maxValue) - rand() % maxValue) <= 0 ? 0 : (randomValueForArmor % maxValue);
        resistance += ((randomValueForResistance % maxValue) - rand() % maxValue) <= 0 ? 0 : (randomValueForResistance % maxValue);
    }
    int strengthVariance = (rand() % ((floorLevel / 2) + 1)) + ((rand() % variance) / 2) - ((rand() % variance) / 2);
    int dexterityVariance = (rand() % ((floorLevel / 2) + 1)) + (rand() % variance) - (rand() % variance);
    int intelligenceVariance = (rand() % ((floorLevel / 2) + 1)) + (rand() % variance) - (rand() % variance);
    int faithVariance = (rand() % ((floorLevel / 2) + 1)) + (rand() % variance) - (rand() % variance);
    strength += strengthVariance;
    dexterity += dexterityVariance;
    intelligence += intelligenceVariance;
    faith += faithVariance;
} // This helps the constructor look prettier

// Accessors
std::string Enemy::getName() const{
    return name;
}
EnemyType Enemy::getType() const{
    return type;
}
WeaponMove Enemy::getChosenMove(){
    chosenMove = weapon.getMoves().at(chosenMoveIndex);
    return chosenMove;
}
int Enemy::retrieveSoulsHeld(){
    int soulsRetrieved = (type * 2) + floorLevel;
    if (soulsRetrieved == 0)
    {
        return 1;
    }
    else
    {
        return soulsRetrieved;
    }
}

// Methods
void Enemy::chooseNewMove(){
    chosenMoveIndex = rand() % weapon.getMoves().size();
}
