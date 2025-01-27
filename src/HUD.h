#ifndef HUD_H
#define HUD_H

#include "../lib/SDL_FontCache.h"

#include <SDL.h>

#include <cstdint>
#include <string>

// forward declaration to avoid include cycle
class HighScore;
class Game;
class Renderer;
class PlayerController;

class HUD {
public:
  HUD(Game *const game, Renderer *const renderer);
  ~HUD();

  // getters / setters

  // behavior methods
  void draw() const;
  void update();
  void updateTableWidth();

private:
  const std::uint32_t kFastBlinkTickLimit_{250};
  const std::uint32_t kSlowBlinkTickLimit_{500};
  const std::string kHighScores{"HIGH SCORES"};
  const std::string kPushStart{"PUSH START"};
  const std::string k1Coin1Start{"1 COIN 1 START"};
  const std::string kPlayer1{"PLAYER 1"};
  const std::string kPlayer2{"PLAYER 2"};
  const std::string kGameOver{"GAME OVER"};
  const std::string kHiScoreEntry{"YOUR SCORE IS ONE OF THE TEN BEST\n"
                                  "PLEASE ENTER YOUR INITIALS\n"
                                  "PUSH ROTATE TO SELECT LETTER\n"
                                  "PUSH HYPERSPACE WHEN LETTER IS CORRECT"};

  Game *const game_ = nullptr;
  Renderer *const renderer_ = nullptr;
  PlayerController *const player1_ = nullptr;
  PlayerController *const player2_ = nullptr;
  SDL_Color hudColor;
  FC_Font *small_ = nullptr;
  FC_Font *medium_ = nullptr;
  FC_Font *large_ = nullptr;
  int centerX_;
  int centerY_;
  int tableX_;
  int tableY_;
  int spaceWidth_;
  int slotWidth_;
  int scoreWidth_;
  int tagWidth_;
  int maxWidth_;

  std::uint32_t blinkTicks_;
  bool blink_{false};

  void drawP1Score() const;
  void drawP2Score() const;
  void drawP1Lives() const;
  void drawP2Lives() const;
  void drawHiScore() const;
  void drawPushStart() const;
  void drawMessageCenterX(float y, const char *message) const;
  void drawHiScoreTable() const;
  void draw1Coin1Start() const;
  void drawScoreEntry() const;
};

#endif