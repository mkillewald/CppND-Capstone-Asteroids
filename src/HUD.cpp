#include "HUD.h"
#include "Game.h"
#include "HighScore.h"
#include "Renderer.h"

#include "../lib/SDL_FontCache.h"

#include <SDL.h>

#include <iostream>
#include <string>

// TODO: add concept of game scale, eliminate magic numbers

HUD::HUD(Game *const game, Renderer *const renderer)
    : game_(game), player1_(game->player1()), player2_(game->player2()),
      renderer_(renderer) {

  centerX_ = renderer_->gridWidth() / 2;
  centerY_ = renderer_->gridHeight() / 2;

  hudColor = FC_MakeColor(0xFF, 0xFF, 0xFF, 0xAA);

  // atari_vector.ttf font used from
  // http://vectorlib2.free.fr/Fonts/http://vectorlib2.free.fr/Fonts/

  // Load fonts
  small_ = FC_CreateFont();
  FC_LoadFont(small_, renderer_->sdlRenderer(), "../fonts/atari_vector.ttf", 15,
              hudColor, TTF_STYLE_NORMAL);
  if (nullptr == small_) {
    std::cerr << "True type font was not found." << std::endl;
    std::cerr << "SDL_Error: " << SDL_GetError() << std::endl;
  }
  medium_ = FC_CreateFont();
  FC_LoadFont(medium_, renderer_->sdlRenderer(), "../fonts/atari_vector.ttf",
              30, hudColor, TTF_STYLE_NORMAL);
  if (nullptr == medium_) {
    std::cerr << "True type font was not found." << std::endl;
    std::cerr << "SDL_Error: " << SDL_GetError() << std::endl;
  }
  large_ = FC_CreateFont();
  FC_LoadFont(large_, renderer_->sdlRenderer(), "../fonts/atari_vector.ttf", 60,
              hudColor, TTF_STYLE_NORMAL);
  if (nullptr == large_) {
    std::cerr << "True type font was not found." << std::endl;
    std::cerr << "SDL_Error: " << SDL_GetError() << std::endl;
  }

  updateTableWidth();
}

HUD::~HUD() {
  FC_FreeFont(small_);
  FC_FreeFont(medium_);
  FC_FreeFont(large_);
}

void HUD::update() {
  switch (game_->state()) {
  case Game::kAttract_:
    break;
  case Game::kReadyToPlay_:
    if (SDL_GetTicks() - blinkTicks_ >= kSlowBlinkTickLimit_) {
      blink_ = !blink_;
      blinkTicks_ = SDL_GetTicks();
    }
    break;
  case Game::kReadyPlayer1_:
  case Game::kReadyPlayer2_:
    if (SDL_GetTicks() - blinkTicks_ >= kFastBlinkTickLimit_) {
      blink_ = !blink_;
      blinkTicks_ = SDL_GetTicks();
    }
    break;
  case Game::kPlay_:
    break;
  case Game::kHighScoreEntry_:
    if (SDL_GetTicks() - blinkTicks_ >= kSlowBlinkTickLimit_) {
      blink_ = !blink_;
      blinkTicks_ = SDL_GetTicks();
    }
    // TODO: time out and save entry if no input made within time frame
    break;
  }
}

void HUD::draw() const {
  switch (game_->state()) {
  case Game::kAttract_: {
    // TODO: alternate between attract and high score table
    drawP1Score();
    drawHiScore();
    drawP2Score();
    drawHiScoreTable();
    draw1Coin1Start();
    break;
  }
  case Game::kReadyToPlay_: {
    // TODO: alternate between attract and high score table
    drawP1Score();
    drawHiScore();
    drawP2Score();
    drawPushStart();
    drawHiScoreTable();
    draw1Coin1Start();
    break;
  }
  case Game::kReadyPlayer1_:
    if (game_->numPlayers() == 2) {
      if (blink_) {
        drawP1Score();
      }
      drawP2Score();
      drawP2Lives();
    } else {
      drawP1Score();
    }
    drawP1Lives();
    drawHiScore();
    drawMessageCenterX(150, kPlayer1.c_str());
    break;
  case Game::kReadyPlayer2_:
    drawP1Score();
    drawP1Lives();
    drawHiScore();
    if (blink_) {
      drawP2Score();
    }
    drawP2Lives();
    drawMessageCenterX(150, kPlayer2.c_str());
    break;
  case Game::kPlay_:
    // run game
    drawP1Score();
    drawP1Lives();
    drawHiScore();
    if (game_->numPlayers() == 2) {
      drawP2Score();
      drawP2Lives();
    }
    break;
  case Game::kGameOver_:
    drawP1Score();
    drawP1Lives();
    drawHiScore();
    if (game_->numPlayers() == 2) {
      drawP2Score();
      drawP2Lives();
      if (game_->currentPlayer() == game_->player1()) {
        drawMessageCenterX(150, kPlayer1.c_str());
      } else {
        drawMessageCenterX(150, kPlayer2.c_str());
      }
    }
    drawMessageCenterX(250, kGameOver.c_str());
    break;
  case Game::kHighScoreEntry_:
    if (game_->numPlayers() == 2) {
      if (game_->currentPlayer() == game_->player1() && blink_) {
        drawMessageCenterX(150, kPlayer1.c_str());
      } else if (game_->currentPlayer() == game_->player2() && blink_) {
        drawMessageCenterX(150, kPlayer2.c_str());
      }
    }

    drawP1Score();
    drawHiScore();
    drawP2Score();
    drawScoreEntry();
    break;
  }
}

