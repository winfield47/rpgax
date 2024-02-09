//
//  Player.cpp
//  rpgax
//
//  Created by Kyle Winfield Burnham on 1/16/24.
//

#include "player.h"

// Constructors
Player::Player(){}
Player::Player(Origin origin, std::string playerName){
    this->origin = origin;
    description = playerName;
    level = 0;
    vigor = 0;
    armor = 0;
    resistance = 0;
    weapon = Weapon();
    apparel = Apparel();
    cloak = Cloak();
    potion = Potion();
    isCurrentlyDodging = false;
    status = nostatus;
    
    switch (origin) {
            
        case brute:
            asciiArt = "|O|";//   |O|
            strength = 75;
            dexterity = 69;
            intelligence = 65;
            faith = 71;
            souls = 2;
            weapon = Weapon(zweihander);
            apparel = Apparel("Hide", 2);
            break;
            
        case rogue:
            asciiArt = "`0~";//   `0~
            strength = 68;
            dexterity = 75;
            intelligence = 67;
            faith = 70;
            souls = 5;
            weapon = Weapon(estoc);
            apparel = Apparel("Leather", 1);
            cloak = Cloak("Tattered", 1);
            break;
        
        case wizard:
            asciiArt = ")^(";//   )^(
            strength = 65;
            dexterity = 72;
            intelligence = 75;
            faith = 68;
            souls = 4;
            weapon.setPlayerIntelligenceModifier(intelligence);
            weapon = Weapon(spellbook);
            cloak = Cloak("Hooded", 2);
            potion = Potion("Healing", 5);
            break;
            
        case inquisitor:
            asciiArt = "/?\\";//   /?\         /
            strength = 72;
            dexterity = 65;
            intelligence = 68;
            faith = 75;
            souls = 1;
            weapon = Weapon(talisman);
            apparel = Apparel("Leather", 1);
            cloak = Cloak("Tattered", 1);
            potion = Potion("Healing", 5);
            break;
            
        default:
        case nomad:
            asciiArt = "\\o/";//   \o/
            strength = 70;
            dexterity = 70;
            intelligence = 70;
            faith = 70;
            souls = 22;
            weapon = Weapon(unarmed);
            break;
    }
    
    hpMax = hp = 20 + (strength - 70) * 2;
    armor = apparel.grade;
    resistance = cloak.grade;
    weapon.setPlayerIntelligenceModifier(intelligence);
    weapon.setPlayerFaithModifier(faith);
    
}

// Accessors
std::string Player::getFullBlownASCII() const{
    switch (origin) {
        case brute:
            return R"(
      _,.
    ,` -.)
   ( _/-\\-._
  /,|`--._,-^|            ,
  \_| |`-._/||          ,'|
    |  `-, / |         /  /
    |     || |        /  /
     `r-._||/   __   /  /
 __,-<_     )`-/  `./  /
'  \   `---'   \   /  /
    |           |./  /
    /           //  /
\_/' \         |/  /
 |    |   _,^-'/  /
 |    , ``  (\/  /_
  \,.->._    \X-=/^
  (  /   `-._//^`
   `Y-.____(__}       `-.-'
    |     {__)
          ()
                       
)";
        case rogue:
            return R"(
             _,._
           ,'   ,`-.
|.        /     |\  `.
\ \      (  ,-,-` ). `-._ __
 \ \      \|\ ∂     `\  /'  `\
  \ \      ` |, ,  /  \ \     \
   \ \         `,_/`, /\,`-.__/`.
    \ \            | ` /    /    `-._
     \\\           `-/'    /         `-.
      \\`/ _______,-/_   /'             \
     ---'`|       |`  ),' `---.  ,       |
      \..-`--..___|_,/          /       /
                 |    |`,-,...,/      ,'
                 \    | |_|   /     ,' __  r-'',
                  |___|/  |, /  __ /-''  `'`)  |
               _,-'   ||__\ /,-' /     _,.--|  (
            .-'       )   `(_   / _,.-'  ,-' _,/
             `-------'       `--''       `'''

)";
        case wizard:
            return R"(
                             /\
                            /  \
                           |    |
                         --:'''':--
                           :'_' :
                           _:  :\___
            ' '      ____.'         '._
           . *=====<<=)           \    :
            .  '      '-'-'\_      /'._.'
                             \====:_ ""
                            .'     \\
                           :       :
                          /   :    \
                         :   .      '.
         ,. _        snd :  : :      :
      '-'    ).          :__:-:__.;--'
    (        '  )        '-'   '-'
 ( -   .00.   - _
(    .'  _ )     )
'-  ()_.\,\,   -
)";
        case inquisitor:
            return R"(
            {}
             .--.
            /.--.\
            |====|
            |`::`|
        .-;`\..../`;_.-^-._
 /\\   /  |...::..|`   :   `|
 |:'\ |   /'''::''|   .:.   |
@|\ /\;-,/\   ::  |..:::::..|
`||\ <` >  >._::_.| ':::::' |
 || `""`  /   ^^  |   ':'   |
 ||       |       \    :    /
 ||       |        \   :   /
 ||       |___/\___|`-.:.-`
 ||        \_ || _/    `
 ||        <_ >< _>
 ||        |  ||  |
 ||        |  ||  |
 ||       _\.:||:./_
 \/      /____/\____\ jgs

)";
        case nomad:
            return R"(
     ___
   ,'._,`.
  (-.___.-)
  `-.___.-'
   ((  e e|              .            __
    \   ` |         ,\   |`.    @|   |  |      _.-._
   __`.`=-=mm===mm:: |   | |`.   |   |  |    ,'=` '=`.
  (    `-'|:/  /:/  `/  @| | |   |, @| @|   /---)W(---\
   \ \   / /  / /         @| |   '         (----| |----) ,~
   |\ \ / /| / /            @|              \---| |---/  |
   | \ V /||/ /                              `.-| |-,'   |
   |  `-' |V /                                 \| |/    @'
   |    , |-'                                 __| |__
   |    .;: _,-.                         ,--""..| |..""--.
   ;;:::' "    )                        (`--::__|_|__::--')
 ,-"      _,  /                          \`--...___...--'/
