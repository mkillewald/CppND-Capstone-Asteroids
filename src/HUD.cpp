#include "HUD.h"
#include "Game.h"
#include "Renderer.h"

#include <SDL_ttf.h>

#include <iostream>

HUD::HUD(Game const *game, Renderer const *renderer)
    : game_(game), player1_(game->player1()), player2_(game->player2()),
      renderer_(renderer) {
  // Initialize SDL_ttf library
  TTF_Init();

  // Load fonts
  SDL_Color textColor = {255, 255, 255};
  small_ = TTF_OpenFont("../fonts/atari_vector.ttf", 12);
  if (nullptr == small_) {
    std::cerr << "True type font was not found." << std::endl;
    std::cerr << "SDL_Error: " << SDL_GetError() << std::endl;
  }
  medium_ = TTF_OpenFont("../fonts/atari_vector.ttf", 24);
  if (nullptr == medium_) {
    std::cerr << "True type font was not found." << std::endl;
    std::cerr << "SDL_Error: " << SDL_GetError() << std::endl;
  }
  large_ = TTF_OpenFont("../fonts/atari_vector.ttf", 48);
  if (nullptr == large_) {
    std::cerr << "True type font was not found." << std::endl;
    std::cerr << "SDL_Error: " << SDL_GetError() << std::endl;
  }

  // Create surface with font
  p1ScoreSfc_ = TTF_RenderText_Solid(medium_, "10374", textColor);
  p2ScoreSfc_ = TTF_RenderText_Solid(medium_, "14322", textColor);
  hiScoreSfc_ = TTF_RenderText_Solid(small_, "23645", textColor);

  // Create font textures from surfaces
  p1ScoreTxt_ =
      SDL_CreateTextureFromSurface(renderer_->sdlRenderer(), p1ScoreSfc_);
  p2ScoreTxt_ =
      SDL_CreateTextureFromSurface(renderer_->sdlRenderer(), p2ScoreSfc_);
  hiScoreTxt_ =
      SDL_CreateTextureFromSurface(renderer_->sdlRenderer(), hiScoreSfc_);

  // Set position and size of font textures
  int texH = 0;
  int texW = 0;
  SDL_QueryTexture(p1ScoreTxt_, NULL, NULL, &texW, &texH);
  p1ScoreRct_ = {10, 10, texW, texH};

  SDL_QueryTexture(p2ScoreTxt_, NULL, NULL, &texW, &texH);
  p2ScoreRct_ = {(int)(renderer_->gridWidth() - texW - 10), 10, texW, texH};

  SDL_QueryTexture(hiScoreTxt_, NULL, NULL, &texW, &texH);
  hiScoreRct_ = {(int)(renderer_->gridWidth() - texW) / 2, 10, texW, texH};
}

HUD::~HUD() {
  TTF_CloseFont(small_);
  TTF_CloseFont(medium_);
  TTF_CloseFont(large_);
  SDL_DestroyTexture(p1ScoreTxt_);
  SDL_DestroyTexture(p2ScoreTxt_);
  SDL_DestroyTexture(hiScoreTxt_);
  SDL_FreeSurface(p1ScoreSfc_);
  SDL_FreeSurface(p2ScoreSfc_);
  SDL_FreeSurface(hiScoreSfc_);
  TTF_Quit();
}

void HUD::draw() const {
  switch (game_->state()) {
  case Game::eGameState::kAttract_:
    SDL_RenderCopy(renderer_->sdlRenderer(), p1ScoreTxt_, NULL, &p1ScoreRct_);
    SDL_RenderCopy(renderer_->sdlRenderer(), p2ScoreTxt_, NULL, &p2ScoreRct_);
    SDL_RenderCopy(renderer_->sdlRenderer(), hiScoreTxt_, NULL, &hiScoreRct_);
    break;
  case Game::eGameState::kReadyToPlay_:
    break;
  case Game::eGameState::kPlay_:
    break;
  case Game::eGameState::kHighScoreEntry_:
    break;
  }
}