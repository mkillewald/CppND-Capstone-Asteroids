#include "InputController.h"
#include "PlayerController.h"

#include <SDL.h>

#include <iostream>

// based off Snake Game example code:
// https://github.com/udacity/CppND-Capstone-Snake-Game

void InputController::handleInput(bool &running,
                                  PlayerController *player) const {
  SDL_Event e;

  // single hit keys, and other SDL events
  while (SDL_PollEvent(&e)) {
    switch (e.type) {
    case SDL_QUIT:
      running = false;
      break;
    case SDL_KEYDOWN:
      switch (e.key.keysym.sym) {
      case SDLK_SEMICOLON:
        player->thrustOn();
        break;
      case SDLK_QUOTE:
        player->fire();
        break;
      case SDLK_SPACE:
        player->hyperspace();
        break;
      }
      break;
    case SDL_KEYUP:
      switch (e.key.keysym.sym) {
      case SDLK_a:
        player->rotateOff();
        break;
      case SDLK_s:
        player->rotateOff();
        break;
      case SDLK_SEMICOLON:
        player->thrustOff();
        break;
      }
      break;
    }
  }

  const Uint8 *keystates = SDL_GetKeyboardState(NULL);

  // contiuously held keys (this avoids keyboard repeat delay)
  if (keystates[SDL_SCANCODE_A]) {
    player->rotateLeft();
  }
  if (keystates[SDL_SCANCODE_S]) {
    player->rotateRight();
  }
}