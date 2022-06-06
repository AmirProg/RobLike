#ifndef MONSTER_HPP_INCLUDED
#define MONSTER_HPP_INCLUDED

#include "entity.hpp"
#include "animation.hpp"
#include <iostream>

/*** ~ Class Monster ~

Tous les monstres (ennemis, monstres alliés) hériteront de cette classe.
Deux classes de monstres se distinguent : monstre au corps à corps (MeleeMonster) et monstre à distance (ShooterMonster)
L'intelligence du monstre est liée à l'énumération AI, deux types pour le moment : runaway et tracking ***/

class Monster : public Entity{

public:

  enum class Direction { Left, Right, Up, Down, None };
  enum class AI { Runaway, Tracking, None };

  Monster();
  Monster(const std::string& pathTexture, const sf::Vector2f& pos, int health, unsigned int speed, int damage, const sf::Vector2u& dimSheet, AI ai);
  Monster(const Monster& monster);
  Monster& operator=(const Monster& monster);

  virtual ~Monster() = default;
  virtual void setPosition(const sf::Vector2f& v) override;
  virtual void move(const sf::Vector2f& dv) override;
  void setSpeed(int speed);
  void setDimSheet(const sf::Vector2u& dimSheet);
  void setLineSheet(std::size_t lineSheet);
  void setBase(const sf::Vector2u& base);
  void animate();
  void setAI(AI ai);
  void activeAI(const Collidable& c, const Collidable& c2);
  int getDamage() const;
  void getHealthDamage(int damage);
  bool isAlive() const;
  sf::Vector2i getMV() const;
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
  virtual sf::FloatRect getBox() const override;

private:

  std::string pathTexture_;
  sf::Texture texture_;
  sf::Sprite sprite_;
  std::string monsterName_;
  int health_;
  unsigned int speed_;
  sf::Vector2i velocityVect_;
  int damage_;
  Animation anim_;
  std::size_t lineSheet_;
  sf::Vector2u dimSheet_;
  Direction dir_;
  AI ai_;

  // Méthodes liées à l'intelligence du monstre

  void track(const Collidable& c, const Collidable& c2);
  void runaway(const Collidable& c, const Collidable& c2);
};

#endif
