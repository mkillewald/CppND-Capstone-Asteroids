#ifndef GAME_H
#define GAME_H

#include "HUD.h"
#include "HighScore.h"
#include "PlayerController.h"

#include <SDL.h>

#include <cstdint>
#include <memory>
#include <random>
#include <vector>

// forward declaration to avoid include cycle
class InputController;
class Renderer;

class Game {
public:
  enum eGameState {
    kAttract_,
    kReadyToPlay_,
    kReadyPlayer1_,
    kReadyPlayer2_,
    kPlay_,
    kGameOver_,
    kHighScoreEntry_
  };

  // Contructor
  Game(Renderer *const renderer, float game_scale);

  // getters / setters
  eGameState state() const;
  void setState(eGameState state);
  PlayerController *const player1() const;
  PlayerController *const player2() const;
  PlayerController *const currentPlayer() const;
  void setCurrentPlayer(PlayerController *const player);
  HighScore *const highScore() const;
  HUD *const hud() const;
  void setRunning(bool running);
  std::uint32_t numPlayers() const;

  // behavior methods
  void run(InputController *const inputController,
           std::size_t target_frame_duration);
  void insertCoin();
  void onePlayerStart();
  void twoPlayerStart();
  bool switchPlayer();

private:
  const std::uint32_t kDisplayTickLimit_{2000};

  std::unique_ptr<HUD> hud_;
  std::unique_ptr<HighScore> highScore_;
  std::unique_ptr<PlayerController> player1_;
  std::unique_ptr<PlayerController> player2_;
  PlayerController *currentPlayer_ = nullptr;
  Renderer *renderer_ = nullptr;
  bool running_ = true;
  eGameState state_ = kAttract_;
  std::uint32_t numPlayers_{0};
  std::uint32_t credits_{0};
  std::uint32_t displayTicks_;

  void setPlayers(unsigned int players);

  void input(InputController *const inputController);
  void update();
};

#endif