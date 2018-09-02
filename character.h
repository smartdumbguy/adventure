#ifndef character
#define character

#include <string>
using namespace std;

// Character class declaration
class Character
{   private:
        string char_name;
        int numLives;
        int health;

    public:
        // Constructor
        Character();

        // Variable to hold number of treasures collected
        int numTreasures = 0;

        void setName();
        void setHealth(int newHealth);
        void setnumLives(int nL);
        int getHealth();
        int getNumLives();
        string getCharName();
        void takeLife();
};

#endif 