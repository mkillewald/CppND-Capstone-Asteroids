#include "UFO.h"
#include "Renderer.h"

UFO::UFO(const std::size_t grid_width, const std::size_t grid_height,
         float game_scale, eUFOSize size)
    : GameObject(grid_width, grid_height, game_scale), size_(size) {
  setColorRGBA(0x00, 0x00, 0xFF, 0xFF);
  init();
}

void UFO::init() {
  setPosition({gridWidth() - 101.0f, 200.0f});
  setVelocity({-2.0f, 0.0f});
  setAcceleration({0.0f, 0.0f});
  setAngle(0.0f);

  if (size_ == kSluggo_) {
    setScale(1.0f * gameScale());
  } else {
    setScale(0.7f * gameScale());
  }
  setRadius(80.0f * scale());

  std::vector<SDL_Point> atOrigin;

  // points inferred from Ed Logg's Asteroids design sketches
  // https://sudonull.com/post/8376-How-to-create-a-vector-arcade-machine-Atari-Asteroids

  // UFO at origin 200 X 120 (large)
  // use scale 0.7 for small and 1.0 for large
  atOrigin.emplace_back(SDL_Point{-20, -60}); // 0
  atOrigin.emplace_back(SDL_Point{20, -60});  // 1
  atOrigin.emplace_back(SDL_Point{40, -20});  // 2
  atOrigin.emplace_back(SDL_Point{100, 20});  // 3
  atOrigin.emplace_back(SDL_Point{40, 60});   // 4
  atOrigin.emplace_back(SDL_Point{-40, 60});  // 5
  atOrigin.emplace_back(SDL_Point{-100, 20}); // 6
  atOrigin.emplace_back(SDL_Point{-40, -20}); // 7

  // copy atOrigin into points_
  points_ = atOrigin;

  // move atOrigin into private member atOrigin_ of parent class GameObject so
  // that its contents cannot be directly accessed or modified by the derived
  // class.
  setAtOrigin(std::move(atOrigin));
}

void UFO::drawObject(Renderer *const renderer) const {
  // draw outline of ufo using base class drawObject() method
  GameObject::drawObject(renderer);

  // draw internal lines
  renderer->drawLine(points_[2], points_[7], colorRGBA());
  renderer->drawLine(points_[3], points_[6], colorRGBA());
}

void UFO::drawGhostLines(Renderer *const renderer,
                         sGFlags const &gflags) const {
  // draw ghost outline of ufo using base class drawGhostLines() method
  GameObject::drawGhostLines(renderer, gflags);

  // draw ghost of internal lines
  SDL_Point p1{0, 0};
  SDL_Point p2{0, 0};
  for (int i = 2, next = 7; i < 4; i++, next--) {
    p1.x = points_[i].x + gflags.s1x * static_cast<int>(gridWidth());
    p1.y = points_[i].y + gflags.s1y * static_cast<int>(gridHeight());
    p2.x = points_[next].x + gflags.s2x * static_cast<int>(gridWidth());
    p2.y = points_[next].y + gflags.s2y * static_cast<int>(gridHeight());
    renderer->drawLine(p1, p2, colorRGBA());
  }
}