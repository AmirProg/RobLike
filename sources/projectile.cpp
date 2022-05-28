#include "projectile.hpp"

Projectile::Projectile() : Projectile(10)
{}

Projectile::Projectile(unsigned int speed) : Projectile(300,400, 0, speed){

  circle_.setFillColor(sf::Color::Red);
  circle_.setPosition(300,400);

  circle_.setRadius(3);
}

Projectile::Projectile(float x, float y, float direction, int speed) : speed_(speed), dir_(direction){

  circle_.setRadius(3);
  circle_.setFillColor(sf::Color::White);
  circle_.setPosition(x,y);
}

void Projectile::move(){

  if(dir_ == 180.0) // right
    circle_.move(-speed_,0);
  if(dir_ == 0.0) // left
    circle_.move(speed_,0);
  if(dir_ == 90.0)  // up
    circle_.move(0,-speed_);
  if(dir_ == 270.0) // down
    circle_.move(0, speed_);
  else
    circle_.move(0,0);
}

void Projectile::setSpeed(unsigned int speed){

  speed_ = speed;
}

sf::Vector2f Projectile::getMV() const{

  if(dir_ == 0) // left
    return sf::Vector2f(-speed_,0);
  if(dir_ == 180) // right
    return sf::Vector2f(speed_,0);
  if(dir_ == 90)  // up
    return sf::Vector2f(0,-speed_);
  if(dir_ == 270) // down
    return sf::Vector2f(0, speed_);
  else
    return sf::Vector2f(0,0);
}

void Projectile::draw(sf::RenderTarget& target, sf::RenderStates states) const{

  target.draw(circle_, states);
}

sf::FloatRect Projectile::getBox() const{

  return sf::FloatRect(circle_.getGlobalBounds().left, circle_.getGlobalBounds().top, circle_.getGlobalBounds().width, circle_.getGlobalBounds().height);
}
