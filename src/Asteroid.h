#ifndef ASTEROID_H
#define ASTEROID_H

#include "GameObject.h"

#include <cstddef>
#include <cstdint>
#include <random>

class Asteroid : public GameObject {
public:
  enum eAsteroidType { kType1_, kType2_, kType3_, kType4_, kTypeUFO_ };
  enum eAsteroidSize { kLarge_, kMedium_, kSmall_ };

  // constructor / destructor
  Asteroid(std::size_t grid_width, std::size_t grid_height, float game_scale);

  // getters / setters
  std::uint32_t getScore() const;

  // behaviour methods
  void hit();

private:
  const float kRadius_{80.0f};
  const float kLargeScale_{2.0f};
  const float kMediumScale_{1.3f};
  const float kSmallScale_{0.7f};
  const int type_;

  eAsteroidSize size_ = kLarge_;

  void initPoints();
  void initType1();
  void initType2();
  void initType3();
  void initType4();
};

#endif