#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "Asteroid.h"
#include "PlayerShip.h"
#include "PlayerShot.h"
#include "UFO.h"

#include <SDL.h>

#include <cstdint>
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
  uint32_t lives() const;
  uint32_t score() const;

  // behavior methods
  void update();
  void draw(Renderer *const renderer) const;
  void drawLives(Renderer *const renderer, int const &x, int const &y,
                 SDL_Color const &color) const;
  void initPlayer();
  void start();
  void die();
  void addLife();
  void minusLife();
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
  uint32_t score_{0};
  bool alive_{false};
  bool switchPlayer_{false};
  uint32_t lives_{0};
  uint32_t reloadTicks_{0};
  uint32_t reloadTickLimit_{100};

  void setLives(uint32_t lives);
  void setScore(uint32_t score);
  void addScore(uint32_t score);
};

#endif