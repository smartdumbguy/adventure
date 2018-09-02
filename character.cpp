#include "character.h"
#include <string>
#include <iostream>

using namespace std;

/*************************************************************************
 |                          Character Functions                          |
 *************************************************************************/
 //Constructor
 Character::Character()
 {
   health = 100;
   numLives = 3;
 }

 void Character::setName()
 {
   string name;
   cout << "Enter a name for your character: ";
   cin  >> name;
   char_name = name;
 }

 // Get/Set Functions
 int Character::getHealth() {  return health;  }
 int Character::getNumLives() {  return numLives;  }

 void Character::setHealth(int newHealth)
 {
   health = newHealth;
 }

 // Function to set the number of remaining lives
 void Character::setnumLives(int nL)
 {
   numLives = nL;
 }

 string Character::getCharName() {  return char_name;  }

 // Function to subract one life from the number of lives the character has
 void Character::takeLife()
 {
   cout << "\n";
   cout << "You died. If you still have lives left, you will respawn." << endl;
   setHealth(100);
   setnumLives(getNumLives() - 1);
   cout << "You have " << getNumLives() << " lives left.";
   cout << "\n";
 }
/*************************************************************************
 |                        End Character Functions                        |
 *************************************************************************/