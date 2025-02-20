#include "menu.hpp"
#include <iostream>


Menu::Menu(const sf::Vector2u& sizeWindow) : sizeWindow_(sizeWindow), nbWidgets_(0), currentChoice_(1){

  widgets_.clear();

  cursor_.setRadius(5);
  cursor_.setFillColor(sf::Color::Yellow);
  cursor_.setPosition(sf::Vector2f(0,0));
  //menuTimer_.restart();
}

void Menu::add(const std::string& textStr, const std::function<void()>& func){

  sf::Text text;
  text.setFont(*font_);

  text.setCharacterSize(60);
  text.setFillColor(sf::Color::Red);
  text.setPosition(sizeWindow_.x/2-80, sizeWindow_.y/2 + 60 * nbWidgets_);
  text.setString(textStr);
  widgets_.push_back(std::pair<sf::Text, std::function<void()>>(text, func));
  cursor_.setPosition(sizeWindow_.x/2 - 90, sizeWindow_.y/2 + 30 * currentChoice_);
  nbWidgets_++;
}

void Menu::setFont(sf::Font* font){

  font_ = font;
}

void Menu::updateCursor(){

  for(std::size_t k = 0; k < nbWidgets_; ++k){
    if(k == currentChoice_ - 1)
      widgets_[k].first.setFillColor(sf::Color::Yellow);
    else
      widgets_[k].first.setFillColor(sf::Color::Red);
  }

  cursor_.setPosition(sizeWindow_.x/2 - 110, sizeWindow_.y/2 + 45 * currentChoice_);
}

void Menu::manageCursor(sf::RenderWindow& window){

  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){

    if(currentChoice_ == 1){
      window.close(); // On ferme le menu
    }

    activate(currentChoice_-1); // On lance la fonction associée au choix du menu
  }

  if(menuTimer_.getElapsedTime().asMilliseconds() > 100){

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){

      currentChoice_++;

      if(currentChoice_ > nbWidgets_)
        currentChoice_ = 1;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){

        currentChoice_--;
        if(currentChoice_ < 1)
          currentChoice_ = nbWidgets_;

    }

    updateCursor();
    menuTimer_.restart();
  }
}

void Menu::setSizeWindow(const sf::Vector2u& size){

  sizeWindow_ = size;
}
void Menu::activate(std::size_t k){

  assert(k < std::size(widgets_));

  widgets_[k].second();
}

std::size_t Menu::getNumberWidgets() const{

  return nbWidgets_;
}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const{

  // On dessine dans l'ordre inverse d'ajout au std::vector pour dessiner dans le bon ordre attendu
  int nb = nbWidgets_;

  for(auto w : widgets_)
    target.draw(w.first, states);

  target.draw(cursor_);
}
