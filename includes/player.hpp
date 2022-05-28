#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include <string>
#include <vector>
#include "collidable.hpp"
#include "animation.hpp"
#include "projectile.hpp"

/*** ~ Class Player

Représente les joueurs du jeu, les caractéristiques des personnages, leurs animations, leurs armes...
L'arme est considérée comme étant liée au personnage et à ses caractéristiques :
-> Le personnage tire naturellement des objets de type Projectile, il ne possède pas d'objet Arme qui lui permettrait de le faire
Modifier les caractéristiques de Player pourra donc modifier les caractéristiques de ses projectiles ***/

class Player : public sf::Drawable, public Collidable, public NonCopyable{

public:
  enum class Direction { Left, Right, Up, Down, None };

  Player();
  Player(const std::string& playerName, unsigned int speed, const std::string& weapon);
  Player(const std::string& playerName, unsigned int speed, const std::string& weapon, const std::string& pathTexture, const sf::Vector2u&);
  virtual ~Player() = default;
  void move();
  void attack(); // Throw through the player direction
  void setDir(Direction dir);
  void setPosition(const sf::Vector2f& pos);
  void setSpeed(int speed);
  void setFireRate(unsigned int fireRate);
  void setLineSheet(std::size_t lineSheet);
  void setDimSheet(const sf::Vector2u& dimSheet);
  void setBase(const sf::Vector2u& base);
  void animate();
  void moveProjectile();
  bool hasProj();
  void deleteProj(std::size_t k); // Supprime le k-eme projectile
  sf::Vector2f getMV() const;
  Direction getDir() const;
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
  virtual sf::FloatRect getBox() const override;
  std::vector<Projectile> getTabProj() const;

private:

  std::string playerName_;
  sf::Texture textureSprite_;
  sf::Sprite spritePlayer_;
  Direction dir_;
  int speed_;
  unsigned int fireRate_; // Cadence de tir du joueur en ms
  std::string weapon_;
  float angle_;
  Animation anim_;
  std::size_t lineSheet_;
  sf::Vector2u dimSheet_;
  std::vector<Projectile> tabProjectile_ = {};

  sf::Clock clockPlayer_;
};

#endif
