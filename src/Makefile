#### Makefile Projet C++ - ROBLIKE
#### CHALI Amir
#### BARBAROUX Leo-Paul

LIBS=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lsfml-audio
FLAGS= -std=gnu++17 -I../include -g
SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)

TARGET = ../roblike

$(TARGET): $(OBJ)
	g++ -o $(TARGET) $(OBJ) $(LIBS)

#roblike: main.o map.o player.o tileMapProperties.o item.o entity.o animation.o projectile.o monster.o floor.o menu.o game.o
#	g++ -o roblike main.o map.o player.o tileMapProperties.o item.o entity.o animation.o projectile.o monster.o floor.o menu.o game.o $(LIBS)

%.o: %.cpp
	g++ $(FLAGS) -c $< -o $@

#map.o: ./sources/map.cpp
#	g++ -std=gnu++17 -c map.cpp



clean:
	rm -f *.o

vclean: clean
	rm -f roblike
