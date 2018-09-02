#ifndef room
#define room

#include <string>
#include "monster.h"

using namespace std;

class Monster;

// Room class declaration
class Room
{   private:
        string room_name;
        string room_description;
        int room_id;
        bool occupied;

    public:
      // Constructor
      Room(const string& name, const string& desc, int id);

      int numEntered;
      Monster* activeMonster;
      void setOccupied(bool);
      string getRoomName();
      string getRoomDescription();
      int getRoom_id();
      bool getOccupied();
      int getNumEntered();
      // Variables to hold adjacent rooms
      int N, S, E, W;
};

#endif