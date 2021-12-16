#ifndef GAME_H
#define GAME_H

#include "HUD.h"
#include "PlayerController.h"

#include <SDL.h>

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
  int random_w();
  int random_h();
  int random_type();
  eGameState state() const;
  PlayerController *const player1() const;
  PlayerController *const player2() const;
  void setRunning(bool running);
  Uint32 numPlayers() const;

  // behavior methods
  void run(InputController *const inputController,
           std::size_t target_frame_duration);
  void insertCoin();
  void onePlayerStart();
  void twoPlayerStart();
  bool switchPlayer();

private:
  const Uint32 kDisplayTickLimit_{2000};

  std::unique_ptr<HUD> hud_;
  std::unique_ptr<PlayerController> player1_;
  std::unique_ptr<PlayerController> player2_;
  PlayerController *currentPlayer_ = nullptr;
  Renderer *renderer_ = nullptr;
  bool running_ = true;
  eGameState state_ = kAttract_;
  Uint32 numPlayers_{0};
  Uint32 credits_{0};
  Uint32 displayTicks_;

  std::random_device dev_;
  std::mt19937 engine_;
  std::uniform_int_distribution<int> random_w_;
  std::uniform_int_distribution<int> random_h_;
  std::uniform_int_distribution<int> random_type_;

  void setPlayers(Uint32 players);
  void setState(eGameState state);

  void input(InputController *const inputController);
  void update();
};

#endif