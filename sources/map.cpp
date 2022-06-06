#include "map.hpp"
#include <cassert>
#include <iostream>
#include <fstream>

TileMap::TileMap() : TileMap("VIDE", sf::Vector2u(0,0), std::initializer_list<std::initializer_list<int>>())
{}

TileMap::TileMap(const std::string& pathTexture, const sf::Vector2u& nbSprites, const std::initializer_list<std::initializer_list<int>>& mapMatrix) :
  pathTexture_(pathTexture),
  nbSprites_(nbSprites),
  background_(false){

    assert(texture_.loadFromFile(pathTexture) && "Erreur chargement texture map");
    spriteSheet_.setTexture(texture_);

    numberTiles_ = sf::Vector2u(std::size(*std::begin(mapMatrix)), std::size(mapMatrix)); // *std::begin(mapMatrix) is the first case of the Matrix (-> Rows)
    mapMatrix_.resize(numberTiles_.y,numberTiles_.x);

    std::size_t countLine {};
    std::size_t countRow {};

    for(const auto& i : mapMatrix){ // i is a std::initialiser_list<int>, not an integer
        for(const auto& j : i){ // But j is
            mapMatrix_(countLine,countRow) = j;
            ++countRow;
        }

        ++countLine;
        countRow = 0;
    }

    ++countLine;
    countRow = 0;
}

TileMap::TileMap(const std::string& path){

    std::ifstream file{ path };
    assert(file && "Erreur fichier map"); // The file has been charged

    int currentValue{};

    sf::Vector2u numberTilesSheet{};
    sf::Vector2u numberTiles{};

    file >> pathTexture_ >> numberTilesSheet.x >> numberTilesSheet.y >> numberTiles.x >> numberTiles.y; // The first line is the path to the texture, the two next are the number of tiles (width, height)

    assert(texture_.loadFromFile(pathTexture_) && "Erreur texture map");
    spriteSheet_.setTexture(texture_);

    mapMatrix_.resize(numberTiles.y, numberTiles.x);

    numberTiles_ = numberTiles;
    nbSprites_ = numberTilesSheet;

    for (std::size_t i{}; i < numberTiles_.y; ++i) {

        for (std::size_t j{}; j < numberTiles_.x; ++j) {

            file >> currentValue >> std::ws;
            mapMatrix_(i, j) = currentValue;
        }
    }
}

TileMap::TileMap(const TileMap& map){

  *this = map;
}

TileMap& TileMap::operator=(const TileMap& map){

  pathTexture_ = map.pathTexture_;
  texture_ = map.texture_;
  spriteSheet_ = map.spriteSheet_;
  numberTiles_ = map.numberTiles_;

  mapMatrix_.resize(numberTiles_.y, numberTiles_.x);
  mapMatrix_ = map.mapMatrix_;

  nbSprites_ = map.nbSprites_;
  sprites_.clear();

  loadTexture();

  return *this;
}

void TileMap::loadTexture(){

  spriteSheet_.setTexture(texture_);
}

void TileMap::setDim(const sf::Vector2f& dim){

  dim_ = dim;
}

void TileMap::fillMap(){

  sprites_.clear();

  sf::Vector2f sizeOneSprite { getSizeOneSprite() };

  for(std::size_t i {}; i < numberTiles_.y; ++i){ // 0 -> number of lines

      for(std::size_t j {}; j < numberTiles_.x; ++j){ // 0 -> number of rows

          std::size_t scaleX = mapMatrix_(i,j)%nbSprites_.x; // Prevent to go over the number of tiles on a single line
          std::size_t scaleY = static_cast<std::size_t>(mapMatrix_(i,j)/nbSprites_.x);

          sf::Sprite copy { spriteSheet_ };

          cut(copy, sizeOneSprite, sf::Vector2u(scaleX,scaleY)); // sf::IntRect(x,y,sizeX,sizeY)
          copy.setPosition(sf::Vector2f(j*sizeOneSprite.x,i*sizeOneSprite.y)); // On repositionne

          sprites_.push_back(copy); // On ajoute le sprite correctement découpé et positionné au tableau de sprites (la map visuellement)
      }
  }
}

void TileMap::setBackground(const std::string& path){

  if(!textureBackground_.loadFromFile(path))
    std::cerr << "Erreur texture background" << std::endl;

  else{
    spriteBackground_.setTexture(textureBackground_);
    background_ = true;
  }
}

sf::Vector2f TileMap::getSizeOneSprite() const{

  try{

    if(nbSprites_.x != 0 && nbSprites_.y != 0)
      return sf::Vector2f(static_cast<float>(spriteSheet_.getTexture()->getSize().x / nbSprites_.x), static_cast<float>(spriteSheet_.getTexture()->getSize().y / nbSprites_.y));

      else
        throw std::runtime_error("Erreur division par 0");
  }

  catch(const std::runtime_error& e){

    std::cerr << e.what();
  }

  return sf::Vector2f(0,0);
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const{

  //if(background_)
  //  target.draw(spriteBackground_, states);

  for(const auto& sprite : sprites_)
    target.draw(sprite, states);
}

void cut(sf::Sprite& sprite, const sf::Vector2f& sizeOneSprite, const sf::Vector2u& index){
    sprite.setTextureRect((sf::IntRect(index.x * sizeOneSprite.x, index.y * sizeOneSprite.y, sizeOneSprite.x, sizeOneSprite.y)));
}

sf::Vector2u TileMap::positionToIndex(const sf::Vector2f& position) const{

  return sf::Vector2u(static_cast<std::size_t>(std::size_t(position.y/getSizeOneSprite().y) + 1),
                      static_cast<std::size_t>(std::size_t(position.x/getSizeOneSprite().x) + 1));
}

sf::Sprite TileMap::getTile(const sf::Vector2u& index) const{

    return sprites_[(index.x-1)*numberTiles_.x+index.y-1];
}

sf::Sprite TileMap::getTileWithPosition(const sf::Vector2f& position) const{

    return getTile(positionToIndex(position));
}

int TileMap::getTileNumber(const sf::Vector2u& index) const{

    try {

        if (index.x-1 < numberTiles_.x && index.y-1 < numberTiles_.y && index.x-1 >= 0 && index.y-1 >= 0)
            return mapMatrix_(index.x - 1, index.y - 1);

        else
            throw std::overflow_error("");
    }

    catch (const std::overflow_error& error) {

        std::cerr << error.what();
        return -1;
    }

    catch (const std::exception& error) {

        std::cerr << error.what();
        return -1;
    }
}

sf::Vector2u TileMap::getNumberTiles() const{

  return numberTiles_;
}

void TileMap::changeTile(const sf::Vector2u& index, int newTile){

  sprites_.clear();
  spriteSheet_.setTexture(texture_);
  mapMatrix_(index.x-1,index.y-1) = newTile;

  fillMap();
}
