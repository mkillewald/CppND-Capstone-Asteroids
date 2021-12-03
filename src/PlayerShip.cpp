#include "PlayerShip.h"
#include "Renderer.h"

PlayerShip::PlayerShip(const std::size_t grid_width,
                       const std::size_t grid_height, float game_scale)
    : GameObject(grid_width, grid_height, game_scale) {
  setColorRGBA(0x00, 0x00, 0xFF, 0xFF);
  init();
}
PlayerShip::~PlayerShip() {}

bool PlayerShip::alive() const { return alive_; }

void PlayerShip::init() {
  position_.x = grid_width_ / 2;
  position_.y = grid_height_ / 2;
  velocity_ = {0.0, 0.0};
  acceleration_ = {0.0, 0.0};
  maxVelocity_ = 15;
  angle_ = -90; // ship faces top of window
  scale_ = 1.0 * game_scale_;

  // points used from Ed Logg's Asteroids design document
  // https://sudonull.com/post/8376-How-to-create-a-vector-arcade-machine-Atari-Asteroids

  // player's ship at origin
  std::vector<SDL_Point> atOrigin;
  atOrigin.emplace_back(SDL_Point{-40, 32});  // 0
  atOrigin.emplace_back(SDL_Point{56, 0});    // 1
  atOrigin.emplace_back(SDL_Point{-40, -32}); // 2
  atOrigin.emplace_back(SDL_Point{-24, -16}); // 3
  atOrigin.emplace_back(SDL_Point{-24, 16});  // 4

  // thruster at origin
  atOrigin.emplace_back(SDL_Point{-24, -16}); // 5
  atOrigin.emplace_back(SDL_Point{-56, 0});   // 6
  atOrigin.emplace_back(SDL_Point{-24, 16});  // 7

  // copy atOrigin into points_
  points_ = atOrigin;

  // move atOrigin into private member atOrigin_ of parent class GameObject so
  // that its contents cannot be directly accessed or modified by the derived
  // class.
  setAtOrigin(std::move(atOrigin));

  // apply our starting angle and position
  rotateMoveAndScalePoints();
}

void PlayerShip::update() {
  switch (rot_) {
  case kRotLeft_:
    angle_ -= 5;
    break;
  case kRotRight_:
    angle_ += 5;
    break;
  }

  updatePosition();
  rotateMoveAndScalePoints();
  checkPointsAtEdges(0, static_cast<int>(grid_width_), 0,
                     static_cast<int>(grid_height_));
}

void PlayerShip::draw(Renderer *const renderer) const {
  drawObject(renderer);
  drawGhost(renderer);
}

void PlayerShip::rotateLeft() { rot_ = kRotLeft_; }
void PlayerShip::rotateRight() { rot_ = kRotRight_; }
void PlayerShip::rotateOff() { rot_ = kRotNone_; }
void PlayerShip::thrustOn() { thrust_ = true; }
void PlayerShip::thrustOff() { thrust_ = false; }
void PlayerShip::fire() {}
void PlayerShip::hyperspace() {}

void PlayerShip::updatePosition() {
  if (thrust_) {
    acceleration_.x = cos(angle_ * PI / 180.0);
    acceleration_.y = sin(angle_ * PI / 180.0);
  } else {
    acceleration_.x = 0.0;
    acceleration_.y = 0.0;
  }

  velocity_.x += acceleration_.x * 0.1; // accelleration was ramping up too
  velocity_.y += acceleration_.y * 0.1; // quickly, so we reduce magnitude here.

  if (velocity_.x > maxVelocity_) {
    velocity_.x = maxVelocity_;
  } else if (velocity_.x < -maxVelocity_) {
    velocity_.x = -maxVelocity_;
  }

  if (velocity_.y > maxVelocity_) {
    velocity_.y = maxVelocity_;
  }
  if (velocity_.y < -maxVelocity_) {
    velocity_.y = -maxVelocity_;
  }

  position_.x += velocity_.x;
  position_.y += velocity_.y;
  wrapCoordinates(position_);
}

void PlayerShip::drawObject(Renderer *const renderer) const {
  // draw ship
  int next;
  for (int i = 0; i < 5; i++) {
    if (i == 4) {
      next = 0;
    } else {
      next = i + 1;
    }
    renderer->drawLine(points_[i], points_[next], color_);
  }

  // draw thruster
  if (thrust_) {
    renderer->drawLine(points_[5], points_[6], color_);
    renderer->drawLine(points_[6], points_[7], color_);
  }
}

void PlayerShip::drawGhostLines(Renderer *const renderer,
                                sGFlags const &gflags) const {
  SDL_Point p1{0, 0};
  SDL_Point p2{0, 0};
  int next;
  for (int i = 0; i < 5; i++) {
    if (i == 4) {
      next = 0;
    } else {
      next = i + 1;
    }
    p1.x = points_[i].x + gflags.s1x * static_cast<int>(grid_width_);
    p1.y = points_[i].y + gflags.s1y * static_cast<int>(grid_height_);
    p2.x = points_[next].x + gflags.s2x * static_cast<int>(grid_width_);
    p2.y = points_[next].y + gflags.s2y * static_cast<int>(grid_height_);
    renderer->drawLine(p1, p2, color_);
  }

  if (thrust_) {
    for (int i = 5; i < 7; i++) {
      p1.x = points_[i].x + gflags.s1x * static_cast<int>(grid_width_);
      p1.y = points_[i].y + gflags.s1y * static_cast<int>(grid_height_);
      p2.x = points_[i + 1].x + gflags.s2x * static_cast<int>(grid_width_);
      p2.y = points_[i + 1].y + gflags.s2y * static_cast<int>(grid_height_);
      renderer->drawLine(p1, p2, color_);
    }
  }
}

void PlayerShip::drawGhost(Renderer *const renderer) const {
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