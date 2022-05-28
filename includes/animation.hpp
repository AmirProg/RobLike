#ifndef ANIMATION_HPP_INCLUDED
#define ANIMATION_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "nonCopyable.hpp"

class Entity;

class Animation : private NonCopyable {

public:
   enum class Status { None, Disable, Active, OUT };
   Animation() = delete;
   Animation(sf::Sprite& spriteSheet, const sf::Vector2u& dimSheet);
   virtual ~Animation() = default;
   void setSpriteSheet(sf::Sprite& sprite);
   void setFrame(std::size_t frame); // Set the frame of the animation
   void restart(); // Reload the clock and the number of sprite animated
   void setBase(const sf::Vector2u& base); // The first sprite on the screen (row,line) (x,y), set (-1,-1) allow to have not any sprite in the screen
   void setDim(const sf::Vector2u& dimSheet);
   void playAnimationLine(std::size_t lineSheet); // Play the animation according to the clock and the line on sheet
   void playAnimation(); // Play the entire sprite sheet
   void pauseAnimation();

private:
   std::reference_wrapper<sf::Sprite> spriteSheet_; // Reference on the current spriteSheet_ animated
   sf::Vector2u dimSheet_;
   std::size_t frame_;
   sf::Vector2u currentSprite_; // The current sprite animated : (1,1) si the first one
   sf::Clock timer_; // Time measure
   sf::Time time_;
   Status status_;

   void cut(const sf::Vector2u& offset); // Découpe la sprite sheet en fonction de l'offset donné
};

#endif
