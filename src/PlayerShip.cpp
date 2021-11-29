#include "PlayerShip.h"
PlayerShip::PlayerShip(std::size_t grid_width, std::size_t grid_height) {
  init(grid_width, grid_height);
}
PlayerShip::~PlayerShip() {}

bool PlayerShip::alive() const { return alive_; }

void PlayerShip::init(std::size_t grid_width, std::size_t grid_height) {
  pos_.x = grid_width / 2;
  pos_.y = grid_height / 2;
  vel_.x = 0;
  vel_.y = 0;
  angle_ = 90.0;

  lines_.emplace_back(line{0, 0, -20, 40});
  lines_.emplace_back(line{-20, 40, 20, 40});
  lines_.emplace_back(line{20, 40, 0, 0});
}

void PlayerShip::rotateLeft() {}
void PlayerShip::rotateRight() {}
void PlayerShip::thrust() {}
void PlayerShip::fire() {}
void PlayerShip::hyperspace() {}