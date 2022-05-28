#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

/*** ~ Class Game ~

Lie les différents objets du jeu entre eux ***/

#include <vector>
#include "floor.hpp"
#include "player.hpp"
#include "collision.hpp"
#include "entity.hpp"

class Game{

public:
  Game();
  ~Game() = default;
  void start();

private:
  Player p1_;
  Player p2_;
  std::vector<Floor> floors_;
  unsigned int currentMap_;
  unsigned int currentFloor_;
  TileMapProperties prop_;
  std::vector<Item*> items_;
  std::vector<sf::Drawable*> drawableResources_;

  void showMenu();
  void buildLevels();
  void updateLevels();
  void drawAll(sf::RenderWindow& window) const;
  void manageInput(sf::RenderWindow& window, sf::Event& event);
  void manageCollision(sf::RenderWindow& window);
  void manageAnimation();

  sf::Vector2f getSizeWindow(const TileMap& map, const sf::Vector2u& numberTiles) const;
};

#endif
