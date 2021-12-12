#ifndef HUD_H
#define HUD_H

#include "../lib/SDL_FontCache.h"

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
  Game const *game_ = nullptr;
  Renderer const *renderer_ = nullptr;
  PlayerController const *player1_ = nullptr;
  PlayerController const *player2_ = nullptr;

  FC_Font *small_ = nullptr;
  FC_Font *medium_ = nullptr;
  FC_Font *large_ = nullptr;
};

#endif