(    -:--'/  /                           /`--...___...--'\
 "-._  `"'._/                           /`---...___...---'\
     "-._   "---.                      (`---....___....---')
      .' ",._ ,' )                     |`---....___....---'|
      /`._|  `|  |                     (`---....___....---')
     (   \    |  /                      \`---...___...---'/
      `.  `,  ^""                        `:--...___...--;'
        `.,'                               `-.Shimrod.-'
                                              
)";
        default:
            throw "You didn't give a valid Origin for the full blown ASCII art...";
    }
}
std::string Player::getName() const{
    return description;
}
Origin Player::getOrigin() const{
    return origin;
}
int Player::getSouls() const{
    return souls;
}
int Player::getLevel() const{
    return level;
}
int Player::getVigor() const{
    return vigor;
}
int Player::getSoulsNeededToLevelUp() const{
    if (level == 0)
    {
        return 10;
    }
    else
    {
        return vigor * 1.2;
    }
}
int Player::getArmor() const{
    return armor;
}
int Player::getResistance() const{
    return resistance;
}
Apparel Player::getApparel() const{
    return apparel;
}
Cloak Player::getCloak() const{
    return cloak;
}
Potion Player::getPotion() const{
    return potion;
}
bool Player::isDodging() const{
    return isCurrentlyDodging;
}

// Methods
int Player::spendSouls(int soulsSpent){
    souls -= soulsSpent;
    return soulsSpent;
}
void Player::levelUp(int soulsConsumed, std::string attributeToIncrease){
    if (soulsConsumed == getSoulsNeededToLevelUp())
    {
        souls -= soulsConsumed;
        vigor = soulsConsumed;
        level += 1;
        hpMax += 1;
        heal(1);
        if (attributeToIncrease == "str")
        {
            strength += 1;
            hpMax += 2;
            heal(2);
        }
        else if (attributeToIncrease == "dex")
        {
            dexterity += 1;
        }
        else if (attributeToIncrease == "int")
        {
            intelligence += 1;
            weapon.setPlayerIntelligenceModifier(intelligence);
        }
        else if (attributeToIncrease == "fai")
        {
            faith += 1;
            weapon.setPlayerFaithModifier(faith);
        }
        else
        {
            throw "bad attribute to level up";
        }
    }
    else
    {
        throw "consumed invalid amount of souls to level up";
    }
}
void Player::addSouls(int soulsAdded){
    souls += soulsAdded;
}
void Player::replaceWeapon(Weapon newWeapon){
    weapon = newWeapon;
}
void Player::replaceApparel(Apparel newApparel){
    apparel = newApparel;
    armor = apparel.grade;
}
void Player::replaceCloak(Cloak newCloak){
    cloak = newCloak;
    resistance = cloak.grade;
}
void Player::replacePotion(Potion newPotion){
    potion = newPotion;
}
Potion Player::popPotion(){
    Potion usedPotion = potion;
    potion = Potion();
    return usedPotion;
}
void Player::startDodging(){
    isCurrentlyDodging = true;
}
void Player::stopDodging(){
    isCurrentlyDodging = false;
}
