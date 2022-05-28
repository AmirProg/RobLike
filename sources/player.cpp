#include "player.hpp"
#include <iostream>

Player::Player() : Player("Sans nom", 10, "Epee brisee")
{}

/* Le nombre de sprites dans la sheet est considéré unitaire sauf indication contraire */

Player::Player(const std::string& playerName, unsigned int speed, const std::string& weapon) : playerName_(playerName), speed_(speed), weapon_(weapon), dir_(Direction::None), anim_(spritePlayer_, sf::Vector2u(1,1)), lineSheet_(1), dimSheet_(sf::Vector2u(1,1)), fireRate_(200){
  spritePlayer_.setPosition(300,400);
  tabProjectile_.clear();
}

Player::Player(const std::string& playerName, unsigned int speed, const std::string& weapon, const std::string& pathTexture, const sf::Vector2u& dimSheet) : Player(playerName, speed, weapon){

  dimSheet_ = dimSheet;

  if(!textureSprite_.loadFromFile(pathTexture))
    std::cerr << "Erreur texture player" << std::endl;

  else{
    spritePlayer_.setTexture(textureSprite_);
    anim_.setSpriteSheet(spritePlayer_);
    anim_.setDim(dimSheet_);
    anim_.setFrame(150);
  }

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

void Player::moveProjectile(){

  for(size_t k = 0; k < tabProjectile_.size(); k++)
      tabProjectile_[k].move();
}

void Player::attack(){

  if(clockPlayer_.getElapsedTime().asMilliseconds() > fireRate_){

    tabProjectile_.push_back(Projectile(getBox().left, getBox().top, angle_, 3));
    clockPlayer_.restart();

  }
}

void Player::setDir(Direction dir){

  dir_ = dir;
}

void Player::setPosition(const sf::Vector2f& pos){

  spritePlayer_.setPosition(pos);
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

void Player::animate(){

  anim_.playAnimationLine(lineSheet_);
}

bool Player::hasProj(){ // on teste si le joueur a des projectiles encore "vivants"

  if(tabProjectile_.size() > 0)
    return true;
  else
    return false;
}

void Player::deleteProj(std::size_t k){

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
}

sf::FloatRect Player::getBox() const{

  return sf::FloatRect(spritePlayer_.getGlobalBounds().left, spritePlayer_.getGlobalBounds().top, spritePlayer_.getTexture()->getSize().x/dimSheet_.x, spritePlayer_.getTexture()->getSize().y/dimSheet_.y);
}

std::vector<Projectile> Player::getTabProj() const{

  return tabProjectile_;
}
