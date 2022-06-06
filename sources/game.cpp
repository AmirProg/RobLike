#include "game.hpp"
#include <vector>
#include <numeric>
#include <string_view>

Game::Game() :
  p1_("Joueur 1", 3, 10, "character_astronaut_v2.png", sf::Vector2u(4,4)),
  p2_("Joueur 2", 3, 10, "perso.png", sf::Vector2u(9,4)),
  currentMap_(0),
  currentFloor_(0),
  menu_(sf::Vector2u(0,0), "akashi.ttf"),
  playing_(false){

  buildLevels();

  p1_.setBase(sf::Vector2u(1,1));
  p2_.setBase(sf::Vector2u(1,1));

  players_.push_back(&p1_);
  players_.push_back(&p2_);
  drawableResources_.push_back(&p1_);
  drawableResources_.push_back(&p2_);

  loadBasicMonsters();
}

void Game::buildLevels(){

  floors_.clear();

  floors_.push_back(Floor());

  floors_[0].addMap(TileMap("level1.txt"));
  floors_[0].addMap(TileMap("treasureRoom.txt"));
  floors_[0].addMap(TileMap("level3.txt"));

  updateLevels();

  prop_.addState(2, "SOLID");
  prop_.addState(4, "SOLID");
  prop_.addState(5, "SOLID");
  prop_.addState(6, "SOLID");
  prop_.addState(7, "SOLID");
  prop_.addState(12, "SOLID");
  prop_.addState(13, "SOLID");
  prop_.addState(14, "SOLID");
  prop_.addState(15, "SOLID");
  prop_.addState(0, "ITEM");
}

void Game::updateLevels(){

  floors_[currentFloor_].getMap(currentMap_)->fillMap();
  currentTileMap_ = floors_[currentFloor_].getMap(currentMap_);
}

/* Ces fonctions sont répétitives, l'idée serait plus tard de lire le fichier texte level.txt
   et ce fichier texte aurait les informations de la map mais aussi des monstres du niveau actuel, il suffirait de le charger */

void Game::loadBasicMonsters(){

  if(currentMap_ == 0){

    Monster zombie("zombie_big.png", sf::Vector2f(100,100), 40, static_cast<unsigned int>(1), 10, sf::Vector2u(3,4), Monster::AI::Tracking);
    monsters_.push_back(zombie);
  }

  else if(currentMap_ == 2){

    Monster robot("robot_1.png", sf::Vector2f(100,100), 100, static_cast<unsigned int>(1), 30, sf::Vector2u(4,4), Monster::AI::Tracking);
    Monster robot2("seigneur_gobelin.png", sf::Vector2f(450,400), 50, static_cast<unsigned int>(1), 20, sf::Vector2u(3,4), Monster::AI::Tracking);

    monsters_.push_back(robot);
    monsters_.push_back(robot2);
  }
}

void Game::handleMonstersLogic(const sf::RenderWindow& window){

  for(auto& m : monsters_)
    m.activeAI(p1_, p2_);
}

void Game::drawAll(sf::RenderWindow& window) const{

  window.draw(*currentTileMap_);

  for(const auto& target : drawableResources_)
    window.draw(*target);

  for(const auto& target : monsters_)
    window.draw(target);
}

void foo(){

}

void Game::play(){
  playing_ = true;
}

void quit(){


}

void Game::showMenu(){

  menu_.add("Play", std::bind(&Game::start, this)); // Comme la fonction start est membre de Game, il faut lier cette méthode à un objet (ici l'objet pointeur this)
  menu_.add("Credits", foo);
}

