#ifndef TILEMAPPROPERTIES_HPP_INCLUDED
#define TILEMAPPROPERTIES_HPP_INCLUDED

#include <iostream>
#include <unordered_map>
#include "nonCopyable.hpp"

/* ~ Class TileMapProperties ~

Permet de modéliser les caractéristiques non graphiques des tiles
Par exemple faire correspondre un indice de tile à une caractéristique solide pour empêcher de traverser l'élément
Ou une caractéristique item, etc ***/

class TileMapProperties : public NonCopyable{

public:

  using propMap = std::unordered_map<int, std::string>;

  TileMapProperties();
  TileMapProperties(const propMap&);
  virtual ~TileMapProperties() = default;
  void addState(int tileId, const std::string& state);
  void changeState(int tileId, const std::string& state);
  bool isState(int tileId, const std::string& state);

private:

  propMap properties_;
};

#endif
