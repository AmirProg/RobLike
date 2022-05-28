#ifndef FLOOR_HPP_INCLUDED
#define FLOOR_HPP_INCLUDED

#include "map.hpp"
#include "tileMapProperties.hpp"

/*** ~ Class Floor

Permet de gérer un étage entier (ensemble de maps et d'ennemis qu'on ajoute à la scène) ***/

class Floor{

public:

  Floor();
  Floor(const std::vector<TileMap>& maps);
  void addMap(const TileMap& map);
  void setMap(const TileMap& map, std::size_t index);
  void clearFloor();
  void drawMap(sf::RenderWindow& window, std::size_t index);
  TileMap* getMap(std::size_t index); // On renvoie un pointeur vers la map d'index voulu

private:

  std::vector<TileMap> maps_;
};

#endif
