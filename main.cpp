#include <iostream>
#include <fstream>
#include <string>
#include "videoGame.h"

using namespace std;

/* Bang Ngoc Pham
   This is Items Discover Game. As its name, to win this game, the player needs to find at least three different type of 
   items: Crystal (randomly located in the world), Clover (by facing Monster) and Riddle (by solving riddle) in the world of game.
   Of course, there are several obstacles that has been set to avoid the player getting items. These obstacles can be 
   Monsters, Bomb or Riddles. Also, if the player has crystals, he/she can chooses to put it down at any locations.
   For Monsters, it is an super angry Monster. The Monster extremely loves Crystal, so the only way to calm it is to give 
   it your Crystals; or yield and then you will lose. Also, the Monster owns Clover which is a magical curative
   leaf. If you give the Monster your Crystal, it will give its Clover back to you.
   For Booms, the player need to find out the password to dispose of the boom. The password can be randomly set, it is one of
   the two numbers : 0 or 1. If the player choose the correct number, he/she can pass this Bomb location; otherwise, the
   Bomb will immediately explode and hurt the player. But if the player has Clover in bag, he/she can choose to use it to cure himself
   /herself. Of course, the number of Clovers in his/her bag is decreased.
   For Riddle, then the player needs to choose the correct word among 2 given words based on a descriptive sentence.
   Note: In order to win this game, you don't have to pass all the locations in the world. 
   You just need to find AT LEAST ONE FOR EACH OF THREE DIFFERENT TYPES OF ITEMS and ALL SPECIAL ITEMS, then you win.
   Project 7's new feature:
   There are two kinds of special items: chocolate and candy which is randomly assigned when the user creates a Special object
   A Queue class is created to store Special items that are located in the world based on game.txt. Queue's Enqueue and Remove
   are used in Special class to enqueue an new Special item (when the user create a Special object) and remove the Special 
   item that has the key as its name from the queue when the player has been visited its location.
   A Map is created in Player.h to store Special items that has been located in the world. The map's key is Special items' name
   (chocolate or candy) and the value is the number of each Special item. Whenever the player found out chocolate or candy, the
   number of that Special item is decreased by 1. This is because the map shows how many each type of Special items left to find,
   not what the player has been found. Also, in the menu, a new option (h)ow many Special items left is added, the player can 
   choose it to see how many Special items left he/she needs to find to win the game.
   Project 8's new feature:
   Storage class, which inherits from Location class, is a location that can save the dropped item and the player can retrieve it
   later. The player can choose to drop one of normal items (Crystal, Key and Clover), not special item (Chocolate and Candy) at
   any location in the world's board. If the player fortunately drops item at Storage location, he/she can retrieve it later.
   Otherwise, if the player unfortunately drops item at other location, he/she loses the item
   */

int main(int argc, char* argv[]) {
    Videogame g;
    g.playGame();
   return 0;
}