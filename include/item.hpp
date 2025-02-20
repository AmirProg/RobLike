#ifndef ITEM_HPP_INCLUDED
#define ITEM_HPP_INCLUDED

/*** Classe Item

Représente tous les types d'items collectables par le joueur
- Mère de deux classes : * PassiveItem -> Représente les items passifs du joueur (ne modifie pas aux types de projectiles envoyés, seulement les stats du joueur)
                         * ActiveItem -> Représente les items actifs du joueur (modifie les projectiles envoyés)

***/

#include "collidable.hpp"
class Player;

class Item : public sf::Drawable, public Collidable{

public:

  Item();
  Item(const std::string& name, const std::string& effect, int rarity, bool unique, const std::function<void(Player&)>&);
  Item(const std::string& pathTexture);
  Item(const Item&);
  virtual ~Item() = default;
  virtual void info(sf::RenderWindow& window) const = 0;
  virtual void activate(Player& player, sf::RenderWindow& window, std::size_t& frame) const = 0; // Active l'effet de l'item sur le joueur l'ayant ramassé
  virtual sf::FloatRect getBox() const;
  virtual void setFont(sf::Font* font);
  bool isUnique() const;

protected:

  std::string name_;
  std::string infoEffect_;
  int rarity_;
  bool unique_;
  sf::Texture itemTexture_;
  sf::Sprite itemSprite_;
  int index_; // Correspond à son index dans le tableau de la map
  sf::Font* font_; // Police d'écriture d'affichage des infos de l'item lorsqu'il est loot
  std::function<void(Player&)> func_;
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};

class PassiveItem : public Item{

public:

  PassiveItem();
  PassiveItem(const std::string& name, const std::string& effect, int rarity, bool unique, const std::function<void(Player&)>& func);
  virtual ~PassiveItem() = default;
  virtual void info(sf::RenderWindow& window) const override;
  virtual void activate(Player& player, sf::RenderWindow& window, std::size_t& frame) const override; // Active l'effet de l'item sur le joueur l'ayant ramassé

private:

};

class ActiveItem : public Item{

public:

  ActiveItem();
  ActiveItem(const std::string& name, const std::string& effect, int rarity, bool unique, const std::function<void(Player&)>& func);
  virtual ~ActiveItem() = default;
  virtual void info(sf::RenderWindow& window) const override;
  virtual void activate(Player& player, sf::RenderWindow& window, std::size_t& frame) const override; // Active l'effet de l'item sur le joueur l'ayant ramassé

private:

};

#endif
