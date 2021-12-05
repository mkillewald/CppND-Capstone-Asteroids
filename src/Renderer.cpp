#include "Renderer.h"
#include "PlayerController.h"

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

void Renderer::render(PlayerController *const player) {
  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer_, 0x00, 0x00, 0x00, 0xFF);
  SDL_RenderClear(sdl_renderer_);

  // Render game objects
  player->draw(this);

  // Update screen
  SDL_RenderPresent(sdl_renderer_);
}

// TODO: remove score from window title once we have in game fonts working
void Renderer::updateWindowTitle(int score, int fps) {
  std::string title{"Asteroids Score: " + std::to_string(score) +
                    " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window_, title.c_str());
}

void Renderer::drawLine(SDL_Point const &p1, SDL_Point const &p2,
                        sColorRGBA const &color) const {
  SDL_SetRenderDrawColor(sdl_renderer_, color.r, color.g, color.b, color.a);
  // SDL_RenderSetScale(sdl_renderer_, 1.0, 1.0);
  SDL_RenderDrawLine(sdl_renderer_, p1.x, p1.y, p2.x, p2.y);
}
