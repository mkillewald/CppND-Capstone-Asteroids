#ifndef HUD_H
#define HUD_H

#include "PlayerController.h"

#include <SDL.h>
#include <SDL_ttf.h>

class HUD {
public:
  HUD(SDL_Renderer *sdl_renderer, PlayerController const *player1,
      PlayerController const *player2);
  ~HUD();

  // getters / setters

  // behavior methods
  void draw() const;

private:
  SDL_Renderer *sdl_renderer_ = nullptr;
  PlayerController *player1_ = nullptr;
  PlayerController *player2_ = nullptr;

  TTF_Font *small_ = nullptr;
  TTF_Font *medium_ = nullptr;
  TTF_Font *large_ = nullptr;

  SDL_Surface *fontSurface1_ = nullptr;
  SDL_Surface *fontSurface2_ = nullptr;
  SDL_Surface *fontSurface3_ = nullptr;

  SDL_Texture *fontTexture1_ = nullptr;
  SDL_Texture *fontTexture2_ = nullptr;
  SDL_Texture *fontTexture3_ = nullptr;

  SDL_Rect fontRect1;
  SDL_Rect fontRect2;
  SDL_Rect fontRect3;
};

#endif