void Game::manageInput(sf::RenderWindow& window, sf::Event& event){

  while (window.pollEvent(event)){

      if (event.type == sf::Event::Closed)
          window.close();
  }

  /* Si on voulait mettre en place une IA, c'est assez simple ici on opterait pour le même système que les monstres actuellement
  Si le joueur 2 est une IA il va suivre le joueur (voir méthode track de Monstre, on ne gérerait pas les input ici) */

  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
    p1_.setDir(Player::Direction::Left);
    p1_.setLineSheet(2);
  }

  else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
    p1_.setDir(Player::Direction::Right);
    p1_.setLineSheet(3);

  }

  else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
    p1_.setDir(Player::Direction::Up);
    p1_.setLineSheet(4);

  }

  else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
    p1_.setDir(Player::Direction::Down);
    p1_.setLineSheet(1);
  }

  else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    p1_.attack();

  else{
    p1_.setLineSheet(1);
    p1_.setDir(Player::Direction::None);
  }

  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
    p2_.setDir(Player::Direction::Left);
    p2_.setLineSheet(2);
  }

  else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
    p2_.setDir(Player::Direction::Right);
    p2_.setLineSheet(4);

  }

  else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
    p2_.setDir(Player::Direction::Up);
    p2_.setLineSheet(1);

  }

  else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
    p2_.setDir(Player::Direction::Down);
    p2_.setLineSheet(3);
  }

  else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad0))
    p2_.attack();

  else{
    p2_.setLineSheet(1);
    p2_.setDir(Player::Direction::None);
  }
}

void Game::manageCollision(sf::RenderWindow& window){

    for(auto p : players_){

      int index = 0;

      if(!Collision::makeTilesSolidWithState(*p, *floors_[currentFloor_].getMap(currentMap_), prop_, p->getMV(), "SOLID", window))
        p->move();


      Collision::collisionWithItem(*p, floors_[currentFloor_].getMap(currentMap_), prop_, items_, "ITEM", window, itemCollectedDelay_);

      for(const auto& monster : monsters_){

        if(Collision::intersectEntity(*p, monster))
          p->getHealthDamage(monster.getDamage());
      }

      for(size_t k = 0; k < p->getTabProj().size(); k++){

        if(Collision::makeTilesSolidWithState(p->getTabProj()[k], *floors_[currentFloor_].getMap(currentMap_), prop_, p->getTabProj()[k].getMV(), "SOLID", window)){
            p->deleteProj(k); // Si collision avec objet on detruit le projectile
            break;
        }

        for(std::size_t m = 0; m < std::size(monsters_); m++){

            if(Collision::intersectEntity(monsters_[m], p->getTabProj()[k])){

              monsters_[m].getHealthDamage(p->getDamage()); // On inflige les dégâts du joueur au monstre

              if(!monsters_[m].isAlive())
                monsters_.erase(std::begin(monsters_) + m); // BUG SI ON TUE LE PREMIER MONTRE DU TABLEAU...

              p->deleteProj(k); // Si collision avec un monstre on detruit le projectile
              break;
            }
        }
      }
  }

  /* Gère le changement de niveau - si un des deux joueurs touche le haut de la fenêtre et que le niveau est fini
  -> on change */

    Collision::makeWindowSolid(p1_, window);

    if(!areMonstersAlive() && (Collision::intersectWindowTop(p1_) || Collision::intersectWindowTop(p2_)) && mapTransition_.getElapsedTime().asMilliseconds() > 200){

      if(currentMap_ < 2){

        p1_.setPosition(sf::Vector2f(300,400));
        p2_.setPosition(sf::Vector2f(300,400));

        currentMap_++;
        monsters_.clear();
        updateLevels();

        loadBasicMonsters();
      }

      mapTransition_.restart();
  }
}

void Game::manageAnimation(){

  for(auto p : players_){

    if(p->getDir() != Player::Direction::None)
      p->animate();

    p->moveProjectile();
  }

  for(auto& m : monsters_)
    m.animate();
}

void Game::manageGameOver(sf::RenderWindow& window, const sf::Font& font){

  if(!p1_.isAlive() || !p2_.isAlive()){
    gameOver.setFont(font);
    gameOver.setString("GAME OVER");
    gameOver.setCharacterSize(30);
    gameOver.setFillColor(sf::Color::Red);
    gameOver.setPosition(window.getSize().x/2 - 100 , window.getSize().y/2);

    drawableResources_.clear();
    monsters_.clear();
    drawableResources_.push_back(&gameOver);

    if(timeGameOver_.getElapsedTime().asSeconds() > 5)
      window.close();

    std::cout << "eeee" <<std::endl;
  }

  else
    timeGameOver_.restart();
}

