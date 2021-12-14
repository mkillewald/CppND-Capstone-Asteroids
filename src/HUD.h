#ifndef HUD_H
#define HUD_H

#include "../lib/SDL_FontCache.h"

#include <string>

// forward declaration to avoid include cycle
class Game;
class Renderer;
class PlayerController;

class HUD {
public:
  HUD(Game const *game, Renderer const *renderer);
  ~HUD();

  // getters / setters

  // behavior methods
  void draw() const;
  void update();

private:
  const std::string kHighScores{"HIGH SCORES"};
  const std::string kPushStart{"PUSH START"};
  const std::string k1Coin1Start{"1 COIN 1 START"};

  Game const *game_ = nullptr;
  Renderer const *renderer_ = nullptr;
  PlayerController const *player1_ = nullptr;
  PlayerController const *player2_ = nullptr;
  FC_Font *small_ = nullptr;
  FC_Font *medium_ = nullptr;
  FC_Font *large_ = nullptr;
  int centerX_;
  int centerY_;
  Uint32 blinkTicks_;
  Uint32 blinkTickLimit_{1000};
  bool blink_{false};

  void drawP1Score() const;
  void drawP2Score() const;
  void drawHiScore() const;
  void drawPushStart() const;
  void drawHiScoreTable() const;
  void draw1Coin1Start() const;
};

#endif