#ifndef MENU_HPP_INCLUDED
#define MENU_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <map>
#include <functional>
#include "nonCopyable.hpp"
#include <cassert>

class Menu : public sf::Drawable{

public:

  Menu(const sf::Vector2u& sizeWindow);
  void add(const std::string& textStr, const std::function<void()>& func);
  void setFont(sf::Font* font);
  void setSizeWindow(const sf::Vector2u& size);
  void activate(std::size_t k);
  void manageCursor(sf::RenderWindow& window);
  void updateCursor();
  std::size_t getNumberWidgets() const;
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
  std::vector<std::pair<sf::Text, std::function<void()>>> widgets_;
  std::size_t nbWidgets_;
  sf::Font* font_;
  sf::Vector2u sizeWindow_ = {};
  sf::CircleShape cursor_;
  std::size_t currentChoice_;
  sf::Clock menuTimer_;
};

#endif
