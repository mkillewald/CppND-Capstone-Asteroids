#include <SDL.h>

#include "asteroids.h"

// Contructor which initialize the parameters.
Asteroids::Asteroids(int height_, int width_) : height(height_), width(width_) {
  SDL_Init(SDL_INIT_VIDEO); // Initializing SDL as Video
  SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); // setting draw color
  SDL_RenderClear(renderer);   // Clear the newly created window
  SDL_RenderPresent(renderer); // Reflects the changes done in the
                               //  window.
}

// Destructor
Asteroids::~Asteroids() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void Asteroids::draw_circle(int center_x, int center_y, int radius_,
                            int border_) {
  // Setting the color to be RED with 100% opaque (0% trasparent).
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

  // Drawing circle
  for (int x = center_x - radius_; x <= center_x + radius_; x++) {
    for (int y = center_y - radius_; y <= center_y + radius_; y++) {
      if ((border_ == 0 &&
           (std::pow(center_y - y, 2) + std::pow(center_x - x, 2)) <=
               std::pow(radius_, 2)) ||
          (border_ != 0 &&
           (std::pow(center_y - y, 2) + std::pow(center_x - x, 2)) <=
               std::pow(radius_, 2) &&
           (std::pow(center_y - y, 2) + std::pow(center_x - x, 2)) >=
               std::pow(radius_ - border_, 2))) {
        SDL_RenderDrawPoint(renderer, x, y);
      }
    }
  }

  // Show the change on the screen
  SDL_RenderPresent(renderer);
}

void Asteroids::move_circle() {
  // Setting the color to be RED with 100% opaque (0% trasparent).

  SDL_Event event; // Event variable
  while (!(event.type == SDL_QUIT)) {

    // Circle will go down!
    for (int i = 0; i < height; i++) {
      SDL_Delay(10);         // setting some Delay
      SDL_PollEvent(&event); // Catching the poll event.
      if (event.type == SDL_QUIT)
        return;
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
      SDL_RenderClear(renderer);
      draw_circle(width / 2, i, 25, 2);
    }

    // Circle will go up!
    for (int i = height; i > 0; i--) {
      SDL_Delay(10);         // setting some Delay
      SDL_PollEvent(&event); // Catching the poll event.
      if (event.type == SDL_QUIT)
        return;
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
      SDL_RenderClear(renderer);
      draw_circle(width / 2, i, 25, 2);
    }
  }
}