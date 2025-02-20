#ifndef PROJECTILE_HPP_INCLUDED
#define PROJECTILE_HPP_INCLUDED

#include <string>
#include "collidable.hpp"

/*** ~ Class Projectile ~

La classe Projectile correspond à un seul sf::CircleShape et modélise ce projectile
-> La classe Player s'occupera de construire une agrégation d'objets Projectile ***/

class Projectile : public sf::Drawable, public Collidable{

public:

  Projectile();
  Projectile(unsigned int speed);
  Projectile(float x, float y, float direction, int speed, int radiusProj, const sf::Color& colorProj);

  virtual ~Projectile() = default;
  void move();
  void move(const sf::Vector2f& target); // En cas de tir homing -> suivi de la position d'une cible
  void setSpeed(unsigned int speed);
  sf::Vector2f getMV() const;
  void increaseRadius(int radius);
  void changeColor(const sf::Color& color);
  void increaseSpeed(int speed);
  void setBox(const sf::FloatRect& box);
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
  virtual sf::FloatRect getBox() const override;

private:
  sf::CircleShape circle_;
  sf::Color color_;
  float dir_;
  int speed_;
};

#endif
