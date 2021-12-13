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

unsigned long PlayerController::score() const { return score_; }
bool PlayerController::alive() const { return alive_; }
void PlayerController::setAlive(bool alive) { alive_ = alive; }
bool PlayerController::switchPlayer() const { return switchPlayer_; }
void PlayerController::setSwitchPlayer(bool switchPlayer) {
  switchPlayer_ = switchPlayer;
}

void PlayerController::update() {
  // update opbjects
  if (alive()) {
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

  if (!ufo_.destroyed()) {
    ufo_.update();
  }

  // check collisions
  for (auto &asteroid : asteroids_) {
    if (!asteroid.destroyed()) {
      if (alive() && asteroid.collide(ship_)) {
        // 1. check ship vs asteroid collisons
        asteroid.setDestroyed(true);
        // ship_.setDestroyed(true);
        // do stuff
      } else if (!ufo_.destroyed() && asteroid.collide(ufo_)) {
        // 2. check ufo vs asteroid collision
        asteroid.setDestroyed(true);
        ufo_.setDestroyed(true);
        // do stuff
      } else {
        for (auto &shot : playerShots_) {
          // 3. check player shot vs asteroid collisions
          if (shot.isFired() && asteroid.collide(shot)) {
            shot.setIsFired(false);
            asteroid.setDestroyed(true);
            // do stuff
          }
        }
      }
    }
  }

  // 4. check ship vs ufo shot collisions

  if (!ufo_.destroyed()) {
    // 5. check ship vs ufo collisions
    if (alive() && !ufo_.destroyed() && ufo_.collide(ship_)) {
      ufo_.setDestroyed(true);
      // ship_.setDestroyed(true);
      //  do stuff
    } else {
      for (auto &shot : playerShots_) {
        // 6. check player shot vs ufo collisions
        if (shot.isFired() && !ufo_.destroyed() && ufo_.collide(shot)) {
          shot.setIsFired(false);
          ufo_.setDestroyed(true);
          // do stuff
        }
      }
    }
  }
}

void PlayerController::draw(Renderer *const renderer) const {
  if (alive()) {
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
  if (!alive() || SDL_GetTicks() - reloadTicks_ < reloadTickLimit_) {
    return;
  }

  for (auto &shot : playerShots_) {
    if (!shot.isFired()) {
      shot.fire(ship_.nose(), ship_.getVelocity(), ship_.angle());
      reloadTicks_ = SDL_GetTicks();
      return;
    }
  }
}

void PlayerController::hyperspace() {}
