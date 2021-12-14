#include "HUD.h"
#include "Game.h"
#include "Renderer.h"

#include "../lib/SDL_FontCache.h"

#include <SDL.h>

#include <iostream>

HUD::HUD(Game const *game, Renderer const *renderer)
    : game_(game), player1_(game->player1()), player2_(game->player2()),
      renderer_(renderer) {

  centerX_ = renderer_->gridWidth() / 2;
  centerY_ = renderer_->gridHeight() / 2;

  SDL_Color textColor = FC_MakeColor(255, 255, 255, 150);

  // Load fonts
  small_ = FC_CreateFont();
  FC_LoadFont(small_, renderer_->sdlRenderer(), "../fonts/atari_vector.ttf", 14,
              textColor, TTF_STYLE_NORMAL);
  if (nullptr == small_) {
    std::cerr << "True type font was not found." << std::endl;
    std::cerr << "SDL_Error: " << SDL_GetError() << std::endl;
  }
  medium_ = FC_CreateFont();
  FC_LoadFont(medium_, renderer_->sdlRenderer(), "../fonts/atari_vector.ttf",
              28, textColor, TTF_STYLE_NORMAL);
  if (nullptr == medium_) {
    std::cerr << "True type font was not found." << std::endl;
    std::cerr << "SDL_Error: " << SDL_GetError() << std::endl;
  }
  large_ = FC_CreateFont();
  FC_LoadFont(large_, renderer_->sdlRenderer(), "../fonts/atari_vector.ttf", 56,
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
    if (SDL_GetTicks() - blinkTicks_ >= blinkTickLimit_) {
      blink_ = !blink_;
      blinkTicks_ = SDL_GetTicks();
    }
    break;
  case Game::eGameState::kPlay_:
    break;
  case Game::eGameState::kHighScoreEntry_:
    break;
  }
}

void HUD::draw() const {
  switch (game_->state()) {
  case Game::eGameState::kAttract_: {
    // alternate between attract and high score table
    drawP1Score();
    drawHiScore();
    drawP2Score();
    drawHiScoreTable();
    draw1Coin1Start();
    break;
  }
  case Game::eGameState::kReadyToPlay_: {
    // alternate between attract and high score table, flash push start
    drawP1Score();
    drawHiScore();
    drawP2Score();
    drawPushStart();
    drawHiScoreTable();
    draw1Coin1Start();
    break;
  }
  case Game::eGameState::kPlay_:
    // run game
    drawP1Score();
    // drawP1Lives();
    drawHiScore();
    if (game_->numPlayers() == 2) {
      drawP2Score();
      // drawP2Lives();
    }
    break;
  case Game::eGameState::kHighScoreEntry_:
    // get players initials
    drawP1Score();
    drawHiScore();
    drawP2Score();

    // TODO: finish this
    break;
  }
}

void HUD::drawP1Score() const {
  FC_Draw(medium_, renderer_->sdlRenderer(), 10, 3, "12345");
}

void HUD::drawP2Score() const {
  FC_DrawAlign(medium_, renderer_->sdlRenderer(), renderer_->gridWidth() - 10,
               3, FC_ALIGN_RIGHT, "12345");
}

void HUD::drawHiScore() const {
  FC_DrawAlign(small_, renderer_->sdlRenderer(), centerX_, 15, FC_ALIGN_CENTER,
               "678910");
}

void HUD::drawPushStart() const {
  if (blink_) {
    FC_DrawAlign(medium_, renderer_->sdlRenderer(), centerX_, 75,
                 FC_ALIGN_CENTER, kPushStart.c_str());
  }
}

void HUD::drawHiScoreTable() const {
  int tableX = centerX_ - 70;
  int tableY = 205;
  int maxWidth = 110;
  int spaceWidth = 15;
  FC_DrawAlign(medium_, renderer_->sdlRenderer(), centerX_, 150,
               FC_ALIGN_CENTER, kHighScores.c_str());
  FC_DrawAlign(medium_, renderer_->sdlRenderer(), tableX, tableY,
               FC_ALIGN_RIGHT, "1.\n2.\n3.\n4.\n5.\n6.\n7.\n8.\n9.\n10.");
  FC_DrawAlign(medium_, renderer_->sdlRenderer(), tableX + maxWidth, tableY,
               FC_ALIGN_RIGHT,
               "39020\n15110\n3480\n2810\n1460\n1060\n680\n360\n240\n90");
  FC_DrawAlign(medium_, renderer_->sdlRenderer(),
               tableX + maxWidth + spaceWidth, tableY, FC_ALIGN_LEFT,
               "KEX\nA\nAAA\nAAA\nAAA\nA\nA\nA\nDAA\nA");
}

void HUD::draw1Coin1Start() const {
  FC_DrawAlign(medium_, renderer_->sdlRenderer(), centerX_, 640,
               FC_ALIGN_CENTER, k1Coin1Start.c_str());
}