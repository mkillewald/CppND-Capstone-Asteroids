#ifndef PLAYERSHIP_H
#define PLAYERSHIP_H

#include "GameObject.h"

#include <cstddef>

// forward declaration to avoid include cycle
class Renderer;

class PlayerShip : public GameObject {
public:
  // constructor / destructor
  PlayerShip(const std::size_t grid_width, const std::size_t grid_height);
  ~PlayerShip();

  // getters / setters
  bool alive() const;

  // typical behaviour methods
  void init();
  void update();
  void drawGhost(Renderer *const renderer) const;
  void draw(Renderer *const renderer) const;
  void updatePosition();
  void rotateLeft();
  void rotateRight();
  void rotateOff();
  void thrustOn();
  void thrustOff();
  void fire();
  void hyperspace();

private:
  bool alive_ = true;
  bool thrust_ = false;
};

#endif