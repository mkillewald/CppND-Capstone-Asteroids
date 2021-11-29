#include "PlayerShip.h"
PlayerShip::PlayerShip(std::size_t grid_width, std::size_t grid_height) {
  init();
}
PlayerShip::~PlayerShip() {}

bool PlayerShip::alive() const { return alive_; }

void PlayerShip::init() {
  lines_.emplace_back(line{320, 200, 300, 240});
  lines_.emplace_back(line{300, 240, 340, 240});
  lines_.emplace_back(line{340, 240, 320, 200});
}

void PlayerShip::rotateLeft() {}
void PlayerShip::rotateRight() {}
void PlayerShip::thrust() {}
void PlayerShip::fire() {}
void PlayerShip::hyperspace() {}