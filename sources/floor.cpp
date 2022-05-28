#include "floor.hpp"

Floor::Floor(){

  maps_.clear();
}

Floor::Floor(const std::vector<TileMap>& maps) : maps_(maps){


}

void Floor::addMap(const TileMap& map){

  maps_.push_back(map);
}

void Floor::setMap(const TileMap& map, std::size_t index){

  if(std::size(maps_) < index + 1)
    throw std::overflow_error("Erreur index tableau des niveaux");

  else
    maps_[index] = map;
}

void Floor::clearFloor(){

  maps_.clear();
}

void Floor::drawMap(sf::RenderWindow& window, std::size_t index){

  if(std::size(maps_) < index + 1)
    throw std::overflow_error("Erreur index tableau des niveaux");

  else
    window.draw(maps_[index]);
}

TileMap* Floor::getMap(std::size_t index){

  if(std::size(maps_) < index + 1)
    throw std::overflow_error("Erreur index tableau des niveaux");

  else
    return &maps_[index];
}
