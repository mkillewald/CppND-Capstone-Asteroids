#ifndef ASTEROID_H
#define ASTEROID_H

#include "GameObject.h"

class Asteroid : public GameObject {
public:
  enum eAsteroidType { kType1_, kType2_, kType3_, kType4_, kTypeUFO_ };
  enum eAsteroidSize { kLarge_, kMedium_, kSmall_ };

  // constructor / destructor
  Asteroid(std::size_t grid_width, std::size_t grid_height, float game_scale,
           int type);
  ~Asteroid();

  // getters / setters

  // typical behaviour methods

private:
  const int type_;
  eAsteroidSize size_ = kLarge_;

  void init();
  void initType1();
  void initType2();
  void initType3();
  void initType4();
  void initUFO();
};

#endif