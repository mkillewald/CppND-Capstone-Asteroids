#include "asteroids.h"

#include <SDL.h>

int main(int argc, char *argv[]) {

  // Creating the game object by passing Height and Width value.
  Asteroids game(200, 400);

  // Starting the animation
  game.move_circle();

  return 1;
}