#ifndef RENDERER_H
#define RENDERER_H

#include "GameObject.h"

#include <SDL.h>
#include <SDL_ttf.h>

#include <vector>

// forward declaration to avoid include cycle
class HUD;
class PlayerController;

// class based off Snake Game example code:
// https://github.com/udacity/CppND-Capstone-Snake-Game

class Renderer {
public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  // getters / setters
  std::size_t getGridWidth() const;
  std::size_t getGridHeight() const;
  SDL_Renderer *getSDLRenderer() const;

  // behavior methods
  void render(HUD *const hud, PlayerController *const player);
  void updateWindowTitle(int score, int fps);
  void drawLine(SDL_Point const &p1, SDL_Point const &p2,
                sColorRGBA const &color) const;
  int drawFilledCircle(int x, int y, int radius);

private:
  SDL_Window *sdl_window_ = nullptr;
  SDL_Renderer *sdl_renderer_ = nullptr;

  TTF_Font *font_ = nullptr;
  SDL_Surface *fontSurface_ = nullptr;
  SDL_Texture *fontTexture_ = nullptr;
  SDL_Rect fontRect;

  const std::size_t screen_width_;
  const std::size_t screen_height_;
  const std::size_t grid_width_;
  const std::size_t grid_height_;
};

#endif