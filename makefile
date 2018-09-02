CFLAGS = -std=c++14 -Wall -pedantic 
CC = g++

adventure: adventure.o character.o monster.o room.o
	$(CC) $(CFLAGS) -o adventure adventure.o character.o monster.o room.o

character: character.cpp
	$(CC) $(CFLAGS) -c character.cpp

monster: monster.cpp
	$(CC) $(CFLAGS) -c monster.cpp

room: room.cpp
	$(CC) $(CFLAGS) -c room.cpp

clean:
	rm -f core *.o adventure