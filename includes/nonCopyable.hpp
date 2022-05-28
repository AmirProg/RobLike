#ifndef NONCOPYABLE_HPP_INCLUDED
#define NONCOPYABLE_HPP_INCLUDED

/****

~ Classe NonCopyable ~

Représente toutes les entités qui n'auraient aucun sens à être copiés (par exemple un personnage)
Toute classe ayant une sémantique d'entité

****/

class NonCopyable{

protected:
  NonCopyable() = default;
  virtual ~NonCopyable(){}

private:
  NonCopyable(const NonCopyable&) = delete;
  NonCopyable& operator=(const NonCopyable&) = delete;
};

#endif
