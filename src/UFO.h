#ifndef UFO_H
#define UFO_H

#include "GameObject.h"

class UFO : public GameObject {
public:
  enum UFOSize { large, small };
  // constructor / destructor
  // UFO();
  // ~UFO();

  // getters / setters

  // typical behaviour methods
  // void update();
  // void draw();

private:
  UFOSize size = large;
};

#endif