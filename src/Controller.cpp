#include "Controller.h"
#include "PlayerShip.h"

#include <SDL.h>

#include <iostream>

// based off Snake Game example code:
// https://github.com/udacity/CppND-Capstone-Snake-Game

void Controller::handleInput(bool &running, PlayerShip &player) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
      case SDLK_a:
        player.rotateLeft();
        break;
      case SDLK_s:
        player.rotateRight();
        break;
      case SDLK_k:
        player.thrust();
        break;
      case SDLK_l:
        player.fire();
        break;
      case SDLK_SPACE:
        player.hyperspace();
        break;
      }
    }
  }
}