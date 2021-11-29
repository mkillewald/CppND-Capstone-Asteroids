#include "Renderer.h"
#include "Asteroid.h"
#include "GameObject.h"
#include "PlayerShip.h"
#include "UFO.h"

#include <SDL.h>

#include <iostream>
#include <string>

// based off Snake Game example code:
// https://github.com/udacity/CppND-Capstone-Snake-Game

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, std::size_t grid_height)
    : screen_width_(screen_width), screen_height_(screen_height),
      grid_width_(grid_width), grid_height_(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize." << std::endl;
    std::cerr << "SDL_Error: " << SDL_GetError() << std::endl;
  }

  // Create Window
  sdl_window_ = SDL_CreateWindow("Asteroids", SDL_WINDOWPOS_CENTERED,
                                 SDL_WINDOWPOS_CENTERED, screen_width_,
                                 screen_height_, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window_) {
    std::cerr << "Window could not be created." << std::endl;
    std::cerr << "SDL_Error: " << SDL_GetError() << std::endl;
  }

  // Create renderer
  sdl_renderer_ = SDL_CreateRenderer(sdl_window_, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer_) {
    std::cerr << "Renderer could not be created." << std::endl;
    std::cerr << "SDL_Error: " << SDL_GetError() << std::endl;
  }
}

Renderer::~Renderer() {
  SDL_DestroyRenderer(sdl_renderer_);
  SDL_DestroyWindow(sdl_window_);
  SDL_Quit();
}

void Renderer::render(PlayerShip const &player,
                      std::vector<Asteroid> &asteroids, UFO const &ufo) {
  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer_, 0x00, 0x00, 0x00, 0xFF);
  SDL_RenderClear(sdl_renderer_);

  // Render game objects
  color shipColor{0x00, 0x00, 0xFF, 0xFF};
  player.draw(this, shipColor);

  // Update screen
  SDL_RenderPresent(sdl_renderer_);
}

void Renderer::updateWindowTitle(int score, int fps) {
  std::string title{"Asteroids Score: " + std::to_string(score) +
                    " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window_, title.c_str());
}

void Renderer::drawLine(line const &line, SDL_Point const &pos,
                        color const &c) {
  SDL_SetRenderDrawColor(sdl_renderer_, c.r, c.g, c.b, c.a);
  SDL_RenderSetScale(sdl_renderer_, 1.0, 1.0);
  SDL_RenderDrawLine(sdl_renderer_, line.x1 + pos.x, line.y1 + pos.y,
                     line.x2 + pos.x, line.y2 + pos.y);
}
