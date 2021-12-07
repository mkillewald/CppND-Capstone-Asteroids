#include "PlayerShot.h"
#include "GameObject.h"
#include "Renderer.h"

PlayerShot::PlayerShot(const std::size_t grid_width,
                       const std::size_t grid_height, float game_scale)
    : GameObject(grid_width, grid_height, game_scale) {
  // setPosition({0.0f, 0.0f});
  // setVelocity({0.0f, 0.0f});
  // setAcceleration({0.0f, 0.0f});
  // setMaxVelocity(15.0f);
  // setAngle(0.0f);
  setScale(1.0f * gameScale());

  std::vector<SDL_Point> atOrigin;
  atOrigin.emplace_back(SDL_Point{0, 0}); // 0

  // copy atOrigin into points_
  points_ = atOrigin;

  // move atOrigin into private member atOrigin_ of base class GameObject so
  // that its contents cannot be directly accessed or modified by the derived
  // class.
  setAtOrigin(std::move(atOrigin));
}

bool PlayerShot::isFired() const { return isFired_; }
void PlayerShot::setIsFired(bool isFired) { isFired_ = isFired; }

void PlayerShot::fire(SDL_Point point_in, sVector2f velocity_in,
                      float angle_in) {
  setIsFired(true);
  // inialize with ships nose position and velocity
  setPosition({(float)point_in.x, (float)point_in.y});
  setVelocity(velocity_in);
  setAngle(angle_in);

  // move outward from ship at ships angle of rotation when fired
  velocity().x += 15.0f * cos(angle() * PI / 180.0);
  velocity().y += 15.0f * sin(angle() * PI / 180.0);
}

void PlayerShot::draw(Renderer *const renderer) const { drawObject(renderer); }

void PlayerShot::drawObject(Renderer *const renderer) const {
  renderer->drawFilledCircle(points_[0].x, points_[0].y, 2);
}