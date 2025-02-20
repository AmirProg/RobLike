#include "player.hpp"
#include <iostream>
#include <string>
#include "monster.hpp"
#include <cmath>

Player::Player() : Player("Sans nom", 0, 0)
{}

/* Le nombre de sprites dans la sheet est considéré unitaire sauf indication contraire */

Player::Player(const std::string& playerName, unsigned int speed, int damage) : playerName_(playerName), speed_(speed), dir_(Direction::None), anim_(spritePlayer_, sf::Vector2u(1,1)), lineSheet_(1), dimSheet_(sf::Vector2u(1,1)), fireRate_(200), health_(200), hpText_(), damage_(damage), radiusProj_(3), colorProj_(sf::Color::White){
  spritePlayer_.setPosition(300,400);
  tabProjectile_.clear();
}

Player::Player(const std::string& playerName, unsigned int speed, int damage, const std::string& pathTexture, const sf::Vector2u& dimSheet) : Player(playerName, speed, damage){

  dimSheet_ = dimSheet;

  if(!textureSprite_.loadFromFile(pathTexture))
    std::cerr << "Erreur texture player" << std::endl;

  else{
    spritePlayer_.setTexture(textureSprite_);
    anim_.setSpriteSheet(spritePlayer_);
    anim_.setDim(dimSheet_);
    anim_.setFrame(150);
  }

  if(!textureGui_.loadFromFile("resources/items.png"))
    std::cerr << "Erreur texture player" << std::endl;

  spriteHealth_.setTexture(textureGui_);
  spriteHealth_.setPosition(0,0);
  spriteHealth_.setTextureRect((sf::IntRect(0,64,64,64)));
}

void Player::setFont(const sf::Font& font){

  hpText_.setFont(font);
  hpText_.setString(std::to_string(health_));
  hpText_.setCharacterSize(25);
  hpText_.setFillColor(sf::Color::Red);
  hpText_.setPosition(60,12);
}

void Player::move(){

  if(dir_ == Direction::Left){
    spritePlayer_.move(-speed_,0);
    angle_ = 180;
  }
  if(dir_ == Direction::Right){
    spritePlayer_.move(speed_,0);
    angle_ = 0;
  }
  if(dir_ == Direction::Up){
    spritePlayer_.move(0,-speed_);
    angle_ = 90;
  }
  if(dir_ == Direction::Down){
    spritePlayer_.move(0, speed_);
    angle_ = 270;
  }
  else
    spritePlayer_.move(0,0);
}

sf::Vector2f Player::getPositionNearestMonster(const std::vector<Monster*>& monsters){

  /* On calcule la position du monstre le plus proche du joueur courant */

  std::size_t index = 0;
  float currentMin { std::sqrt((monsters[0]->getBox().left - getBox().left) * (monsters[0]->getBox().left - getBox().left) +
                     (monsters[0]->getBox().top - getBox().top) * (monsters[0]->getBox().top - getBox().top)) };

  for(std::size_t k = 1; k < std::size(monsters); ++k){

    float temp = { std::sqrt((monsters[k]->getBox().left - getBox().left) * (monsters[k]->getBox().left - getBox().left) +
                   (monsters[k]->getBox().top - getBox().top) * (monsters[k]->getBox().top - getBox().top)) };

    if(temp < currentMin){
      currentMin = temp;

      index = k;
    }
  }

  return sf::Vector2f(monsters[index]->getBox().left, monsters[index]->getBox().top);
}

void Player::moveProjectile(const std::vector<Monster*>& monsters){

  for(size_t k = 0; k < tabProjectile_.size(); k++){

      if(!homing_ || std::size(monsters) <= 0)
        tabProjectile_[k].move();
      else
        tabProjectile_[k].move(getPositionNearestMonster(monsters));
  }
}

