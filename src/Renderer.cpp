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
  player.draw(this);

  // Update screen
  SDL_RenderPresent(sdl_renderer_);
}

void Renderer::updateWindowTitle(int score, int fps) {
  std::string title{"Asteroids Score: " + std::to_string(score) +
                    " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window_, title.c_str());
}

void Renderer::drawLine(sLine const &line, SDL_Point const &pos,
                        float const &angle, sColor const &c) {

  float cosRot = cos(angle);
  float sinRot = sin(angle);
  sLine rotLine;
  rotLine.x1 = (line.x1 * cosRot - line.y1 * sinRot) + 0.4;
  rotLine.y1 = (line.x1 * sinRot + line.y1 * cosRot) + 0.4;
  rotLine.x2 = (line.x2 * cosRot - line.y2 * sinRot) + 0.4;
  rotLine.y2 = (line.x2 * sinRot + line.y2 * cosRot) + 0.4;

  SDL_SetRenderDrawColor(sdl_renderer_, c.r, c.g, c.b, c.a);
  // SDL_RenderSetScale(sdl_renderer_, 1.0, 1.0);
  SDL_RenderDrawLine(sdl_renderer_, rotLine.x1 + pos.x, rotLine.y1 + pos.y,
                     rotLine.x2 + pos.x, rotLine.y2 + pos.y);
}
