#include "monster.hpp"
#include <cmath>

Monster::Monster() : Monster("error404.png", sf::Vector2f(0,0), 0, 0, 0, sf::Vector2u(1,1), AI::None)
{}

Monster::Monster(const std::string& pathTexture, const sf::Vector2f& pos, int health, unsigned int speed, int damage, const sf::Vector2u& dimSheet, AI ai) :
 health_(health),
 pathTexture_(pathTexture),
 speed_(speed),
 velocityVect_(speed_,speed_),
 damage_(damage),
 dimSheet_(dimSheet),
 lineSheet_(1),
 anim_(sprite_, dimSheet),
 ai_(ai){

  if(!texture_.loadFromFile(pathTexture))
    std::cerr << "Erreur texture monstre";
  else{
    sprite_.setTexture(texture_);
    anim_.setSpriteSheet(sprite_);
    anim_.setDim(dimSheet_);
    anim_.setFrame(150);
  }

  setBase(sf::Vector2u(2,3));
  setPosition(pos);
}

Monster::Monster(const Monster& monster) :
  pathTexture_(monster.pathTexture_),
  monsterName_(monster.monsterName_),
  sprite_(monster.sprite_),
  dimSheet_(monster.dimSheet_),
  health_(monster.health_),
  speed_(monster.speed_),
  damage_(monster.damage_),
  lineSheet_(monster.lineSheet_),
  anim_(sprite_, monster.dimSheet_),
  dir_(monster.dir_),
  velocityVect_(monster.velocityVect_),
  ai_(monster.ai_){

  if(!texture_.loadFromFile(monster.pathTexture_))
    std::cerr << "Erreur texture monstre";

  else{
    sprite_.setTexture(texture_);
    anim_.setSpriteSheet(sprite_);
    anim_.setDim(dimSheet_);
    anim_.setFrame(150);
  }

  std::cout << "COPY MONSTER" << std::endl;
}

Monster::~Monster(){

  std::cout << "Destruct Monster" << std::endl;
}

Monster& Monster::operator=(const Monster& monster){

  return *this;
}

void Monster::setPosition(const sf::Vector2f& v){

  sprite_.setPosition(v.x, v.y);
}

void Monster::Monster::move(const sf::Vector2f& dv){

  sprite_.move(dv.x, dv.y);
}

void Monster::setSpeed(int speed){
  speed_ = speed;
  velocityVect_ = sf::Vector2i(speed_, speed_);
}

void Monster::setDimSheet(const sf::Vector2u& dimSheet){

  dimSheet_ = dimSheet;
}

void Monster::setLineSheet(std::size_t lineSheet){

  lineSheet_ = lineSheet;
}

void Monster::setBase(const sf::Vector2u& base){

  anim_.setBase(base);
}

void Monster::animate(){

  anim_.playAnimationLine(lineSheet_);
}

void Monster::setAI(AI ai){

  ai_ = ai;
}

void Monster::activeAI(const Collidable& c, const Collidable& c2){

  if(ai_ == AI::Tracking)
    track(c, c2);
  else if(ai_ == AI::Runaway)
    runaway(c, c2);
  else
  {}
}

void Monster::track(const Collidable& c, const Collidable& c2){

  sf::Vector2f posMonster { sprite_.getPosition() };
  sf::Vector2f posTarget { c.getBox().left, c.getBox().top };
  sf::Vector2f posTarget2 { c2.getBox().left, c.getBox().top };

  // Cette condition permet de faire en sorte que le monstre suive le joueur le plus proche de sa position actuelle

  if(std::sqrt((posTarget.x - posMonster.x) * (posTarget.x - posMonster.x) + (posTarget.y - posMonster.y) * (posTarget.y - posMonster.y)) >
     std::sqrt((posTarget2.x - posMonster.x) * (posTarget2.x - posMonster.x) + (posTarget2.y - posMonster.y) * (posTarget2.y - posMonster.y)))
     posTarget = posTarget2;

  if(posMonster.x > posTarget.x){
    velocityVect_.x = -speed_;
  }

  if(posMonster.x < posTarget.x){
    velocityVect_.x = speed_;
    lineSheet_ = 2;
  }
  if(posMonster.y > posTarget.y){
    velocityVect_.y = -speed_;
  }
  if(posMonster.y < posTarget.y){
    velocityVect_.y = speed_;
    lineSheet_ = 1;
  }

  if(posMonster.x == posTarget.x && posMonster.y == posTarget.y)
    velocityVect_ = sf::Vector2i(0,0);

  sprite_.move(velocityVect_.x, velocityVect_.y);
}

void Monster::runaway(const Collidable& c, const Collidable& c2){

  sf::Vector2f posMonster { sprite_.getPosition() };
  sf::Vector2f posTarget { c.getBox().left, c.getBox().top };
  sf::Vector2f posTarget2 { c2.getBox().left, c.getBox().top };

  // Cette condition permet de faire en sorte que le monstre suive le joueur le plus proche de sa position actuelle

  if(std::sqrt((posTarget.x - posMonster.x) * (posTarget.x - posMonster.x) + (posTarget.y - posMonster.y) * (posTarget.y - posMonster.y)) >
     std::sqrt((posTarget2.x - posMonster.x) * (posTarget2.x - posMonster.x) + (posTarget2.y - posMonster.y) * (posTarget2.y - posMonster.y)))
     posTarget = posTarget2;

  if(posMonster.x > posTarget.x){
    velocityVect_.x = speed_;
  }

  if(posMonster.x < posTarget.x){
    velocityVect_.x = -speed_;
    lineSheet_ = 2;
  }
  if(posMonster.y > posTarget.y){
    velocityVect_.y = speed_;
  }
  if(posMonster.y < posTarget.y){
    velocityVect_.y = speed_;
    lineSheet_ = 1;
  }

  if(posMonster.x == posTarget.x && posMonster.y == posTarget.y)
    velocityVect_ = sf::Vector2i(0,0);

  sprite_.move(velocityVect_.x, velocityVect_.y);
}

int Monster::getDamage() const{

  return damage_;
}

void Monster::getHealthDamage(int damage){

  health_ -= damage;

  if(health_ <= 0)
    health_ = 0;
}

bool Monster::isAlive() const{

  return health_ > 0;
}

int Monster::getHealth() const{

  return health_;
}
void Monster::draw(sf::RenderTarget& target, sf::RenderStates states) const{

  target.draw(sprite_, states);
}

sf::FloatRect Monster::getBox() const{

  return sf::FloatRect(sprite_.getGlobalBounds().left, sprite_.getGlobalBounds().top, sprite_.getTexture()->getSize().x/dimSheet_.x, sprite_.getTexture()->getSize().y/dimSheet_.y);
}
