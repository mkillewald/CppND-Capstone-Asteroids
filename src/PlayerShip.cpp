#include "PlayerShip.h"
#include "Renderer.h"

PlayerShip::PlayerShip(std::size_t grid_width, std::size_t grid_height) {
  setColor(0x00, 0x00, 0xFF, 0xFF);
  init(grid_width, grid_height);
}
PlayerShip::~PlayerShip() {}

bool PlayerShip::alive() const { return alive_; }

void PlayerShip::init(std::size_t grid_width, std::size_t grid_height) {
  pos_.x = grid_width / 2;
  pos_.y = grid_height / 2;
  vel_.x = 0;
  vel_.y = 0;
  angle_ = -1.6; // ship faces top of window

  // player's ship
  lines_.emplace_back(sLine{-14, -8, 10, 0});
  lines_.emplace_back(sLine{-14, 8, 10, 0});
  lines_.emplace_back(sLine{-10, -6, -10, 6});

  // thruster
  lines_.emplace_back(sLine{-18, 0, -11, -4});
  lines_.emplace_back(sLine{-18, 0, -11, 4});
}

void PlayerShip::update() {
  switch (rot_) {
  case left_:
    angle_ -= 0.12;
    break;
  case right_:
    angle_ += 0.12;
    break;
  }
}

void PlayerShip::draw(Renderer *const renderer) const {
  for (int i = 0; i < lines_.size(); i++) {
    if (i > 2 && !thrust_) {
      // no thrust, cool our jets!
      continue;
    }
    renderer->drawLine(lines_[i], pos_, angle_, color_);
  }
}

void PlayerShip::rotateLeft() { rot_ = left_; }
void PlayerShip::rotateRight() { rot_ = right_; }
void PlayerShip::rotateOff() { rot_ = none_; }
void PlayerShip::thrustOn() { thrust_ = true; }
void PlayerShip::thrustOff() { thrust_ = false; }
void PlayerShip::fire() {}
void PlayerShip::hyperspace() {}