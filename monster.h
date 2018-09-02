#ifndef monster
#define monster


#include <string>
#include <vector>
#include <iostream>
#include "character.h"
#include "room.h"

class Room;

using namespace std;

// Monster class declaration
class Monster
{   private:
        string monster_name;
        string monster_description;
        int damage;

    public:
      // Constructor
      Monster(const string& name, const string& desc, int d);

      string getMonsterName();
      string getMonsterDescription();
      int getDamage();
      void monsterData(vector<Room> &gameMap, int &currentRoom);
      void inflictDamage(vector<Room> &gameMap, int &currentRoom, Character &user);
      void monsterAction(vector<Room> &gameMap, int &currentRoom, Character &user);
};

#endif