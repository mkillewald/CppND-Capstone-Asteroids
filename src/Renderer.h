#ifndef RENDERER_H
#define RENDERER_H

#include "GameObject.h"

#include <SDL.h>

#include <vector>

// forward declaration to avoid include cycle
class Asteroid;
class PlayerShip;
class UFO;

// class based off Snake Game example code:
// https://github.com/udacity/CppND-Capstone-Snake-Game

class Renderer {
public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void render(PlayerShip const &player, std::vector<Asteroid> &asteroids,
              UFO const &ufo);
  void updateWindowTitle(int score, int fps);
  void drawLine(sLine const &line, SDL_Point const &pos, float const &angle,
                sColor const &color);

private:
  SDL_Window *sdl_window_ = nullptr;     // Pointer for the SDL window
  SDL_Renderer *sdl_renderer_ = nullptr; // Pointer for the SDL renderer

  const std::size_t screen_width_;
  const std::size_t screen_height_;
  const std::size_t grid_width_;
  const std::size_t grid_height_;
};

#endif