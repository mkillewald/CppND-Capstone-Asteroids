#include "HUD.h"
#include "Game.h"
#include "Renderer.h"

#include "../lib/SDL_FontCache.h"

#include <SDL.h>

#include <iostream>
#include <string>

HUD::HUD(Game *const game, Renderer *const renderer)
    : game_(game), player1_(game->player1()), player2_(game->player2()),
      renderer_(renderer) {

  centerX_ = renderer_->gridWidth() / 2;
  centerY_ = renderer_->gridHeight() / 2;

  hudColor = FC_MakeColor(0xFF, 0xFF, 0xFF, 0xAA);

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
    // TOOD: time out and save entry if no input made within time frame
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

    // TODO: if not start of game, show asteroid field
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

    // TODO: if not start of game, show asteroid field
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
    drawMessageCenterX(250, kGameOver.c_str());
    break;
  case Game::kHighScoreEntry_:
    // get players initials
    drawP1Score();
    drawHiScore();
    drawP2Score();

    drawScoreEntryInstructions();
    // TODO: finish this
    break;
  }
}

// TODO: fix positioning of score and lives

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
  FC_DrawAlign(small_, renderer_->sdlRenderer(), centerX_, 15, FC_ALIGN_CENTER,
               "678910");
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

void HUD::drawHiScoreTable() const {
  // TODO: finish this, dont create int inside loop, get real data.
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

void HUD::drawScoreEntryInstructions() const {
  FC_Draw(medium_, renderer_->sdlRenderer(), 100, 200, kHiScoreEntry.c_str());

  FC_DrawAlign(large_, renderer_->sdlRenderer(), centerX_, 600, FC_ALIGN_CENTER,
               entry().c_str());
}

void HUD::initEntry() {
  initialIndex_ = 0;
  initial0_ = "A";
  initial1_ = "_";
  initial2_ = "_";
}

std::string HUD::entry() const { return initial0_ + initial1_ + initial2_; }

void HUD::setEntry() {
  switch (initialIndex_) {
  case 0:
    initial0_ = chars_.substr(charIndex_, 1);
    break;
  case 1:
    initial1_ = chars_.substr(charIndex_, 1);
    break;
  case 2:
    initial2_ = chars_.substr(charIndex_, 1);
    break;
  }
}

void HUD::charUp() {
  if (charIndex_ == chars_.size() - 1) {
    charIndex_ = 0;
  } else {
    charIndex_++;
  }
  setEntry();
}

void HUD::charDown() {
  if (charIndex_ == 0) {
    charIndex_ = chars_.size() - 1;
  } else {
    charIndex_--;
  }
  setEntry();
}

void HUD::charSelect() {
  if (initialIndex_ == 2) {
    // TODO: save entry
  } else {
    charIndex_ = 0;
    initialIndex_++;
  }
  setEntry();
}