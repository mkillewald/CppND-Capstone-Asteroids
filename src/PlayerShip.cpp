#include "PlayerShip.h"
#include "Renderer.h"

PlayerShip::PlayerShip(std::size_t grid_width, std::size_t grid_height) {
  setColorRGBA(0x00, 0x00, 0xFF, 0xFF);
  init(grid_width, grid_height);
}
PlayerShip::~PlayerShip() {}

bool PlayerShip::alive() const { return alive_; }

void PlayerShip::init(std::size_t grid_width, std::size_t grid_height) {
  position_.x = grid_width / 2;
  position_.y = grid_height / 2;
  velocity_ = {0.1, 0.1};
  acceleration_ = {0.0, 0.0};
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
  // classes.
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

void PlayerShip::draw(Renderer *const renderer) const {
  for (int i = 0; i < lines_.size(); i++) {
    if (i > 2 && !thrust_) {
      // no thrust, cool our jets!
      continue;
    }
    renderer->drawLine(lines_[i], color_);
  }
}

void PlayerShip::rotateLeft() { rot_ = left_; }
void PlayerShip::rotateRight() { rot_ = right_; }
void PlayerShip::rotateOff() { rot_ = none_; }
void PlayerShip::thrustOn() { thrust_ = true; }
void PlayerShip::thrustOff() { thrust_ = false; }
void PlayerShip::fire() {}
void PlayerShip::hyperspace() {}