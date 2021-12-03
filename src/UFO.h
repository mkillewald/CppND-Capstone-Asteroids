#ifndef UFO_H
#define UFO_H

#include "GameObject.h"

class UFO : public GameObject {
public:
  enum UFOSize { large, small };
  // constructor / destructor
  UFO(const std::size_t grid_width, const std::size_t grid_height,
      float game_scale);
  ~UFO();

  // getters / setters

  // typical behaviour methods
  // void update();
  // void draw();

private:
  UFOSize size = large;
};

#endif