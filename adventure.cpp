/*
/ Text Adventure (Final Project)
/
/ This program is a simple text based adventure game.
/
/ Kyle Clapp
/
/ cisp360
/
/ DATE 5-17-17
*/

#include <iostream>
#include <string>
#include <vector>
#include "monster.h"
#include "character.h"
#include "room.h"

using namespace std;

// Function Prototypes
void newLine();
void printProgramName();
void printRoomData(vector<Room> &gameMap, int &currentRoom);
vector<Room> createMap();
vector<Monster> createMonsters();
char getMove();
void makeMove(vector<Room> &gameMap, int &currentRoom, int move, Character &user);
int getRandomInt(int lowerBound, int upperBound);
void trapEncounter(Character &user);

/**************************************************************************
 |                                   Main                                 |
 **************************************************************************/
int main()
{

  // Vectors to hold Room objects and the Monsters. Create a Character object
  // to hold user Character.
  vector <Room> gameMap = createMap();
  vector <Monster> monsters = createMonsters();
  Character user;

  // Variables to hold user move, and number of moves taken
  char move = 'n'; // Initialize to make compiler "happy"
  int numMoves = 0;

  // Print Program Name / Description
  newLine();
  printProgramName();

  // Create Character
  newLine();
  user.setName();
  cout << "Okay it's time to go" << endl;


  // Set current Room to the Room in position 0 of the vector. Throw a monster
  // in the room. Print current room data. Then have the monster in the current
  // room perform its action to the character
  int currentRoom = 0;
  gameMap[currentRoom].numEntered = 1;
  gameMap[currentRoom].activeMonster = &monsters[getRandomInt(0,4)];
  printRoomData(gameMap, currentRoom);
  newLine();
  gameMap[currentRoom].activeMonster->monsterAction(gameMap, currentRoom, user);
  newLine();
  cout << "User Health: " << user.getHealth() << endl;

  // You are now free to move about the map. Unless the user enters 'Q', or
  // dies too many times
  while (move != 'Q' && user.getNumLives() > 0)
  {

    // Bonus - Treasure
    if (numMoves % 4 == 0 && numMoves > 0)
    {
      newLine();
      cout << "You have stumbled upon a hidden Treasure!" << endl;
      user.numTreasures += 1;
    }

    // Bonus - Trap encounter, if certain conditions met
    if (numMoves % 6 == 0 && numMoves > 1)
    {
      trapEncounter(user);
    }

    // Get user choice for next move
    newLine();
    move = getMove();

    // If user enters 'Q', quit the program
    if (move == 'Q')
    {
      newLine();
      cout << "Thanks for playing!" << endl;
    }
    else
    {
      // Switch Rooms or print room description
      // Then increment numMoves and spawn a monster in the new room
      makeMove(gameMap, currentRoom, move, user);
      numMoves += 1;

      // If current Room is occupied, spawn random monster
      // The room is occupied, but the problem set instructions say:
      // "If the room is occupied, randomly select one of 4 monsters to
      // spawn in the room." and I don't want to miss points because I didn't
      // use an if statement
      if (gameMap[currentRoom].getOccupied())
      {
        gameMap[currentRoom].activeMonster = &monsters[getRandomInt(0,4)];
      }

      // Print room data and have monster perform its action on the user
      printRoomData(gameMap, currentRoom);
      newLine();
      gameMap[currentRoom].activeMonster->monsterAction(gameMap, currentRoom, user);
      newLine();
      cout << "User Health: " << user.getHealth() << endl;

      // Subract a life if dead
      if (user.getHealth() <= 0)
      {
        user.takeLife();
      }
    }
  }
  // If no lives left, print message and quit the game, also account for if the
  // user quit or ran out of lives
  if (user.getNumLives() == 0)
  {
    cout << "Sorry " << user.getCharName() << ", Game Over." << endl;
  }
  // Print number of treasures collected
  cout << "You collected " << user.numTreasures << " treasures!" << endl;
  return 0;
}
/**************************************************************************
 |                                End Main                                |
 **************************************************************************/



