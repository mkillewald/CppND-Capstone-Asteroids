#include "Renderer.h"
#include "HUD.h"
#include "PlayerController.h"

#include <SDL.h>

#include <cstddef>
#include <iostream>
#include <string>

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

  // Enable alpha blending
  SDL_SetRenderDrawBlendMode(sdl_renderer_, SDL_BLENDMODE_BLEND);
}

Renderer::~Renderer() {
  SDL_DestroyRenderer(sdl_renderer_);
  SDL_DestroyWindow(sdl_window_);
  SDL_Quit();
}

std::size_t Renderer::gridWidth() const { return grid_width_; }
std::size_t Renderer::gridHeight() const { return grid_height_; }
SDL_Renderer *Renderer::sdlRenderer() const { return sdl_renderer_; }

void Renderer::render(HUD *const hud, PlayerController *const player) {
  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer_, 0x00, 0x00, 0x00, 0xFF);
  SDL_RenderClear(sdl_renderer_);

  // Render game objects
  player->draw(this);

  // Render game text
  hud->draw();

  // Update screen
  SDL_RenderPresent(sdl_renderer_);
}

void Renderer::updateWindowTitle(int score, int fps) {
  std::string title{"Asteroids FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window_, title.c_str());
}

void Renderer::drawLine(SDL_Point const &p1, SDL_Point const &p2,
                        SDL_Color const &color) const {
  SDL_SetRenderDrawColor(sdl_renderer_, color.r, color.g, color.b, color.a);
  SDL_RenderDrawLine(sdl_renderer_, p1.x, p1.y, p2.x, p2.y);
}

void Renderer::drawLine(int const &x1, int const &y1, int const &x2,
                        int const &y2, SDL_Color const &color) const {
  SDL_SetRenderDrawColor(sdl_renderer_, color.r, color.g, color.b, color.a);
  SDL_RenderDrawLine(sdl_renderer_, x1, y1, x2, y2);
}

// function is based on
// https://gist.github.com/Gumichan01/332c26f6197a432db91cc4327fcabb1c
int Renderer::drawFilledCircle(int const &x, int const &y, int const &radius,
                               SDL_Color const &color) const {
  int offsetx, offsety, d;
  int status;

  offsetx = 0;
  offsety = radius;
  d = radius - 1;
  status = 0;

  SDL_SetRenderDrawColor(sdl_renderer_, color.r, color.g, color.b, color.a);

  while (offsety >= offsetx) {

    status += SDL_RenderDrawLine(sdl_renderer_, x - offsety, y + offsetx,
                                 x + offsety, y + offsetx);
    status += SDL_RenderDrawLine(sdl_renderer_, x - offsetx, y + offsety,
                                 x + offsetx, y + offsety);
    status += SDL_RenderDrawLine(sdl_renderer_, x - offsetx, y - offsety,
                                 x + offsetx, y - offsety);
    status += SDL_RenderDrawLine(sdl_renderer_, x - offsety, y - offsetx,
                                 x + offsety, y - offsetx);

    if (status < 0) {
      status = -1;
      break;
    }

    if (d >= 2 * offsetx) {
      d -= 2 * offsetx + 1;
      offsetx += 1;
    } else if (d < 2 * (radius - offsety)) {
      d += 2 * offsety - 1;
      offsety -= 1;
    } else {
      d += 2 * (offsety - offsetx - 1);
      offsety -= 1;
      offsetx += 1;
    }
  }

  return status;
}