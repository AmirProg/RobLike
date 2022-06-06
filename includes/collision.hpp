#ifndef COLLISION_HPP_INCLUDED
#define COLLISION_HPP_INCLUDED

#include "map.hpp"
#include "tileMapProperties.hpp"
#include "item.hpp"
#include <random>
#include <SFML/System.hpp>
#include <time.h>

/**************************************************************
* ~ Collision manager  ~
*
*
* Player A {}, B {};
* if(Collision::intersect(A,B)) // Test de collision entre deux objets de type Player
*   // Do
*
***************************************************************/
/*static inline bool intersectEntity(const T& A, const U& B){

    sf::FloatRect boxA = { A.getBox().left, A.getBox().top, A.getBox().width, A.getBox().height };
    sf::FloatRect boxB = { B.getBox().left, B.getBox().top, B.getBox().width, B.getBox().height };
    return boxA.intersects(boxB);
}*/

namespace Collision{

  template<typename T, typename U>
  static inline bool intersectEntity(const T& A, const U& B){


      return !(A.getBox().left + A.getBox().width < B.getBox().left ||
              A.getBox().top + A.getBox().height < B.getBox().top ||
              A.getBox().left > B.getBox().left + B.getBox().width ||
              A.getBox().top > B.getBox().top + B.getBox().height);
  }

  template<typename T>
  static inline bool intersectWindowLeft(const T& A) {

      return A.getBox().left <= 0;
  }

  template<typename T>
  static inline bool intersectWindowRight(const T& A, const sf::RenderWindow& window) {

      return A.getBox().left + A.getBox().width >= window.getSize().x;
  }

  template<typename T>
  static inline bool intersectWindowTop(const T& A) {

      return A.getBox().top <= 0;
  }

  template<typename T>
  static inline bool intersectWindowBottom(const T& A, const sf::RenderWindow& window) {

      return A.getBox().top + A.getBox().height >= window.getSize().y;
  }

  template<typename T>
  static inline bool intersectWindow(const T& A, const sf::RenderWindow& window) {

      return intersectWindowRight(A, window) || intersectWindowLeft(A) || intersectWindowTop(A) || intersectWindowBottom(A, window);
  }

  template<typename T>
  static inline void makeWindowSolid(T& A, const sf::RenderWindow& window) {

      if (intersectWindowRight(A, window))
          A.setPosition(sf::Vector2f(window.getSize().x - A.getBox().width, A.getBox().top));

      if (intersectWindowBottom(A, window))
          A.setPosition(sf::Vector2f(A.getBox().left, window.getSize().y - A.getBox().height));

      if (intersectWindowTop(A))
          A.setPosition(sf::Vector2f(A.getBox().left, 0));

      if (intersectWindowLeft(A))
          A.setPosition(sf::Vector2f(0, A.getBox().top));
  }

  template<typename T>
  static inline bool collisionTileState(const T& A, const TileMap& tileMap, TileMapProperties& tileMapProperties, const std::string& state) {

      sf::Vector2u tilesMin{ tileMap.positionToIndex(sf::Vector2f(A.getBox().left , A.getBox().top)) };
      sf::Vector2u tilesMax{ tileMap.positionToIndex(sf::Vector2f(A.getBox().left + A.getBox().width,A.getBox().top + A.getBox().height)) };

      for (size_t i{ tilesMin.x }; i <= std::min(tileMap.getNumberTiles().y, tilesMax.x); ++i) {

          for (size_t j{ tilesMin.y }; j <= std::min(tileMap.getNumberTiles().x, tilesMax.y); ++j) {

              if (tileMapProperties.isState(tileMap.getTileNumber(sf::Vector2u(i, j)), state))
                  return true;
          }

      }

      return false;
  }

  template<typename T>
  static inline bool collisionTileState(T& A, const TileMap& tileMap, TileMapProperties& tileMapProperties, const std::string& state, sf::Vector2u& positionIndexTile) {

      sf::Vector2u tilesMin{ tileMap.positionToIndex(sf::Vector2f(A.getBox().left , A.getBox().top)) };
      sf::Vector2u tilesMax{ tileMap.positionToIndex(sf::Vector2f(A.getBox().left + A.getBox().width,A.getBox().top + A.getBox().height)) };

      for (size_t i{ tilesMin.x }; i <= std::min(tileMap.getNumberTiles().y, tilesMax.x); ++i) {

          for (size_t j{ tilesMin.y }; j <= std::min(tileMap.getNumberTiles().x, tilesMax.y); ++j) {

              if (tileMapProperties.isState(tileMap.getTileNumber(sf::Vector2u(i, j)), state)){
                  positionIndexTile = sf::Vector2u(i,j);
                  return true;
              }
          }

      }

      return false;
  }

