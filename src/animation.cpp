#include "animation.hpp"
#include "player.hpp"

Animation::Animation(sf::Sprite& spriteSheet, const sf::Vector2u& dimSheet) :

  spriteSheet_(spriteSheet),
  dimSheet_(dimSheet),
  frame_(0),
  currentSprite_(sf::Vector2u(1,1)),
  status_(Status::Disable)
{}

void Animation::setSpriteSheet(sf::Sprite& spriteSheet){

    spriteSheet_ = spriteSheet;
}

void Animation::setFrame(std::size_t frame){
    frame_ = frame;
}

void Animation::restart(){

    timer_.restart();
    currentSprite_ = sf::Vector2u(1,1); // On remet la frame de base
}

void Animation::setBase(const sf::Vector2u& base){

    cut(sf::Vector2u(base.x,base.y));
    timer_.restart();
}

void Animation::cut(const sf::Vector2u& offset){

    spriteSheet_.get().setTextureRect((sf::IntRect((offset.x - 1) * (spriteSheet_.get().getTexture()->getSize().x/dimSheet_.x), (offset.y - 1) * (spriteSheet_.get().getTexture()->getSize().y/dimSheet_.y), spriteSheet_.get().getTexture()->getSize().x/dimSheet_.x,spriteSheet_.get().getTexture()->getSize().y/dimSheet_.y)));
}

void Animation::setDim(const sf::Vector2u& dimSheet){

  dimSheet_ = dimSheet;
}

void Animation::playAnimationLine(std::size_t lineSheet){

    status_ = Status::Active;

    if(timer_.getElapsedTime().asMilliseconds() >= sf::Int32(frame_) || currentSprite_.y != lineSheet){ // Every frame or when we change the current line on the sheet

        cut(sf::Vector2u(currentSprite_.x,lineSheet));

        currentSprite_.x++; // We pass to the next sprite on the line

        if(currentSprite_.x > dimSheet_.x){
            currentSprite_.x = 1; // The current number of the sprite (on the line) on the spritesheet is reset every lines
            currentSprite_.y++;
        }

      currentSprite_.y = lineSheet;


      timer_.restart();
    }
}

void Animation::playAnimation(){

    status_ = Status::Active;
    playAnimationLine(currentSprite_.y);

    if(currentSprite_.y >= dimSheet_.y)
        restart();
}

void Animation::pauseAnimation(){

    status_ = Status::Disable;
}
