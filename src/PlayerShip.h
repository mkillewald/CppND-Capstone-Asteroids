#ifndef PLAYERSHIP_H
#define PLAYERSHIP_H

#include "GameObject.h"

#include <cstddef>

// forward declaration to avoid include cycle
class Renderer;

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
  void draw(Renderer *const renderer) const;

  void rotateLeft();
  void rotateRight();
  void thrustOn();
  void thrustOff();
  void fire();
  void hyperspace();

private:
  bool alive_ = true;
  bool thrust_ = false;
};

#endif