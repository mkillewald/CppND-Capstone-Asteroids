#ifndef ASTEROID_H
#define ASTEROID_H

#include "GameObject.h"

class Asteroid : public GameObject {
public:
  enum AsteroidSize { kLarge, kMedium, kSmall };

  // constructor / destructor
  Asteroid();
  ~Asteroid();

  // getters / setters

  // typical behaviour methods
  // void update();
  // void draw();

private:
  AsteroidSize size_ = kLarge;
};

#endif