#include "PlayerController.h"
#include "Asteroid.h"
#include "GameObject.h"
#include "PlayerShip.h"
#include "UFO.h"

#include <SDL.h>

#include <cstddef>
#include <cstdint>

PlayerController::PlayerController(std::size_t grid_width,
                                   std::size_t grid_height, float game_scale)
    : ship_(grid_width, grid_height, game_scale),
      ufo_(grid_width, grid_height, game_scale, static_cast<UFO::eUFOSize>(0)) {

  // load maximum shots allowed into ships main cannon
  for (int i = 0; i < ship_.maxShots(); i++) {
    playerShots_.emplace_back(PlayerShot(grid_width, grid_height, game_scale));
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

bool PlayerController::alive() const { return alive_; }
void PlayerController::setAlive(bool alive) { alive_ = alive; }
bool PlayerController::switchPlayer() const { return switchPlayer_; }
void PlayerController::setSwitchPlayer(bool switchPlayer) {
  switchPlayer_ = switchPlayer;
}
std::uint32_t PlayerController::lives() const { return lives_; }
void PlayerController::setLives(std::uint32_t lives) { lives_ = lives; }
std::uint32_t PlayerController::score() const { return score_; }
void PlayerController::setScore(std::uint32_t score) { score_ = score; }
void PlayerController::addScore(std::uint32_t score) { score_ += score; }

bool PlayerController::gunCharging() const { return gunCharging_; }
void PlayerController::setGunCharging(bool gunCharging) {
  gunCharging_ = gunCharging;
}

bool PlayerController::gunReloading() const {
  return SDL_GetTicks() - reloadTicks_ < reloadTickLimit_;
}

void PlayerController::update() {
  // update opbjects
  if (!ship_.destroyed()) {
    ship_.update();
  }

  for (auto &shot : playerShots_) {
    if (shot.isFired()) {
      shot.update();
    }
  }

  for (auto &asteroid : asteroids_) {
    if (!asteroid.destroyed()) {
      asteroid.update();
    }
  }

  // recharge gun if needed
  if (gunCharging() && !playerShots_[playerShots_.size() - 1].isFired()) {
    setGunCharging(false);
  }

  if (!ufo_.destroyed()) {
    ufo_.update();
  }

  // check collisions
  for (auto &asteroid : asteroids_) {
    if (!asteroid.destroyed()) {
      if (!ship_.destroyed() && asteroid.collide(ship_)) {
        // 1. check ship vs asteroid collisons
        asteroid.setDestroyed(true);
        // TODO: split asteroid
        // TODO: add score for asteroid
        die();
      } else if (!ufo_.destroyed() && asteroid.collide(ufo_)) {
        // 2. check ufo vs asteroid collision
        asteroid.setDestroyed(true);
        // TODO:  split asteroid
        ufo_.setDestroyed(true);
      } else {
        for (auto &shot : playerShots_) {
          // 3. check player shot vs asteroid collisions
          if (shot.isFired() && asteroid.collide(shot)) {
            shot.setIsFired(false);
            asteroid.setDestroyed(true);
            // TODO: split asteroid
            // TODO: do actual scoring
            addScore(10);
          }
        }
      }
    }
  }

  // TODO: 4. check ship vs ufo shot collisions

  if (!ufo_.destroyed()) {
    // 5. check ship vs ufo collisions
    if (!ship_.destroyed() && !ufo_.destroyed() && ufo_.collide(ship_)) {
      ufo_.setDestroyed(true);
      // TODO: add score for UFO
      die();
    } else {
      for (auto &shot : playerShots_) {
        // 6. check player shot vs ufo collisions
        if (shot.isFired() && !ufo_.destroyed() && ufo_.collide(shot)) {
          shot.setIsFired(false);
          ufo_.setDestroyed(true);
          // TODO: add score for UFO
        }
      }
    }
  }
}

void PlayerController::draw(Renderer *const renderer) const {
  if (!ship_.destroyed()) {
    ship_.draw(renderer);
  }

  for (auto &shot : playerShots_) {
    if (shot.isFired()) {
      shot.draw(renderer);
    }
  }

  for (auto &asteroid : asteroids_) {
    if (!asteroid.destroyed()) {
      asteroid.draw(renderer);
    }
  }

  if (!ufo_.destroyed()) {
    ufo_.draw(renderer);
  }
}

void PlayerController::drawLives(Renderer *const renderer, int const &x,
                                 int const &y, SDL_Color const &color) const {
  if (lives() == 0) {
    return;
  }

  for (int i = 0; i < lives() - 1; i++) {
    ship_.drawLife(renderer, x + 24 * i, y, color);
  }
}

void PlayerController::initPlayer() {
  setLives(4);
  setScore(0);
  setSwitchPlayer(false);
  // TODO: init asteroids (wave 1)
  // TODO: init ufo
}

void PlayerController::start() {
  setAlive(true);
  // TODO: wait for clear asteroid field
  ship_.reset();
}

void PlayerController::die() {
  rotateOff();
  thrustOff();
  ship_.setDestroyed(true);
  setAlive(false);
  minusLife();
  // TODO: explode ship
  setSwitchPlayer(true);
}

void PlayerController::addLife() { lives_++; }
void PlayerController::minusLife() {
  if (lives() == 0) {
    return;
  }
  lives_--;
}

void PlayerController::rotateLeft() {
  if (!alive()) {
    return;
  }
  ship_.setRotDir(GameObject::kRotLeft_);
}

void PlayerController::rotateRight() {
  if (!alive()) {
    return;
  }
  ship_.setRotDir(GameObject::kRotRight_);
}

void PlayerController::rotateOff() { ship_.setRotDir(GameObject::kRotNone_); }

void PlayerController::thrustOn() {
  if (!alive()) {
    return;
  }
  ship_.setThrust(true);
}

void PlayerController::thrustOff() { ship_.setThrust(false); }

void PlayerController::fire() {
  if (!alive() || gunCharging() || gunReloading()) {
    return;
  }

  for (int i = 0; i < playerShots_.size(); i++) {
    if (!playerShots_[i].isFired()) {
      playerShots_[i].fire(ship_.nose(), ship_.getVelocity(), ship_.angle());
      if (i == playerShots_.size() - 1) {
        setGunCharging(true);
      }
      reloadTicks_ = SDL_GetTicks();
      return;
    }
  }
}

void PlayerController::hyperspace() {}
