#ifndef HUD_H
#define HUD_H

#include <SDL_ttf.h>

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

private:
  Game const *game_ = nullptr;
  Renderer const *renderer_ = nullptr;
  PlayerController const *player1_ = nullptr;
  PlayerController const *player2_ = nullptr;

  TTF_Font *small_ = nullptr;
  TTF_Font *medium_ = nullptr;
  TTF_Font *large_ = nullptr;

  SDL_Surface *p1ScoreSfc_ = nullptr;
  SDL_Surface *p2ScoreSfc_ = nullptr;
  SDL_Surface *hiScoreSfc_ = nullptr;
  SDL_Surface *hiScoreTableSfc_ = nullptr;

  SDL_Texture *p1ScoreTxt_ = nullptr;
  SDL_Texture *p2ScoreTxt_ = nullptr;
  SDL_Texture *hiScoreTxt_ = nullptr;
  SDL_Texture *hiScoreTableTxt_ = nullptr;

  SDL_Rect p1ScoreRct_;
  SDL_Rect p2ScoreRct_;
  SDL_Rect hiScoreRct_;
  SDL_Rect hiScoreTableRct_;
};

#endif