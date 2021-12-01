#include "PlayerShip.h"
#include "Renderer.h"

PlayerShip::PlayerShip(const std::size_t grid_width,
                       const std::size_t grid_height)
    : GameObject(grid_width, grid_height) {
  //   grid_width_ = grid_width;
  //   grid_height_ = grid_height;
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

  // player's ship at origin
  std::vector<SDL_Point> atOrigin;
  atOrigin.emplace_back(SDL_Point{-14, -8}); // 0
  atOrigin.emplace_back(SDL_Point{10, 0});   // 1
  atOrigin.emplace_back(SDL_Point{-14, 8});  // 2
  atOrigin.emplace_back(SDL_Point{-10, -6}); // 3
  atOrigin.emplace_back(SDL_Point{-10, 6});  // 4

  // thruster at origin
  atOrigin.emplace_back(SDL_Point{-11, -4}); // 5
  atOrigin.emplace_back(SDL_Point{-18, 0});  // 6
  atOrigin.emplace_back(SDL_Point{-11, 4});  // 7

  // copy atOrigin into points_
  points_ = atOrigin;

  // move atOrigin into private member atOrigin_ of parent class GameObject so
  // that its contents cannot be directly accessed or modified by the derived
  // class.
  setAtOrigin(std::move(atOrigin));

  // connect the dots: player's ship
  lines_.emplace_back(sLine{points_[0], points_[1]});
  lines_.emplace_back(sLine{points_[1], points_[2]});
  lines_.emplace_back(sLine{points_[3], points_[4]});

  // connect the dots: thruster
  lines_.emplace_back(sLine{points_[5], points_[6]});
  lines_.emplace_back(sLine{points_[6], points_[7]});

  // apply our starting angle and position
  rotateAndMovePoints();
}

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

void PlayerShip::update() {
  switch (rot_) {
  case left_:
    angle_ -= 5;
    break;
  case right_:
    angle_ += 5;
    break;
  }

  updatePosition();
  rotateAndMovePoints();
}

// TODO: refactor this, too much code duplication!
void PlayerShip::drawGhost(Renderer *const renderer) const {
  bool left = false;
  bool right = false;
  bool top = false;
  bool bottom = false;
  for (auto &point : points_) {
    if (point.x < 0) {
      left = true;
    } else if (point.x > (int)grid_width_) {
      right = true;
    }

    if (point.y < 0) {
      top = true;
    } else if (point.y > (int)grid_height_) {
      bottom = true;
    }
  }

  SDL_Point p1{0, 0};
  SDL_Point p2{0, 0};
  sLine ghostLine{p1, p2};
  if (left) {
    // draw ghost at right edge
    for (int i = 0; i < lines_.size(); i++) {
      if (i > 2 && !thrust_) {
        // no thrust, cool our jets!
        continue;
      }
      p1.x = lines_[i].p1.x + (int)grid_width_;
      p1.y = lines_[i].p1.y;
      p2.x = lines_[i].p2.x + (int)grid_width_;
      p2.y = lines_[i].p2.y;
      renderer->drawLine(ghostLine, color_);
    }

  } else if (right) {
    // draw ghost at left edge
    for (int i = 0; i < lines_.size(); i++) {
      if (i > 2 && !thrust_) {
        // no thrust, cool our jets!
        continue;
      }
      p1.x = lines_[i].p1.x - (int)grid_width_;
      p1.y = lines_[i].p1.y;
      p2.x = lines_[i].p2.x - (int)grid_width_;
      p2.y = lines_[i].p2.y;
      renderer->drawLine(ghostLine, color_);
    }
  }

  if (top) {
    // draw ghost at bottom edge
    for (int i = 0; i < lines_.size(); i++) {
      if (i > 2 && !thrust_) {
        // no thrust, cool our jets!
        continue;
      }
      p1.x = lines_[i].p1.x;
      p1.y = lines_[i].p1.y + (int)grid_height_;
      p2.x = lines_[i].p2.x;
      p2.y = lines_[i].p2.y + (int)grid_height_;
      renderer->drawLine(ghostLine, color_);
    }
  } else if (bottom) {
    // draw ghost at top edge
    for (int i = 0; i < lines_.size(); i++) {
      if (i > 2 && !thrust_) {
        // no thrust, cool our jets!
        continue;
      }
      p1.x = lines_[i].p1.x;
      p1.y = lines_[i].p1.y - (int)grid_height_;
      p2.x = lines_[i].p2.x;
      p2.y = lines_[i].p2.y - (int)grid_height_;
      renderer->drawLine(ghostLine, color_);
    }
  }
}

void PlayerShip::draw(Renderer *const renderer) const {
  // draw Ship
  for (int i = 0; i < lines_.size(); i++) {
    if (i > 2 && !thrust_) {
      // no thrust, cool our jets!
      continue;
    }
    renderer->drawLine(lines_[i], color_);
  }

  // if any point in object has crossed a window edge, aslo draw its ghost
  // also draw its "ghost"
  drawGhost(renderer);
}

void PlayerShip::rotateLeft() { rot_ = left_; }
void PlayerShip::rotateRight() { rot_ = right_; }
void PlayerShip::rotateOff() { rot_ = none_; }
void PlayerShip::thrustOn() { thrust_ = true; }
void PlayerShip::thrustOff() { thrust_ = false; }
void PlayerShip::fire() {}
void PlayerShip::hyperspace() {}