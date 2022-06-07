#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include <string>
#include <vector>
#include "collidable.hpp"
#include "animation.hpp"
#include "projectile.hpp"

class Monster;

/*** ~ Class Player

Représente les joueurs du jeu, les caractéristiques des personnages, leurs animations, leurs armes...
L'arme est considérée comme étant liée au personnage et à ses caractéristiques :
-> Le personnage tire naturellement des objets de type Projectile, il ne possède pas d'objet Arme qui lui permettrait de le faire
Modifier les caractéristiques de Player pourra donc modifier les caractéristiques de ses projectiles ***/

class Player : public sf::Drawable, public Collidable, public NonCopyable{

public:

  enum class Direction { Left, Right, Up, Down, None };
  enum class PositionGUI { Up, Down, None };

  Player();
  Player(const std::string& playerName, unsigned int speed, int damage);
  Player(const std::string& playerName, unsigned int speed, int damage, const std::string& pathTexture, const sf::Vector2u&);
  virtual ~Player() = default;
  void move();
  void attack(); // Throw through the player direction
  void getHealthDamage(int damage);
  bool isAlive() const;
  void updateCharac(); // Va mettre à jour l'état des charactéristiques du personnage
  void setDir(Direction dir);
  void setPosition(const sf::Vector2f& pos);
  void setGuiPosition(PositionGUI pos);
  void setFont(const sf::Font& font);
  void setSpeed(int speed);
  void setFireRate(unsigned int fireRate);
  void setLineSheet(std::size_t lineSheet);
  void setDimSheet(const sf::Vector2u& dimSheet);
  void setBase(const sf::Vector2u& base);
  int getDamage() const;
  int getSpeed() const;
  void increaseDamage(int damage);
  void increaseRadiusProj(int radius);
  void changeColorProj(const sf::Color& color);
  void increaseSpeedProj(int speed);
  void increaseFireRate(unsigned int fireRate);
  void healthUp(int hp);
  void setHoming(bool homing);
  void animate();
  sf::Vector2f getPositionNearestMonster(const std::vector<Monster*>& monsters); // Obtient la position sur la fenêtre du monstre le plus proche (utile enc as de homing projectiles)
  void moveProjectile(const std::vector<Monster*>& monsters);
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
  sf::Texture textureGui_;
  sf::Font f;
  sf::Sprite spriteHealth_;
  sf::Text hpText_;
  sf::Sprite spritePlayer_;
  Direction dir_;
  int speed_;
  int damage_;
  int health_;
  unsigned int fireRate_; // Cadence de tir du joueur en ms
  float angle_;
  Animation anim_;
  std::size_t lineSheet_;
  sf::Vector2u dimSheet_;
  sf::Color colorProj_;
  int radiusProj_;
  std::vector<Projectile> tabProjectile_ = {};
  bool homing_ = false; // Tirs tête-chercheuse
  sf::Clock clockPlayer_;
  sf::Clock invuFrame_;
};

#endif
