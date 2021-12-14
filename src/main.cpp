#include "Game.h"
#include "InputController.h"
#include "Renderer.h"

#include <SDL.h>

#include <memory>

int main(int argc, char *argv[]) {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{1024};
  constexpr std::size_t kScreenHeight{768};
  constexpr std::size_t kGridWidth{1024};
  constexpr std::size_t kGridHeight{768};

  std::unique_ptr<Renderer> renderer = std::make_unique<Renderer>(
      kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  std::unique_ptr<InputController> input = std::make_unique<InputController>();
  std::unique_ptr<Game> game = std::make_unique<Game>(renderer.get(), 0.2);

  game->run(input.get(), kMsPerFrame);
  return 0;
}