#include <iostream>
#include "item.hpp"

Item::Item() : Item("NONE", "NONE EFFECT", -1, false, std::function<void(Player&)>())
{}

Item::Item(const std::string& name, const std::string& effect, int rarity, bool unique, const std::function<void(Player&)>& func) :
  name_(name),
  infoEffect_(effect),
  rarity_(rarity),
  func_(func)
{}

Item::Item(const std::string& pathTexture){

  if(itemTexture_.loadFromFile(pathTexture))
    std::cerr << "Erreur texture item" << std::endl;

  else
    itemSprite_.setTexture(itemTexture_);
}

Item::Item(const Item& item) {

  name_ = item.name_;
  infoEffect_ = item.infoEffect_;
  rarity_ = item.rarity_;
  unique_ = item.unique_;
  itemTexture_ = item.itemTexture_;
  itemSprite_ = item.itemSprite_;
}

sf::FloatRect Item::getBox() const{
  return sf::FloatRect();
}

bool Item::isUnique() const{
  return unique_;
}

void Item::draw(sf::RenderTarget& target, sf::RenderStates states) const{

  target.draw(itemSprite_, states);
}


/* PassiveItem */

PassiveItem::PassiveItem() : Item()
{}

PassiveItem::PassiveItem(const std::string& name, const std::string& effect, int rarity, bool unique, const std::function<void(Player&)>& func) : Item(name, effect, rarity, unique, func)
{}

void PassiveItem::info() const{

  std::cout << "ITEM TYPE : PASSIVE" << std::endl
            << "Name : " << name_ << std::endl
            << "Effect : " << infoEffect_ << std::endl
            << "Rareté : " << rarity_ << std::endl << std::endl;
}

void PassiveItem::activate(Player& player) const{ // Active l'effet de l'item sur le joueur l'ayant ramassé

  func_(player);
  info();
};

ActiveItem::ActiveItem() : Item()
{}

ActiveItem::ActiveItem(const std::string& name, const std::string& effect, int rarity, bool unique, const std::function<void(Player&)>& func) : Item(name, effect, rarity, unique, func)
{}

void ActiveItem::info() const{

  std::cout << "ITEM TYPE : ACTIVE" << std::endl
            << "Name : " << name_ << std::endl
            << "Effect : " << infoEffect_ << std::endl
            << "Rareté : " << rarity_ << std::endl << std::endl;
}

void ActiveItem::activate(Player& player) const{

  func_(player);
  info();
}
