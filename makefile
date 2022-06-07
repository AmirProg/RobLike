#### Makefile Projet C++ - ROBLIKE
#### CHALI Amir
#### BARBAROUX Leo-Paul

LIBS=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lsfml-audio

roblike: main.o map.o player.o tileMapProperties.o item.o entity.o animation.o projectile.o monster.o floor.o menu.o game.o
	g++ -o roblike main.o map.o player.o  tileMapProperties.o item.o entity.o animation.o projectile.o monster.o floor.o menu.o game.o $(LIBS)

map.o: map.cpp
	g++ -std=gnu++17 -c map.cpp

player.o: player.cpp
	g++ -std=gnu++17 -c player.cpp

tileMapProperties.o: tileMapProperties.cpp
	g++ -std=gnu++17 -c tileMapProperties.cpp

item.o: item.cpp
	g++ -std=gnu++17 -c item.cpp

entity.o: entity.cpp
	g++ -std=gnu++17 -c entity.cpp

animation.o: animation.cpp
	g++ -std=gnu++17 -c animation.cpp

projectile.o: projectile.cpp
	g++ -std=gnu++17 -c projectile.cpp

monster.o: monster.cpp
	g++ -std=gnu++17 -c monster.cpp

floor.o: floor.cpp
	g++ -std=gnu++17 -c floor.cpp

menu.o: menu.cpp
	g++ -std=gnu++17 -c menu.cpp

game.o: game.cpp floor.hpp
	g++ -std=gnu++17 -c game.cpp

main.o: main.cpp map.hpp player.hpp matrix.hpp nonCopyable.hpp tileMapProperties.hpp collision.hpp collidable.hpp item.hpp entity.hpp animation.hpp projectile.hpp monster.hpp floor.hpp menu.hpp game.hpp
	g++ -std=gnu++17 -c main.cpp

clean:
	rm -f *.o

vclean: clean
	rm -f roblike
