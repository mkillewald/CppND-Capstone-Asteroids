#include "Game.h"
#include "HUD.h"
#include "HighScore.h"
#include "InputController.h"
#include "PlayerController.h"
#include "Renderer.h"

#include <SDL.h>

#include <cstddef>
#include <cstdint>
#include <memory>

// TODO: fix  player shot logic
// TODO: asteroid splitting, scoring and wave logic
// TODO: ufo logic (shooting, change direction) and scoring
// TODO: add object explosions
// TODO: add game sounds
// TODO: satisfy 5 needed items from rubric (multithreadding...)

Game::Game(Renderer *const renderer, float game_scale) : renderer_(renderer) {
  std::size_t grid_width = renderer->gridWidth();
  std::size_t grid_height = renderer->gridHeight();
  player1_ =
      std::make_unique<PlayerController>(grid_width, grid_height, game_scale);
  player2_ =
      std::make_unique<PlayerController>(grid_width, grid_height, game_scale);
  currentPlayer_ = player1_.get();
  highScore_ = std::make_unique<HighScore>(this);
  hud_ = std::make_unique<HUD>(this, renderer);
  numPlayers_ = 0;

  std::mt19937 engine_(dev_());
  std::uniform_int_distribution<int> random_w_(0, static_cast<int>(grid_width));
  std::uniform_int_distribution<int> random_h_(0,
                                               static_cast<int>(grid_height));
  std::uniform_int_distribution<int> random_type_(0, 3);
}

int Game::random_w() { return random_w_(engine_); }
int Game::random_h() { return random_w_(engine_); }
int Game::random_type() { return random_type_(engine_); }

Game::eGameState Game::state() const { return state_; }
void Game::setState(eGameState state) { state_ = state; }

PlayerController *const Game::player1() const { return player1_.get(); }
PlayerController *const Game::player2() const { return player2_.get(); }
PlayerController *const Game::currentPlayer() const { return currentPlayer_; }
void Game::setCurrentPlayer(PlayerController *const player) {
  currentPlayer_ = player;
}
HighScore *const Game::highScore() const { return highScore_.get(); }
HUD *const Game::hud() const { return hud_.get(); }

void Game::setRunning(bool running) { running_ = running; }

uint32_t Game::numPlayers() const { return numPlayers_; }
void Game::setPlayers(uint32_t players) { numPlayers_ = players; }

void Game::run(InputController *const inputController,
               std::size_t target_frame_duration) {
  uint32_t title_timestamp = SDL_GetTicks();
  uint32_t frame_start;
  uint32_t frame_end;
  uint32_t frame_duration;
  int frame_count = 0;

  while (running_) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    input(inputController);
    update();
    renderer_->render(hud_.get(), currentPlayer_);

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

void Game::insertCoin() {
  if (credits_ < 99) {
    credits_++;
  }

  if (state() == kAttract_) {
    setState(kReadyToPlay_);
  }
}

void Game::onePlayerStart() {
  if (credits_ > 0) {
    credits_--;
    setPlayers(1);
    player1_->initPlayer();
    currentPlayer_ = player1_.get();
    setState(kReadyPlayer1_);
    displayTicks_ = SDL_GetTicks();
  }
}

void Game::twoPlayerStart() {
  if (credits_ > 1) {
    credits_ -= 2;
    setPlayers(2);
    player1_->initPlayer();
    player2_->initPlayer();
    currentPlayer_ = player1_.get();
    setState(kReadyPlayer1_);
    displayTicks_ = SDL_GetTicks();
  }
}

bool Game::switchPlayer() {
  if (currentPlayer_ == player1_.get() && player2_->lives() > 0) {
    // switch to player 2
    currentPlayer_->setSwitchPlayer(false);
    currentPlayer_ = player2_.get();
    setState(kReadyPlayer2_);
    displayTicks_ = SDL_GetTicks();
    return true;
  } else if (currentPlayer_ == player2_.get() && player1_->lives() > 0) {
    // switch to player 1
    currentPlayer_->setSwitchPlayer(false);
    currentPlayer_ = player1_.get();
    setState(kReadyPlayer1_);
    displayTicks_ = SDL_GetTicks();
    return true;
  }
  return false;
}

void Game::input(InputController *const inputController) {
  switch (state()) {
  case kReadyToPlay_:
    inputController->ready(this);
    break;
  case kPlay_:
    inputController->play(this, currentPlayer_);
    break;
  case kHighScoreEntry_:
    inputController->highScore(this, highScore_.get());
    break;
  default:
    inputController->attract(this);
    break;
  }
}

void Game::update() {
  switch (state()) {
  case kAttract_:
    break;
  case kReadyToPlay_:
    break;
  case kReadyPlayer1_:
  case kReadyPlayer2_:
    if (SDL_GetTicks() - displayTicks_ >= kDisplayTickLimit_) {
      currentPlayer_->start();
      setState(kPlay_);
    }
    break;
  case kPlay_:
    if (numPlayers() > 1 && currentPlayer_->switchPlayer()) {
      // 2 player game, switch player
      if (currentPlayer_->lives() > 0) {
        if (!switchPlayer()) {
          // player could not be switched
          currentPlayer_->setSwitchPlayer(false);
          currentPlayer_->start();
        }
      } else {
        setState(kGameOver_);
        displayTicks_ = SDL_GetTicks();
      }
    } else if (numPlayers() == 1 && currentPlayer_->switchPlayer()) {
      // 1 player game
      currentPlayer_->setSwitchPlayer(false);
      if (currentPlayer_->lives() > 0) {
        currentPlayer_->start();
      } else {
        setState(kGameOver_);
        displayTicks_ = SDL_GetTicks();
      }
    }
    break;
  case kGameOver_:
    if (SDL_GetTicks() - displayTicks_ >= kDisplayTickLimit_) {
      if (numPlayers() > 1 && currentPlayer_->switchPlayer()) {
        // 2 player game, switch player
        if (!switchPlayer()) {
          // player could not be switched
          currentPlayer_->setSwitchPlayer(false);
          bool p1High = highScore_->scoreIsHigh(player1_->score());
          bool p2High = highScore_->scoreIsHigh(player2_->score());
          if (p1High || p2High) {
            if (p1High) {
              currentPlayer_ = player1_.get();
            } else {
              currentPlayer_ = player2_.get();
            }
            highScore_->setP1High(p1High);
            highScore_->setP2High(p2High);
            setState(kHighScoreEntry_);
          } else {
            setState(kAttract_);
          }
        }
      } else {
        // 1 player game
        if (highScore_->scoreIsHigh(player1_->score())) {
          highScore_->setP1High(true);
          highScore_->setP2High(false);
          setState(kHighScoreEntry_);
        } else {
          setState(kAttract_);
        }
      }
    }
    break;
  case kHighScoreEntry_:
    break;
  }

  currentPlayer_->update();
  hud_->update();
}
