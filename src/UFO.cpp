#include "UFO.h"
#include "Renderer.h"

UFO::UFO(const std::size_t grid_width, const std::size_t grid_height,
         float game_scale, eUFOSize size)
    : GameObject(grid_width, grid_height, game_scale), size_(size) {
  setColorRGBA(0x00, 0x00, 0xFF, 0xFF);
  init();
}
UFO::~UFO() {}

void UFO::draw(Renderer *const renderer) const {
  drawObject(renderer);
  drawGhost(renderer);
}

void UFO::init() {
  position_.x = grid_width_ - 101;
  position_.y = 200;
  velocity_ = {-2.0, 0.0};

  if (size_ == kSluggo_) {
    scale_ = 1.0 * game_scale_;
  } else {
    scale_ = 0.7 * game_scale_;
  }

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
  // draw outline of ufo using base class draw() method
  GameObject::draw(renderer);

  // draw internal lines
  renderer->drawLine(points_[2], points_[7], color_);
  renderer->drawLine(points_[3], points_[6], color_);
}

void UFO::drawGhostLines(Renderer *const renderer,
                         sGFlags const &gflags) const {

  // draw ghost outline of ufo using base class drawGhostLines() method
  GameObject::drawGhostLines(renderer, gflags);

  SDL_Point p1{0, 0};
  SDL_Point p2{0, 0};

  // draw ghost of internal lines
  for (int i = 2, next = 7; i < 4; i++, next--) {
    p1.x = points_[i].x + gflags.s1x * static_cast<int>(grid_width_);
    p1.y = points_[i].y + gflags.s1y * static_cast<int>(grid_height_);
    p2.x = points_[next].x + gflags.s2x * static_cast<int>(grid_width_);
    p2.y = points_[next].y + gflags.s2y * static_cast<int>(grid_height_);
    renderer->drawLine(p1, p2, color_);
  }
}

void UFO::drawGhost(Renderer *const renderer) const {
  // handle corners
  if (edgeFlags_.test(kLeftEdge_) && edgeFlags_.test(kTopEdge_)) {
    // draw ghost at bottom, right corner
    drawGhostLines(renderer, {1, 1, 1, 1});
  } else if (edgeFlags_.test(kTopEdge_) && edgeFlags_.test(kRightEdge_)) {
    // draw ghost at bottom, left corner
    drawGhostLines(renderer, {-1, 1, -1, 1});
  } else if (edgeFlags_.test(kRightEdge_) && edgeFlags_.test(kBottomEdge_)) {
    // draw ghost at top, left corner
    drawGhostLines(renderer, {-1, -1, -1, -1});
  } else if (edgeFlags_.test(kBottomEdge_) && edgeFlags_.test(kLeftEdge_)) {
    // draw ghost at top, right corner
    drawGhostLines(renderer, {1, -1, 1, -1});
  }

  // handle edges
  if (edgeFlags_.test(kLeftEdge_)) {
    // draw ghost at right edge
    drawGhostLines(renderer, {1, 0, 1, 0});
  } else if (edgeFlags_.test(kRightEdge_)) {
    // draw ghost at left edge
    drawGhostLines(renderer, {-1, 0, -1, 0});
  }
  if (edgeFlags_.test(kTopEdge_)) {
    // draw ghost at bottom edge
    drawGhostLines(renderer, {0, 1, 0, 1});
  } else if (edgeFlags_.test(kBottomEdge_)) {
    // draw ghost at top edge
    drawGhostLines(renderer, {0, -1, 0, -1});
  }
}