#include <SDL.h>

class Asteroids {
public:
  // Contructor
  Asteroids(int height_, int width_);
  // Destructor
  ~Asteroids();

  void draw_circle(int center_x, int center_y, int radius_, int border_ = 0);
  void move_circle();

private:
  int height;                    // Height of the window
  int width;                     // Width of the window
  SDL_Renderer *renderer = NULL; // Pointer for the renderer
  SDL_Window *window = NULL;     // Pointer for the window
};