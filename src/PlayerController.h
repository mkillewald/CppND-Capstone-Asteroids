#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "Asteroid.h"
#include "PlayerShip.h"
#include "PlayerShot.h"
#include "UFO.h"

#include <SDL.h>

#include <cstddef>
#include <cstdint>
#include <memory>

// forward declaration to avoid include cycle
class Renderer;
class GameObject;

class PlayerController {
public:
  // constructor / destructor
  PlayerController(std::size_t grid_width, std::size_t grid_height,
                   float game_scale);

  // getters / setters
  bool alive() const;
  void setAlive(bool alive);
  bool switchPlayer() const;
  void setSwitchPlayer(bool b);
  std::uint32_t lives() const;
  std::uint32_t score() const;

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
  std::uint32_t score_{0};
  bool alive_{false};
  bool switchPlayer_{false};
  std::uint32_t lives_{0};
  std::uint32_t reloadTicks_{0};
  std::uint32_t reloadTickLimit_{100};

  void setLives(std::uint32_t lives);
  void setScore(std::uint32_t score);
  void addScore(std::uint32_t score);
};

#endif