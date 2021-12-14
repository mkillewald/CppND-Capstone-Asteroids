#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "Asteroid.h"
#include "PlayerShip.h"
#include "PlayerShot.h"
#include "UFO.h"

#include <SDL.h>

#include <memory>

// forward declaration to avoid include cycle
class Renderer;
class GameObject;

class PlayerController {
public:
  // constructor / destructor
  PlayerController(size_t grid_width, size_t grid_height, float game_scale);

  // getters / setters
  bool alive() const;
  void setAlive(bool alive);
  bool switchPlayer() const;
  void setSwitchPlayer(bool b);
  Uint32 lives() const;
  Uint32 score() const;

  // behavior methods
  void update();
  void draw(Renderer *const renderer) const;
  void init();
  void rotateLeft();
  void rotateRight();
  void rotateOff();
  void thrustOn();
  void thrustOff();
  void fire();
  void hyperspace();

private:
  PlayerShip ship_;
  std::vector<PlayerShot> playerShots_;
  std::vector<Asteroid> asteroids_;
  UFO ufo_;
  unsigned long score_{0};
  bool alive_{false};
  bool switchPlayer_{false};
  Uint32 lives_{0};
  Uint32 reloadTicks_;
  Uint32 reloadTickLimit_{100};

  void setLives(Uint32 lives);
  void setScore(Uint32 score);
  void addScore(Uint32 score);
};

#endif