/*************************************************************************
 |                          Helper Functions                             |
 *************************************************************************/

 // Function to print new line to make program easier to read
 void newLine(void)
 {
   cout << endl;
 }

 // Function to print a simple greeting
 void printProgramName(void)
 {
   cout << "\tKyle's Simple Adventure Game\n";
   cout << "---------------------------------------------------\n";
   cout << "This game takes place in an abandoned hotel and\n"
        << "contains 7 Rooms. You will start off in the Lobby.\n"
        << "Each room will contain 1 of 4 random monsters.\n"
        << "Most of which will hurt you. You can move around\n"
        << "using the N,S,E,W keys to move in that direction.\n"
        << "You can also enter L to see the description of\n"
        << "the current room, or enter Q to quit the adventure.\n";
   cout << "---------------------------------------------------\n";
 }

 void printRoomData(vector<Room> &gameMap, int &currentRoom)
 {
   // Print current room name and, if it's the first time in the Room,
   // print description
   newLine();
   cout << "\t\t\tCurrent Room: " << gameMap[currentRoom].getRoomName() << endl;
   if (gameMap[currentRoom].getNumEntered() == 1)
   {
     cout << "Room Description: " << gameMap[currentRoom].getRoomDescription()
          << endl;
   }
 }

 // Function to fill a vector full of Room objects
 // TO DO - MAYBE SWAP THE SPA AND THE KITCHEN SO IT MAKES MORE SENSE
 vector<Room> createMap()
 {
   vector<Room> temp;

   Room Lobby("Lobby", "This is the hotel Lobby. To the North is the Kitchen, and to\n"
              "the East is the Bar.", 0);

   Room Kitchen("Kitchen", "This is the Kitchen. To the North is the Spa, to the\n"
              "South is the Lobby, and to the East is the Lounge.", 1);

   Room Bar("Bar", "This is the hotel Bar. To the North is the Lounge, and to\n"
              "West is the Lobby.", 2);

   Room Lounge("Lounge", "This is Lounge. To the North is the Restaurant, to the\n"
              "South is the Bar, to the East is the Patio, and to the West is "
              "the Kitchen.", 3);

   Room Spa("Spa", "This is the Spa. To the South is the Kitchen, and to the\n"
              "East is the Restaurant.", 4);

   Room Restaurant("Restaurant", "This is the Restaurant. To the South is Lounge, and to the\n"
              "West is the Spa.", 5);

   Room Patio("Patio", "This is the Patio. There is only one way to go from\n"
              "here, to the West where you came from...", 6);

   // Set adjacent Rooms for each room, Values represent position in array,
   // The values will be the room_id of the adjacent rooms or -1 if there
   // is no room in that direction
   Lobby.N =  Kitchen.getRoom_id();
   Lobby.S = -1;
   Lobby.E =  Bar.getRoom_id();
   Lobby.W = -1;

   Kitchen.N =  Spa.getRoom_id();;
   Kitchen.S =  Lobby.getRoom_id();
   Kitchen.E =  Lounge.getRoom_id();
   Kitchen.W =  -1;

   Bar.N =  Lounge.getRoom_id();
   Bar.S = -1;
   Bar.E = -1;
   Bar.W =  Lobby.getRoom_id();

   Lounge.N =  Restaurant.getRoom_id();
   Lounge.S =  Bar.getRoom_id();
   Lounge.E =  Patio.getRoom_id();
   Lounge.W =  Kitchen.getRoom_id();

   Spa.N =  -1;
   Spa.S =  Kitchen.getRoom_id();
   Spa.E =  Restaurant.getRoom_id();
   Spa.W =  -1;

   Restaurant.N =  -1;
   Restaurant.S =  Lounge.getRoom_id();
   Restaurant.E =  -1;
   Restaurant.W =  Spa.getRoom_id();

   Patio.N =  -1;
   Patio.S =  -1;
   Patio.E =  -1;
   Patio.W =  Lounge.getRoom_id();

   // Add Rooms to vector
   temp.push_back(Lobby);
   temp.push_back(Kitchen);
   temp.push_back(Bar);
   temp.push_back(Lounge);
   temp.push_back(Spa);
   temp.push_back(Restaurant);
   temp.push_back(Patio);

   return temp;
 }

 // Function to fill a vector full of Monster objects
 vector<Monster> createMonsters()
 {
   vector<Monster> temp;

   Monster monster1("Small Dog", "While not very big, the small, but angry dog\n"
                    "bites your ankles causing minor injuries.", 10);

   Monster monster2("Vampire", "The vampire rushes you and bites your neck.\n"
                    "You have lost some blood which effects your health.", 15);

   Monster monster3("Dragon", "Dragons are very powerfull. The dragon spits a\n"
                    "ball of fire at you inflicting serious damage.", 20);

   Monster monster4("Troll", "A troll is a \"nice\" monster.\n"
                    "The troll informs you that there is a cheat code\n"
                    "available that will restore your health. But, since he is\n"
                    "still a monster, he doesn't tell you what it is. Only\n"
                    "that it is a very famous cheat code.",  0);

   // Add Monsters to vector
   temp.push_back(monster1);
   temp.push_back(monster2);
   temp.push_back(monster3);
   temp.push_back(monster4);
   return temp;
 }

 // Function to get and validate potential move. Valid moves are N,S,E, or W.
 // Also, 'L' and 'Q' are valid entries representing room description and
 // quit respectivly.
 // This function will input the move as a string, check the first character
 // against valid moves, and ensure the user did not enter more than one
 // character for the move. Also, allow for the Cheat Code.
 char getMove()
 {
   string temp;
   char tempChar;
   cout << "Enter Move: ";
   cin >> temp;

   // Konami Code
   if (temp == "uuddlrlrba")
   {
     cout << "Cheat Code Accepted!\n";
     tempChar = 'c';
   }
   else
   {
     while ( (toupper(temp[0]) != 'N' && toupper(temp[0]) != 'S' &&
              toupper(temp[0]) != 'E' && toupper(temp[0]) != 'W' &&
              toupper(temp[0]) != 'L' && toupper(temp[0]) != 'Q') ||
              temp.length() != 1 )
     {
       cout << "\nInvalid Move!\n"
            << "You can only enter 'Q' to quit, 'L' to look around,\n"
            << "or one of the four cardinal(N,S,E,W) to move around\n"
            << "Try again: ";
       cin  >> temp;
     }
     tempChar = temp[0];
   }
   return toupper(tempChar);
 }

 // Function to make user move in map. Either switch rooms, show
 // description(look around room) or use the cheat code.
 void makeMove(vector<Room> &gameMap, int &currentRoom, int move, Character &user)
 {
   // Move if possible. Use a validMove flag to repeat process until a valid
   // move is entered by the user.
   bool validMove = false;
   while (!validMove)
   {
     // If user enters 'L' show room description
     if (move == 'L')
     {
       newLine();
       cout << "\t\t\tCurrent Room: " << gameMap[currentRoom].getRoomName() << endl;
       cout << "Room Description: " << gameMap[currentRoom].getRoomDescription()
            << endl << endl;
       move = getMove();
     }
     // Apply cheat code
     else if (move == 'C')
     {
       user.setnumLives(3);
       user.setHealth(100);
       cout << "Health has been restored. " << endl;
       move = getMove();
     }
     // Else Try Moving in the direction entered. Use Room object N,S,E,W
     // variables to determine if there is a room in entered direction.
     // The .N, .S, .E, .W, will be -1 if no room is in that direction
     else if (move == 'N' && gameMap[currentRoom].N >= 0)
     {
       gameMap[currentRoom].setOccupied(false);
       currentRoom = gameMap[currentRoom].N;
       gameMap[currentRoom].setOccupied(true);
       gameMap[currentRoom].numEntered += 1;
       validMove = true;
     }
     else if (move == 'S' && gameMap[currentRoom].S >= 0)
     {
       gameMap[currentRoom].setOccupied(false);
       currentRoom = gameMap[currentRoom].S;
       gameMap[currentRoom].setOccupied(true);
       gameMap[currentRoom].numEntered += 1;
       validMove = true;
     }
     else if (move == 'E' && gameMap[currentRoom].E >= 0)
     {
       gameMap[currentRoom].setOccupied(false);
       currentRoom = gameMap[currentRoom].E;
       gameMap[currentRoom].setOccupied(true);
       gameMap[currentRoom].numEntered += 1;
       validMove = true;
     }
     else if (move == 'W' && gameMap[currentRoom].W >= 0)
     {
       gameMap[currentRoom].setOccupied(false);
       currentRoom = gameMap[currentRoom].W;
       gameMap[currentRoom].setOccupied(true);
       gameMap[currentRoom].numEntered += 1;
       validMove = true;
     }
     // Else, there is no room in that direction, inform user and try again
     else
     {
       newLine();
       cout << "Oops, there is no room in that direction." << endl;
       cout << "Try again: ";
       move = getMove();
     }
   }
 }

 // Function to return random int in the range (lowerBound, upperBound - 1)
 int getRandomInt(int lowerBound, int upperBound)
 {
   // Variable to hold returned random int
   int randInt;

   // Initialize srand to system time to seed rand
   srand(time(NULL));

   // Generate random number between lowerBound and (upperBound - 1),
   // then return value
   randInt = lowerBound + rand() % upperBound;
   return randInt;
 }

 // Function for trap encounters.
 // Being bitten by a snake reduces your health by half.
 // While the ceiling falling on you, makes you dead
 void trapEncounter(Character &user)
 {
   int currentUserHealth = user.getHealth();

   // Variable to hold random number to select trap encounter
   int randNum = getRandomInt(0,2);

   if (randNum == 0)
   {
     newLine();
     cout << "You have been bitten by a venomous snake!\n";
     cout << "Your health has been reduced by half!" << endl;
     user.setHealth(currentUserHealth / 2);
     cout << "User Health: " << user.getHealth() << endl;
   }
   else if (randNum == 1)
   {
     newLine();
     cout << "The ceiling has collaplsed on you!";
     user.takeLife();
     cout << "User Health: " << user.getHealth() << endl;
   }
 }
/*************************************************************************
 |                      End Helper Functions                             |
 *************************************************************************/


 