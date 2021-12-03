#include "Game.h"
#include "Controller.h"
#include "Renderer.h"

#include <SDL.h>

// based off Snake Game example code:
// https://github.com/udacity/CppND-Capstone-Snake-Game

Game::Game(const std::size_t grid_width, const std::size_t grid_height,
           float game_scale)
    : player_(grid_width, grid_height, game_scale),
      ufo_(grid_width, grid_height, game_scale), engine_(dev_()),
      random_w_(0, static_cast<int>(grid_width)),
      random_h_(0, static_cast<int>(grid_height)), random_type_(0, 3) {
  initAsteroids(grid_width, grid_height, game_scale);
}

unsigned long Game::score() const { return score_; }

void Game::run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;

  while (running_) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.handleInput(running_, player_);
    update();
    renderer.render(player_, asteroids_, ufo_);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.updateWindowTitle(score_, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is smaller
    // than the target ms_per_frame), delay the loop to achieve the correct
    // frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::initAsteroids(size_t grid_width, size_t grid_height,
                         float game_scale) {
  // set up first wave

  asteroids_.emplace_back(Asteroid(grid_width, grid_height, game_scale, 0));
  asteroids_.emplace_back(Asteroid(grid_width, grid_height, game_scale, 1));
  asteroids_.emplace_back(Asteroid(grid_width, grid_height, game_scale, 2));
  asteroids_.emplace_back(Asteroid(grid_width, grid_height, game_scale, 3));
  asteroids_.emplace_back(Asteroid(grid_width, grid_height, game_scale, 4));
  // for (int i = 0; i < 4; i++) {
  //   asteroids_.emplace_back(
  //       Asteroid(grid_width, grid_height, game_scale,
  //       random_type_(engine_)));
  // }
}

void Game::initUFO() {}

void Game::update() {
  if (!player_.alive()) {
    return;
  }

  player_.update();
  for (auto &asteroid : asteroids_) {
    asteroid.update();
  }

  // ufo_.update();
}
