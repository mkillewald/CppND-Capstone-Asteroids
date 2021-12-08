#include "PlayerController.h"
#include "Asteroid.h"
#include "GameObject.h"
#include "PlayerShip.h"
#include "UFO.h"

#include <SDL.h>

PlayerController::PlayerController(size_t grid_width, size_t grid_height,
                                   float game_scale)
    : ship_(grid_width, grid_height, game_scale),
      ufo_(grid_width, grid_height, game_scale, static_cast<UFO::eUFOSize>(0)) {

  // load maximum shots allowed into ships main cannon
  for (int i = 0; i < ship_.maxShots(); i++) {
    shots_.emplace_back(PlayerShot(grid_width, grid_height, game_scale));
  }

  // init first wave of asteroids
  asteroids_.emplace_back(Asteroid(grid_width, grid_height, game_scale, 0));
  asteroids_.emplace_back(Asteroid(grid_width, grid_height, game_scale, 1));
  asteroids_.emplace_back(Asteroid(grid_width, grid_height, game_scale, 2));
  asteroids_.emplace_back(Asteroid(grid_width, grid_height, game_scale, 3));
  // for (int i = 0; i < 4; i++) {
  //   asteroids_->emplace_back(
  //       Asteroid(grid_width, grid_height, game_scale,
  //       random_type_(engine_)));
  // }
}

unsigned long PlayerController::score() const { return score_; }
bool PlayerController::alive() const { return alive_; }
bool PlayerController::switchPlayer() const { return switchPlayer_; }
void PlayerController::setSwitchPlayer(bool switchPlayer) {
  switchPlayer_ = switchPlayer;
}

void PlayerController::update() {
  ship_.update();

  for (auto &shot : shots_) {
    if (shot.isFired()) {
      shot.update();
    }
  }

  for (auto &asteroid : asteroids_) {
    asteroid.update();
  }

  ufo_.update();
}

void PlayerController::draw(Renderer *const renderer) const {
  ship_.draw(renderer);

  for (auto &shot : shots_) {
    if (shot.isFired()) {
      shot.draw(renderer);
    }
  }

  for (auto &asteroid : asteroids_) {
    asteroid.draw(renderer);
  }

  ufo_.draw(renderer);
}

void PlayerController::rotateLeft() { ship_.setRotDir(GameObject::kRotLeft_); }
void PlayerController::rotateRight() {
  ship_.setRotDir(GameObject::kRotRight_);
}
void PlayerController::rotateOff() { ship_.setRotDir(GameObject::kRotNone_); }
void PlayerController::thrustOn() { ship_.setThrust(true); }
void PlayerController::thrustOff() { ship_.setThrust(false); }

void PlayerController::fire() {
  if (SDL_GetTicks() - reloadTicks_ < reloadTickLimit_) {
    return;
  }

  for (auto &shot : shots_) {
    if (!shot.isFired()) {
      shot.fire(ship_.nose(), ship_.getVelocity(), ship_.angle());
      reloadTicks_ = SDL_GetTicks();
      return;
    }
  }
}

void PlayerController::hyperspace() {}
