#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "Asteroid.h"
#include "PlayerShip.h"
#include "UFO.h"

#include <SDL.h>

#include <memory>

class PlayerController {
public:
  // constructor / destructor
  PlayerController(size_t grid_width, size_t grid_height, float game_scale);
  ~PlayerController();

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
  std::unique_ptr<PlayerShip> ship_;
  std::unique_ptr<std::vector<Asteroid>> asteroids_;
  std::unique_ptr<UFO> ufo_;
  unsigned long score_{0};
  bool alive_ = true;
  bool switchPlayer_ = false;
};

#endif