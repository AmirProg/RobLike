#ifndef COLLIDABLE_HPP_INCLUDED
#define COLLIDABLE_HPP_INCLUDED

/* Classe interface Collidable
   Représente les objets qui sont suceptibles de pouvoir être testé en collision */


#include <SFML/Graphics.hpp>

class Collidable{

public:

  Collidable() = default;

protected:

  virtual sf::FloatRect getBox() const = 0;

  sf::FloatRect hitBox_;
};

#endif
