#ifndef MAP_HPP_INCLUDED
#define MAP_HPP_INCLUDED

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "nonCopyable.hpp"
#include "matrix.hpp"

class Map : public sf::Drawable {

public:
  Map() : Map(sf::Vector2f(0,0)) {}
  Map(const sf::Vector2f& dim) : dim_(dim) {}
  virtual void setDim(const sf::Vector2f& dim) = 0;

protected:
  sf::Vector2f dim_;

private:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
};

class TileMap : public Map{

public:
  TileMap();
  TileMap(const std::string&, const sf::Vector2u&, const std::initializer_list<std::initializer_list<int>>& mapMatrix);
  TileMap(const std::string& path); // Permet de charger une tilemap avec un fichier
  TileMap(const TileMap&);
  TileMap& operator=(const TileMap& map);
  void loadTexture();
  sf::Vector2f getSizeOneSprite() const;
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
  virtual void setDim(const sf::Vector2f& dim);
  void fillMap(); // Lance l'algorithme de tile mapping et remplit le tableau de sprites
  void setBackground(const std::string& pathBack); // Rempli le background de la map (pas obligatoire d'avoir une image en arrière-plan, mais c'est possible)
  sf::Vector2u positionToIndex(const sf::Vector2f&) const;
  sf::Sprite getTile(const sf::Vector2u& index) const;
  sf::Sprite getTileWithPosition(const sf::Vector2f& position) const;
  int getTileNumber(const sf::Vector2u& index) const;
  sf::Vector2u getNumberTiles() const;
  void changeTile(const sf::Vector2u& index, int newTile);

private:
  sf::Texture texture_;
  std::string pathTexture_;
  sf::Sprite spriteSheet_;
  sf::Texture textureBackground_;
  bool background_;
  sf::Sprite spriteBackground_;
  std::vector<sf::Sprite> sprites_;
  sf::Vector2u nbSprites_; // Nombre de sprites dans la spritesheet (x,y) (largeur, hauteur)
  sf::Vector2u numberTiles_; // Nombre de sprites dans la map (tiles) (x,y)
  Matrix<int> mapMatrix_ {};

};

void cut(sf::Sprite& sprite, const sf::Vector2f& sizeOneSprite, const sf::Vector2u& index);

#endif
