#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

/*** ~ Class Game ~

Lie les différents objets du jeu entre eux ***/

#include <vector>
#include "floor.hpp"
#include "player.hpp"
#include "collision.hpp"
#include "monster.hpp"
#include "menu.hpp"

class Game{

public:
  Game();
  ~Game() = default;
  void start();
  void showMenu();

private:
  Player p1_;
  Player p2_;
  std::vector<Player*> players_;
  std::vector<Floor> floors_;
  unsigned int currentMap_;
  unsigned int currentFloor_;
  TileMapProperties prop_;
  std::vector<Item*> items_;
  std::vector<sf::Drawable*> drawableResources_;
  TileMap* currentTileMap_;
  std::vector<Monster> monsters_;
  Menu menu_;
  sf::Text gameOver;
  sf::Clock timeGameOver_;
  sf::Clock mapTransition_;
  sf::Clock itemCollectedDelay_;
  bool playing_;

  sf::Texture texture1;
  sf::Texture texture2;

  void buildLevels();
  void updateLevels();
  void loadBasicMonsters();
  void handleMonstersLogic(const sf::RenderWindow& window);
  void drawAll(sf::RenderWindow& window) const;
  void manageInput(sf::RenderWindow& window, sf::Event& event);
  void manageCollision(sf::RenderWindow& window);
  void manageAnimation();
  void manageGameOver(sf::RenderWindow& window, const sf::Font& font);
  void manageMenuButtons();
  bool areMonstersAlive() const;

  void play();

  sf::Vector2f getSizeWindow(const TileMap& map, const sf::Vector2u& numberTiles) const;
};

#endif
