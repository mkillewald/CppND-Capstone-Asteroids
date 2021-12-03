#ifndef GAME_H
#define GAME_H

#include "Asteroid.h"
#include "PlayerShip.h"
#include "UFO.h"

#include <SDL.h>

#include <random>
#include <vector>

// forward declaration to avoid include cycle
class Controller;
class Renderer;

// class based off Snake Game example code:
// https://github.com/udacity/CppND-Capstone-Snake-Game

class Game {
public:
  // Contructor
  Game(std::size_t grid_width, std::size_t grid_height, float game_scale);

  unsigned long score() const;

  void run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);

private:
  PlayerShip player_;
  std::vector<Asteroid> asteroids_;
  UFO ufo_;
  unsigned long score_{0};
  bool running_ = true;

  std::random_device dev_;
  std::mt19937 engine_;
  std::uniform_int_distribution<int> random_w_;
  std::uniform_int_distribution<int> random_h_;
  std::uniform_int_distribution<int> random_type_;

  void initAsteroids(size_t grid_width, size_t grid_height, float game_scale);
  void initUFO();
  void update();
};

#endif