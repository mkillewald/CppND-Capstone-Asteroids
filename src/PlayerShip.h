#ifndef PLAYERSHIP_H
#define PLAYERSHIP_H

#include "GameObject.h"

#include <cstddef>

class PlayerShip : public GameObject {
public:
  // constructor / destructor
  PlayerShip(std::size_t grid_width, std::size_t grid_height);
  ~PlayerShip();

  // getters / setters
  bool alive() const;

  // typical behaviour methods
  void init(std::size_t grid_width, std::size_t grid_height);
  // void update();
  // void draw();

  void rotateLeft();
  void rotateRight();
  void thrust();
  void fire();
  void hyperspace();

private:
  bool alive_ = false;
};

#endif