  /* Cette fonction surchargée est utilisée lorsque vous manipulez une sprite sheet et non seulement une sprite (donc on prend en compte le nombre de sprites) */

  template<typename T>
  static inline bool collisionTileState(T& A, const TileMap& tileMap, TileMapProperties& tileMapProperties, const std::string& state, sf::Vector2u& positionIndexTile, sf::Vector2u& dimSheet) {

      sf::Vector2u tilesMin{ tileMap.positionToIndex(sf::Vector2f(A.getBox().left , A.getBox().top)) };
      sf::Vector2u tilesMax{ tileMap.positionToIndex(sf::Vector2f(A.getBox().left + A.getBox().width/dimSheet.x,A.getBox().top + A.getBox().height/dimSheet.y)) };

      for (size_t i{ tilesMin.x }; i <= std::min(tileMap.getNumberTiles().y, tilesMax.x); ++i) {

          for (size_t j{ tilesMin.y }; j <= std::min(tileMap.getNumberTiles().x, tilesMax.y); ++j) {

              if (tileMapProperties.isState(tileMap.getTileNumber(sf::Vector2u(i, j)), state)){
                  positionIndexTile = sf::Vector2u(i,j);
                  return true;
              }
          }

      }

      return false;
  }

  static inline bool collisionTileStatePos(const sf::Vector2f& position, const sf::Vector2f& dim, const TileMap& tileMap, TileMapProperties& tileMapProperties, const std::string& state) {

      sf::Vector2u tilesMin{ tileMap.positionToIndex(sf::Vector2f(position.x , position.y)) };
      sf::Vector2u tilesMax{ tileMap.positionToIndex(sf::Vector2f(position.x + dim.x, position.y + dim.y)) };

      for (size_t i{ tilesMin.x }; i <= std::min(tileMap.getNumberTiles().y, tilesMax.x); ++i) {

          for (size_t j{ tilesMin.y }; j <= std::min(tileMap.getNumberTiles().x, tilesMax.y); ++j) {

              if (tileMapProperties.isState(tileMap.getTileNumber(sf::Vector2u(i, j)), state))
                  return true;
          }

      }

      return false;
  }

  template<typename T>
  static inline bool makeTilesSolidWithState(const T& A, const TileMap& tileMap, TileMapProperties& prop, const sf::Vector2f& dxy, const std::string& state, const sf::RenderWindow& window){

    sf::Vector2f newPos(A.getBox().left + dxy.x, A.getBox().top + dxy.y);
    sf::Vector2f dim(A.getBox().width, A.getBox().height);

    if (Collision::collisionTileStatePos(newPos, dim, tileMap, prop, state))
        return true;

    return false;
  }

  template<typename T>
  static inline bool makeTilesSolidWithState(const T& A, const TileMap& tileMap, TileMapProperties& prop, const sf::Vector2f& dxy, const sf::Vector2u& dimSheet, const std::string& state, const sf::RenderWindow& window){

    sf::Vector2f size { A.getBox().width/dimSheet.x, A.getBox().height/dimSheet.y };

    sf::Vector2f newPos(A.getBox().left + dxy.x, A.getBox().top + dxy.y);
    sf::Vector2f dim(A.getBox().width, A.getBox().height);
    if (Collision::collisionTileStatePos(newPos, dim, tileMap, prop, state))
        return true;

    return false;
  }

  static inline void collisionWithItem(Player& player, TileMap* tileMap, TileMapProperties& prop, const std::vector<Item*>& items, const std::string& state, const sf::RenderWindow& window, sf::Clock& clock){

    sf::Vector2u positionIndex;

    /* On tire un entier aléatoirement entre 0 et le nombre d'items - 1 */

    if(clock.getElapsedTime().asMilliseconds() > 100){
      
      std::random_device rd;
      std::default_random_engine e(rd());
      std::uniform_int_distribution<int> dist(0,items.size()-1);

      int i { dist(e) };

      if(Collision::collisionTileState(player, *tileMap, prop, state, positionIndex)){
        items[i]->activate(player); // On réindexe le tableau, items commence à 0 et c'est équivalent au (index - nombre_total_tiles + nombre_items) % nombre_items
        tileMap->changeTile(sf::Vector2u(positionIndex.x, positionIndex.y), 1);
        clock.restart();
      }
    }
  }
}

#endif
