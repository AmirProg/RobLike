#include "tileMapProperties.hpp"

TileMapProperties::TileMapProperties()
{}

TileMapProperties::TileMapProperties(const propMap& prop) : properties_(prop)
{}

void TileMapProperties::addState(int tileId, const std::string& state){

  properties_.insert( {tileId, state } );
}

void TileMapProperties::changeState(int tileId, const std::string& state){

  if(std::size(properties_) < tileId + 1)
    throw std::overflow_error("Erreur taille des propriétés de la map [OVERFLOW]");

  else
    properties_[tileId] = state;
}

bool TileMapProperties::isState(int tileId, const std::string& state){

  try{
    return properties_[tileId] == state;
  }

  catch(const std::exception& error){
    std::cerr << error.what();
    return false;
  }
}
