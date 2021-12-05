#include "PlayerController.h"
#include "Asteroid.h"
#include "GameObject.h"
#include "PlayerShip.h"
#include "UFO.h"

PlayerController::PlayerController(size_t grid_width, size_t grid_height,
                                   float game_scale) {
  // init player's ship
  ship_ = std::make_unique<PlayerShip>(grid_width, grid_height, game_scale);

  // init first wave of asteroids
  asteroids_ = std::make_unique<std::vector<Asteroid>>();
  asteroids_->emplace_back(Asteroid(grid_width, grid_height, game_scale, 0));
  asteroids_->emplace_back(Asteroid(grid_width, grid_height, game_scale, 1));
  asteroids_->emplace_back(Asteroid(grid_width, grid_height, game_scale, 2));
  asteroids_->emplace_back(Asteroid(grid_width, grid_height, game_scale, 3));
  // for (int i = 0; i < 4; i++) {
  //   asteroids_->emplace_back(
  //       Asteroid(grid_width, grid_height, game_scale,
  //       random_type_(engine_)));
  // }

  // init ufo
  ufo_ = std::make_unique<UFO>(grid_width, grid_height, game_scale,
                               static_cast<UFO::eUFOSize>(0));
}
PlayerController::~PlayerController() {}

unsigned long PlayerController::score() const { return score_; }
bool PlayerController::alive() const { return alive_; }
bool PlayerController::switchPlayer() const { return switchPlayer_; }
void PlayerController::setSwitchPlayer(bool switchPlayer) {
  switchPlayer_ = switchPlayer;
}

void PlayerController::update() {
  ship_->update();
  for (auto &asteroid : *asteroids_) {
    asteroid.update();
  }
  ufo_->update();
}

void PlayerController::draw(Renderer *const renderer) const {
  ship_->draw(renderer);
  for (auto &asteroid : *asteroids_) {
    asteroid.draw(renderer);
  }
  ufo_->draw(renderer);
}

void PlayerController::rotateLeft() { ship_->setRot(GameObject::kRotLeft_); }
void PlayerController::rotateRight() { ship_->setRot(GameObject::kRotRight_); }
void PlayerController::rotateOff() { ship_->setRot(GameObject::kRotNone_); }
void PlayerController::thrustOn() { ship_->setThrust(true); }
void PlayerController::thrustOff() { ship_->setThrust(false); }
void PlayerController::fire() {}
void PlayerController::hyperspace() {}