void Player::attack(){

  if(clockPlayer_.getElapsedTime().asMilliseconds() > fireRate_){

    tabProjectile_.push_back(Projectile(getBox().left + getBox().width/2, getBox().top + getBox().height/2, angle_, 3, radiusProj_, colorProj_));
    clockPlayer_.restart();
  }
}

void Player::getHealthDamage(int damage){

  if(invuFrame_.getElapsedTime().asMilliseconds() > 800 && health_ > 0){
    health_ -= damage;
    invuFrame_.restart();
  }

  if(health_ <= 0)
    health_ = 0;

  updateCharac();
}

bool Player::isAlive() const{

  return health_ > 0;
}

void Player::updateCharac(){

  hpText_.setString(std::to_string(health_));
}

void Player::setDir(Direction dir){

  dir_ = dir;
}

void Player::setPosition(const sf::Vector2f& pos){

  spritePlayer_.setPosition(pos);
}

void Player::setGuiPosition(PositionGUI pos){

  if(pos == PositionGUI::Up){

    hpText_.setPosition(hpText_.getPosition().x, 12);
    spriteHealth_.setPosition(spriteHealth_.getPosition().x, 0);
  }

  else{

    hpText_.setPosition(hpText_.getPosition().x, 592);
    spriteHealth_.setPosition(0,580);
  }
}

void Player::setSpeed(int speed){

  speed_ = speed;
}

void Player::setFireRate(unsigned int fireRate){

  fireRate_ = fireRate;
}

void Player::setDimSheet(const sf::Vector2u& dimSheet){

  dimSheet_ = dimSheet;
}

void Player::setLineSheet(std::size_t lineSheet){

  lineSheet_ = lineSheet;
}

void Player::setBase(const sf::Vector2u& base){

  anim_.setBase(base);
}

int Player::getDamage() const{

  return damage_;
}

int Player::getSpeed() const{

  return speed_;
}

void Player::increaseDamage(int damage){

  damage_ += damage;
}

void Player::increaseRadiusProj(int radius){

  radiusProj_ += radius;
}

void Player::changeColorProj(const sf::Color& color){

  colorProj_ = color;
}

void Player::increaseSpeedProj(int speed){

  for(auto& p : tabProjectile_)
    p.increaseSpeed(speed);
}

void Player::increaseFireRate(unsigned int fireRate){

  fireRate_ -= fireRate;
}

void Player::healthUp(int hp){

  health_ += hp;
  updateCharac();
}

void Player::setHoming(bool homing){

  homing_ = homing;
}

void Player::animate(){

  anim_.playAnimationLine(lineSheet_);
}

bool Player::hasProj(){ // on teste si le joueur a des projectiles encore "vivants"

  return tabProjectile_.size() > 0;
}

void Player::deleteProj(std::size_t k){

    if(std::size(tabProjectile_) > k)
      tabProjectile_.erase(std::begin(tabProjectile_)+k);
}

sf::Vector2f Player::getMV() const{

  if(dir_ == Direction::Left)
    return sf::Vector2f(-speed_,0);
  if(dir_ == Direction::Right)
    return sf::Vector2f(speed_,0);
  if(dir_ == Direction::Up)
    return sf::Vector2f(0,-speed_);
  if(dir_ == Direction::Down)
    return sf::Vector2f(0, speed_);
  else
    return sf::Vector2f(0,0);
}

Player::Direction Player::getDir() const{

  return dir_;
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const{


  target.draw(spritePlayer_, states);

  for(size_t k = 0; k < tabProjectile_.size(); k++)
      target.draw(tabProjectile_[k], states);

  target.draw(spriteHealth_, states);
  target.draw(hpText_, states);
}

sf::FloatRect Player::getBox() const{

  return sf::FloatRect(spritePlayer_.getGlobalBounds().left, spritePlayer_.getGlobalBounds().top, spritePlayer_.getTexture()->getSize().x/dimSheet_.x, spritePlayer_.getTexture()->getSize().y/dimSheet_.y);
}

std::vector<Projectile> Player::getTabProj() const{

  return tabProjectile_;
}
