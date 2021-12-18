#include "InputController.h"
#include "Game.h"
#include "HUD.h"
#include "PlayerController.h"

#include <SDL.h>

#include <iostream>

void InputController::attract(Game *game) const {
  SDL_Event e;

  // single hit keys, and other SDL events
  while (SDL_PollEvent(&e)) {
    switch (e.type) {
    case SDL_QUIT:
      game->setRunning(false);
      break;
    case SDL_KEYDOWN:
      switch (e.key.keysym.sym) {
      case SDLK_i:
        game->insertCoin();
        break;
      }
      break;
    }
  }
}

void InputController::ready(Game *game) const {
  SDL_Event e;

  // single hit keys, and other SDL events
  while (SDL_PollEvent(&e)) {
    switch (e.type) {
    case SDL_QUIT:
      game->setRunning(false);
      break;
    case SDL_KEYDOWN:
      switch (e.key.keysym.sym) {
      case SDLK_1:
        game->onePlayerStart();
        break;
      case SDLK_2:
        game->twoPlayerStart();
        break;
      case SDLK_i:
        game->insertCoin();
        break;
      }
      break;
    }
  }
}

void InputController::play(Game *game, PlayerController *player) const {
  SDL_Event e;

  // single hit keys, and other SDL events
  while (SDL_PollEvent(&e)) {
    switch (e.type) {
    case SDL_QUIT:
      game->setRunning(false);
      break;
    case SDL_KEYDOWN:
      switch (e.key.keysym.sym) {
      case SDLK_SEMICOLON:
        player->thrustOn();
        break;
      case SDLK_SPACE:
        player->hyperspace();
        break;
      case SDLK_i:
        game->insertCoin();
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
  if (keystates[SDL_SCANCODE_APOSTROPHE]) {
    player->fire();
  }
}

// TODO: finish this with correct keys/functions
void InputController::highScore(Game *game, HUD *hud,
                                PlayerController *player) const {
  SDL_Event e;

  // single hit keys, and other SDL events
  while (SDL_PollEvent(&e)) {
    switch (e.type) {
    case SDL_QUIT:
      game->setRunning(false);
      break;
    case SDL_KEYDOWN:
      switch (e.key.keysym.sym) {
      case SDLK_a:
        hud->charUp();
        break;
      case SDLK_s:
        hud->charDown();
        break;
      case SDLK_SPACE:
        hud->charSelect();
        break;
      case SDLK_i:
        // insert coin
        game->insertCoin();
        break;
      }
      break;
    case SDL_KEYUP:
      switch (e.key.keysym.sym) {
      case SDLK_a:
        // hud->rotateOff();
        break;
      case SDLK_s:
        // hud->rotateOff();
        break;
      }
      break;
    }
  }
}