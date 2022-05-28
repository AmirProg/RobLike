#include "game.hpp"

Game::Game() : p1_("test", 3, "test", "perso.png", sf::Vector2u(9,4)), currentMap_(0), currentFloor_(0){

  buildLevels();

  p1_.setBase(sf::Vector2u(1,1));
  drawableResources_.push_back(&p1_);
}

void Game::buildLevels(){

  floors_.clear();

  floors_.push_back(Floor());

  floors_[0].addMap(TileMap("level1.txt"));

  updateLevels();

  prop_.addState(0, "SOLID");
  prop_.addState(4, "SOLID");
  prop_.addState(14, "ITEM");
}

void Game::updateLevels(){

  floors_[currentFloor_].getMap(currentMap_)->fillMap();
  drawableResources_.push_back(floors_[currentFloor_].getMap(currentMap_));
}

void Game::drawAll(sf::RenderWindow& window) const{

  for(auto target : drawableResources_)
    window.draw(*target);
}

void Game::showMenu(){
  //TODO
}

void Game::manageInput(sf::RenderWindow& window, sf::Event& event){

  while (window.pollEvent(event)){

      if (event.type == sf::Event::Closed)
          window.close();
  }

  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
    p1_.setDir(Player::Direction::Left);
    //s.move(-5,0);
    p1_.setLineSheet(2);
  }

  else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
    p1_.setDir(Player::Direction::Right);
    p1_.setLineSheet(4);

  }

  else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
    p1_.setDir(Player::Direction::Up);
    p1_.setLineSheet(1);

  }

  else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
    p1_.setDir(Player::Direction::Down);
    p1_.setLineSheet(3);
  }

  else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    p1_.attack();

  else{
    p1_.setLineSheet(1);
    p1_.setDir(Player::Direction::None);
  }
}

void Game::manageCollision(sf::RenderWindow& window){

  if(!Collision::makeTilesSolidWithState(p1_, *floors_[currentFloor_].getMap(currentMap_), prop_, p1_.getMV(), "SOLID", window))
    p1_.move();

    Collision::collisionWithItem(p1_, *floors_[currentFloor_].getMap(currentMap_), prop_, items_, "ITEM", window);

    // Projectiles collisions

    if(p1_.hasProj()){

      for(size_t k = 0; k < p1_.getTabProj().size(); k++){

        if(Collision::makeTilesSolidWithState(p1_.getTabProj()[k], *floors_[currentFloor_].getMap(currentMap_), prop_, p1_.getTabProj()[k].getMV(), "SOLID", window))
          p1_.deleteProj(k); // Si collision avec objet on detruit le projectile
      }
    }
}

void Game::manageAnimation(){

  if(p1_.getDir() != Player::Direction::None)
    p1_.animate();
}

void Game::start(){

  std::size_t indexLevel {};

  sf::RenderWindow window { sf::VideoMode(getSizeWindow(*floors_[currentFloor_].getMap(currentMap_), sf::Vector2u(10,10)).x, getSizeWindow(*floors_[currentFloor_].getMap(currentMap_), sf::Vector2u(10,10)).y), "RobLike" };
  window.setFramerateLimit(60);

  PassiveItem item1 {};
  items_.push_back(&item1);

  while(window.isOpen()){

    sf::Event event;
    manageInput(window, event);
    manageAnimation();
    manageCollision(window);

    p1_.moveProjectile();

    window.clear();
    drawAll(window);
    window.display();
  }

}

sf::Vector2f Game::getSizeWindow(const TileMap& map, const sf::Vector2u& numberTiles) const{

  return sf::Vector2f(static_cast<float>(numberTiles.x * map.getSizeOneSprite().x), static_cast<float>(numberTiles.y * map.getSizeOneSprite().y));
}
