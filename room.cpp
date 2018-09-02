#include "room.h"

/*************************************************************************
 |                          Room Functions                               |
 *************************************************************************/
 // Constructor
 Room::Room(const string& name, const string& desc, int id):
 room_name(name), room_description(desc), room_id(id)
 {
   occupied = false;
   numEntered = 0;
   activeMonster = NULL;
 }

 // Get/Set Functions
 void Room::setOccupied(bool flag)
 { occupied = flag; }

 string Room::getRoomName()
 {  return room_name;  }

 string Room::getRoomDescription()
 {  return room_description;  }

 int Room::getRoom_id()
 {  return room_id;  }

 bool Room::getOccupied()
 {  return occupied;  }

 int Room::getNumEntered()
 {  return numEntered;  }
/**************************************************************************
 |                         End Room Functions                             |
 **************************************************************************/