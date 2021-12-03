#include "Controller.h"
#include "Game.h"
#include "Renderer.h"

#include <SDL.h>

int main(int argc, char *argv[]) {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{1024};
  constexpr std::size_t kScreenHeight{768};
  constexpr std::size_t kGridWidth{1024};
  constexpr std::size_t kGridHeight{768};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight, 0.3);

  game.run(controller, renderer, kMsPerFrame);
  return 0;
}