bool Game::areMonstersAlive() const{

  bool alive { false };
  for(const auto& m : monsters_)
    alive = m.isAlive();

  return alive;
}

void speedUp(Player& p){

  p.setSpeed(p.getSpeed() + 1);
}

void speedProjUp(Player& p){

  p.increaseSpeedProj(1);
}

void radiusUp(Player& p){

  p.increaseRadiusProj(6);
}

void damageUp(Player& p){

  p.increaseDamage(5);
}

void fireRateUp(Player& p){

  p.increaseFireRate(30);
}

void laserGunFunc(Player& p){

  damageUp(p);
  radiusUp(p);
  fireRateUp(p);
  speedProjUp(p);
  p.changeColorProj(sf::Color::Blue);
}

void bloodyFunc(Player& p){

  p.changeColorProj(sf::Color::Red);
}

void spaceGodFunc(Player& p){

  damageUp(p);
  damageUp(p);
  damageUp(p);
  damageUp(p);
  damageUp(p);
  radiusUp(p);
  radiusUp(p);
  radiusUp(p);
  radiusUp(p);
  fireRateUp(p);
  fireRateUp(p);
  fireRateUp(p);
  fireRateUp(p);
  speedProjUp(p);
  speedProjUp(p);
  speedProjUp(p);
  speedUp(p);
  p.changeColorProj(sf::Color::Yellow);
}

void Game::start(){
  std::size_t indexLevel {};

  sf::RenderWindow window { sf::VideoMode(getSizeWindow(*floors_[currentFloor_].getMap(currentMap_), sf::Vector2u(10,10)).x, getSizeWindow(*floors_[currentFloor_].getMap(currentMap_), sf::Vector2u(10,10)).y), "RobLike" };
  window.setFramerateLimit(90);

  sf::Font font;

  if(!font.loadFromFile("akashi.ttf"))
    std::cerr << "Erreur font" << std::endl;

  p1_.setFont(font);
  p2_.setFont(font);

  p1_.setGuiPosition(Player::PositionGUI::Up);
  p2_.setGuiPosition(Player::PositionGUI::Down);

  if(!playing_){
    menu_.setSizeWindow(window.getSize());
    showMenu();
  }

  PassiveItem spaceBoots {"Space boots", "Speed UP!", 1, false, speedUp};
  PassiveItem excitedPill {"Excited Pill", "Fire rate up !", 1, false, fireRateUp};
  PassiveItem bloody {"Bloody", "Arrgh ! Vous crachez du sang !", 0, false, bloodyFunc};
  ActiveItem laserGun {"Laser Gun", "Un pirate de l'espace est né !", 3, false, laserGunFunc};
  ActiveItem spaceGod("Space God", "Je suis tout", 5, true, spaceGodFunc);

  items_.push_back(&spaceBoots);
  items_.push_back(&excitedPill);
  items_.push_back(&bloody);
  items_.push_back(&laserGun);
  items_.push_back(&spaceGod);

  while(window.isOpen()){

    if(playing_){ // playing permet de savoir si on doit mettre le jeu en pause ou non (la logique du jeu s'arrête)
      sf::Event event;
      manageInput(window, event);
      manageAnimation();
      handleMonstersLogic(window);
      manageCollision(window);
    }

    else
      menu_.manageCursor(playing_, window);

    manageGameOver(window, font);

    window.clear();

    if(!playing_)
      window.draw(menu_);
    else
      drawAll(window);

    window.display();
  }
}

sf::Vector2f Game::getSizeWindow(const TileMap& map, const sf::Vector2u& numberTiles) const{

  return sf::Vector2f(static_cast<float>(numberTiles.x * map.getSizeOneSprite().x), static_cast<float>(numberTiles.y * map.getSizeOneSprite().y));
}
