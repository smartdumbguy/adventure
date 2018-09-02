#include "monster.h"

/*************************************************************************
  |                       Monster Functions                               |
  *************************************************************************/
  // Constructor
  Monster::Monster(const string& name, const string& desc, int d):
  monster_name(name), monster_description(desc), damage(d)
  {
  }

  string Monster::getMonsterName() {  return monster_name;  }
  string Monster::getMonsterDescription() {  return monster_description;  }
  int Monster::getDamage() {  return damage;  }

  // Function to print Monster name/description
  void Monster::monsterData(vector<Room> &gameMap, int &currentRoom)
  {
    cout << "Oh no! You encountered a "
         << gameMap[currentRoom].activeMonster->getMonsterName() << "." << endl
         << gameMap[currentRoom].activeMonster->getMonsterDescription() << endl;
  }

  void Monster::inflictDamage(vector<Room> &gameMap, int &currentRoom, Character &user)
  {
    // Variable for current health
    int currentUserHealth = user.getHealth();

    user.setHealth(currentUserHealth - gameMap[currentRoom].activeMonster->getDamage());
  }

  // Function to perform monster action to character
  void Monster::monsterAction(vector<Room> &gameMap, int &currentRoom, Character &user)
  {
    // If statements to select proper bit depending on current monster in room
    // Each will print name/ description of monster, then subract appropriate
    // damage from user health
    if (gameMap[currentRoom].activeMonster->getMonsterName() == "Small Dog")
    {
      monsterData(gameMap, currentRoom);
      inflictDamage(gameMap, currentRoom, user);
    }

    else if (gameMap[currentRoom].activeMonster->getMonsterName() == "Vampire")
    {
      monsterData(gameMap, currentRoom);
      inflictDamage(gameMap, currentRoom, user);
    }
    else if (gameMap[currentRoom].activeMonster->getMonsterName() == "Dragon")
    {
      monsterData(gameMap, currentRoom);
      inflictDamage(gameMap, currentRoom, user);
    }
    else if (gameMap[currentRoom].activeMonster->getMonsterName() == "Troll")
    {
      monsterData(gameMap, currentRoom);
    }
  }
  /*************************************************************************
   |                   End Monster Functions                               |
   *************************************************************************/
