#include "PlayerShip.h"
PlayerShip::PlayerShip(std::size_t grid_width, std::size_t grid_height) {}
PlayerShip::~PlayerShip() {}

bool PlayerShip::alive() const { return alive_; }

void PlayerShip::rotateLeft() {}
void PlayerShip::rotateRight() {}
void PlayerShip::thrust() {}
void PlayerShip::fire() {}
void PlayerShip::hyperspace() {}