#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "Asteroid.h"
#include "PlayerShip.h"
#include "PlayerShot.h"
#include "UFO.h"

#include <SDL.h>

#include <memory>

class PlayerController {
public:
  // constructor / destructor
  PlayerController(size_t grid_width, size_t grid_height, float game_scale);

  // getters / setters
  unsigned long score() const;
  bool alive() const;
  bool switchPlayer() const;
  void setSwitchPlayer(bool b);

  // behavior methods
  void update();
  void draw(Renderer *const renderer) const;
  void rotateLeft();
  void rotateRight();
  void rotateOff();
  void thrustOn();
  void thrustOff();
  void fire();
  void hyperspace();

private:
  PlayerShip ship_;
  std::vector<PlayerShot> shots_;
  std::vector<Asteroid> asteroids_;
  UFO ufo_;
  unsigned long score_{0};
  bool alive_ = true;
  bool switchPlayer_ = false;
  int reloadTicks_;
  int reloadTickLimit_{100};
};

#endif