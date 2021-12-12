#include "HUD.h"
#include "Game.h"
#include "Renderer.h"

#include "../lib/SDL_FontCache.h"

#include <SDL.h>

#include <iostream>

HUD::HUD(Game const *game, Renderer const *renderer)
    : game_(game), player1_(game->player1()), player2_(game->player2()),
      renderer_(renderer) {

  SDL_Color textColor = FC_MakeColor(255, 255, 255, 255);

  // Load fonts
  small_ = FC_CreateFont();
  FC_LoadFont(small_, renderer_->sdlRenderer(), "../fonts/atari_vector.ttf", 12,
              textColor, TTF_STYLE_NORMAL);
  if (nullptr == small_) {
    std::cerr << "True type font was not found." << std::endl;
    std::cerr << "SDL_Error: " << SDL_GetError() << std::endl;
  }
  medium_ = FC_CreateFont();
  FC_LoadFont(medium_, renderer_->sdlRenderer(), "../fonts/atari_vector.ttf",
              24, textColor, TTF_STYLE_NORMAL);
  if (nullptr == medium_) {
    std::cerr << "True type font was not found." << std::endl;
    std::cerr << "SDL_Error: " << SDL_GetError() << std::endl;
  }
  large_ = FC_CreateFont();
  FC_LoadFont(large_, renderer_->sdlRenderer(), "../fonts/atari_vector.ttf", 48,
              textColor, TTF_STYLE_NORMAL);
  if (nullptr == large_) {
    std::cerr << "True type font was not found." << std::endl;
    std::cerr << "SDL_Error: " << SDL_GetError() << std::endl;
  }
}

HUD::~HUD() { FC_FreeFont(medium_); }

void HUD::update() {
  switch (game_->state()) {
  case Game::eGameState::kAttract_:
    break;
  case Game::eGameState::kReadyToPlay_:
    break;
  case Game::eGameState::kPlay_:
    break;
  case Game::eGameState::kHighScoreEntry_:
    break;
  }
}

void HUD::draw() const {
  switch (game_->state()) {
  case Game::eGameState::kAttract_:
    // alternate between attract and high score table
    FC_Draw(medium_, renderer_->sdlRenderer(), 10, 10, "12345");
    break;
  case Game::eGameState::kReadyToPlay_:
    // flash press start
    break;
  case Game::eGameState::kPlay_:
    // run game
    break;
  case Game::eGameState::kHighScoreEntry_:
    // get players initials
    break;
  }
}