void HUD::drawP1Score() const {
  std::string score;
  if (player1_->score() == 0) {
    score = "00";
  } else {
    score = std::to_string(player1_->score());
  }
  FC_Draw(medium_, renderer_->sdlRenderer(), 10, 3, score.c_str());
}

void HUD::drawP2Score() const {
  std::string score;
  if (player2_->score() == 0) {
    score = "00";
  } else {
    score = std::to_string(player2_->score());
  }
  FC_DrawAlign(medium_, renderer_->sdlRenderer(), renderer_->gridWidth() - 10,
               3, FC_ALIGN_RIGHT, score.c_str());
}

void HUD::drawP1Lives() const {
  player1_->drawLives(renderer_, 100, 50, hudColor);
}

void HUD::drawP2Lives() const {
  player2_->drawLives(renderer_, 850, 50, hudColor);
}

void HUD::drawHiScore() const {
  std::string hiScore;
  if (game_->highScore()->topScore() == 0) {
    hiScore == "00";
  } else {
    hiScore = std::to_string(game_->highScore()->topScore());
  }
  FC_DrawAlign(small_, renderer_->sdlRenderer(), centerX_, 15, FC_ALIGN_CENTER,
               hiScore.c_str());
}

void HUD::drawPushStart() const {
  if (blink_) {
    FC_DrawAlign(medium_, renderer_->sdlRenderer(), centerX_, 75,
                 FC_ALIGN_CENTER, kPushStart.c_str());
  }
}

void HUD::drawMessageCenterX(float y, const char *message) const {
  FC_DrawAlign(medium_, renderer_->sdlRenderer(), centerX_, y, FC_ALIGN_CENTER,
               message);
}

// need to call this anytime the high score table updates
void HUD::updateTableWidth() {
  spaceWidth_ = FC_GetWidth(medium_, " ");
  slotWidth_ = FC_GetWidth(medium_, game_->highScore()->tableSlots().c_str());
  scoreWidth_ = FC_GetWidth(medium_, game_->highScore()->tableScores().c_str());
  tagWidth_ = FC_GetWidth(medium_, game_->highScore()->tableTags().c_str());
  maxWidth_ = slotWidth_ + scoreWidth_ + tagWidth_ + spaceWidth_ * 2;
  tableX_ = centerX_ - maxWidth_ / 2 + slotWidth_;
  tableY_ = 205;
}

void HUD::drawHiScoreTable() const {
  if (game_->highScore()->topScore() == 0) {
    return;
  }

  FC_DrawAlign(medium_, renderer_->sdlRenderer(), centerX_, 150,
               FC_ALIGN_CENTER, kHighScores.c_str());
  FC_DrawAlign(medium_, renderer_->sdlRenderer(), tableX_, tableY_,
               FC_ALIGN_RIGHT, game_->highScore()->tableSlots().c_str());
  FC_DrawAlign(medium_, renderer_->sdlRenderer(),
               tableX_ + spaceWidth_ + scoreWidth_, tableY_, FC_ALIGN_RIGHT,
               game_->highScore()->tableScores().c_str());
  FC_DrawAlign(medium_, renderer_->sdlRenderer(),
               tableX_ + scoreWidth_ + 2 * spaceWidth_, tableY_, FC_ALIGN_LEFT,
               game_->highScore()->tableTags().c_str());
}

void HUD::draw1Coin1Start() const {
  FC_DrawAlign(medium_, renderer_->sdlRenderer(), centerX_, 640,
               FC_ALIGN_CENTER, k1Coin1Start.c_str());
}

void HUD::drawScoreEntry() const {
  FC_Draw(medium_, renderer_->sdlRenderer(), 100, 200, kHiScoreEntry.c_str());

  FC_DrawAlign(large_, renderer_->sdlRenderer(), centerX_, 600, FC_ALIGN_CENTER,
               game_->highScore()->tag().c_str());
}