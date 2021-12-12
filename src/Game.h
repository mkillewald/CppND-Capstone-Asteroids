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

// class based off Snake Game example code:
// https://github.com/udacity/CppND-Capstone-Snake-Game

class Game {
public:
  enum eGameState { kAttract_, kReadyToPlay_, kPlay_, kHighScoreEntry_ };

  // Contructor
  Game(Renderer *const renderer, float game_scale);

  // getters / setters
  int random_w();
  int random_h();
  int random_type();
  eGameState state() const;
  void setState(eGameState state);
  PlayerController const *player1() const;
  PlayerController const *player2() const;
  unsigned int numPlayers() const;

  // behavior methods
  void run(InputController *const input, std::size_t target_frame_duration);

private:
  std::unique_ptr<HUD> hud_;
  std::unique_ptr<PlayerController> player1_;
  std::unique_ptr<PlayerController> player2_;
  PlayerController *currentPlayer_ = nullptr;
  Renderer *renderer_ = nullptr;
  bool running_ = true;
  eGameState state_ = kAttract_;
  unsigned int numPlayers_;

  std::random_device dev_;
  std::mt19937 engine_;
  std::uniform_int_distribution<int> random_w_;
  std::uniform_int_distribution<int> random_h_;
  std::uniform_int_distribution<int> random_type_;

  void update();
};

#endif