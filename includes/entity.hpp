#ifndef ENTITY_HPP_INCLUDED
#define ENTITY_HPP_INCLUDED

#include "collidable.hpp"
#include <SFML/Graphics.hpp>

class Entity : public sf::Drawable, public sf::Transformable, public Collidable{

public:
  Entity();
  Entity(const Entity&);
  virtual ~Entity() = default;

protected:

  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;
  virtual void setPosition(const sf::Vector2f&) = 0;
  virtual void move(const sf::Vector2f&) = 0;
};

#endif
