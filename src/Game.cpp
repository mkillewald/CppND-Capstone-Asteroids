#include "Game.h"
#include "Asteroid.h"
#include "InputController.h"
#include "Renderer.h"
#include "UFO.h"

#include <SDL.h>

#include <memory>

// based off Snake Game example code:
// https://github.com/udacity/CppND-Capstone-Snake-Game

// std::uniform_int_distribution<int> random_type(0, 3);
Game::Game(Renderer *const renderer, float game_scale) : renderer_(renderer) {
  size_t grid_width = renderer->getGridWidth();
  size_t grid_height = renderer->getGridHeight();
  player1_ =
      std::make_unique<PlayerController>(grid_width, grid_height, game_scale);
  player2_ =
      std::make_unique<PlayerController>(grid_width, grid_height, game_scale);
  currentPlayer_ = player1_.get();

  hud = std::make_unique<HUD>(renderer->getSDLRenderer(), player1_.get(),
                              player2_.get());

  std::mt19937 engine_(dev_());
  std::uniform_int_distribution<int> random_w_(0, static_cast<int>(grid_width));
  std::uniform_int_distribution<int> random_h_(0,
                                               static_cast<int>(grid_height));
  std::uniform_int_distribution<int> random_type_(0, 3);
}

int Game::random_w() { return random_w_(engine_); }
int Game::random_h() { return random_w_(engine_); }
int Game::random_type() { return random_type_(engine_); }

void Game::run(InputController *const input,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;

  while (running_) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    input->handleInput(running_, currentPlayer_);
    update();
    renderer_->render(hud.get(), currentPlayer_);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer_->updateWindowTitle(currentPlayer_->score(), frame_count);
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

void Game::update() {
  if (!currentPlayer_->alive()) {
    return;
  }
  if (currentPlayer_->switchPlayer()) {
    currentPlayer_->setSwitchPlayer(false);
    currentPlayer_->rotateOff();
    currentPlayer_->thrustOff();
    if (currentPlayer_ == player1_.get()) {
      currentPlayer_ = player2_.get();
    } else {
      currentPlayer_ = player1_.get();
    }
  }
  currentPlayer_->update();
}
