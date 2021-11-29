#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>

#include <vector>

// forward declaration to avoid include cycle
class Asteroid;
class PlayerShip;
class UFO;

struct line {
  int x1;
  int y1;
  int x2;
  int y2;
};

struct color {
  int r;
  int g;
  int b;
  int a;
};

class Renderer {
public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void render(PlayerShip const player, std::vector<Asteroid> &asteroids,
              UFO const &ufo);
  void updateWindowTitle(int score, int fps);
  void drawLine(line &line, color &color);

private:
  SDL_Window *sdl_window_ = nullptr;     // Pointer for the SDL window
  SDL_Renderer *sdl_renderer_ = nullptr; // Pointer for the SDL renderer

  const std::size_t screen_width_;
  const std::size_t screen_height_;
  const std::size_t grid_width_;
  const std::size_t grid_height_;
};

#endif