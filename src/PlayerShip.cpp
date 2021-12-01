#include "PlayerShip.h"
#include "Renderer.h"

PlayerShip::PlayerShip(const std::size_t grid_width,
                       const std::size_t grid_height)
    : GameObject(grid_width, grid_height) {
  setColorRGBA(0x00, 0x00, 0xFF, 0xFF);
  init();
}
PlayerShip::~PlayerShip() {}

bool PlayerShip::alive() const { return alive_; }

void PlayerShip::init() {
  position_.x = grid_width_ / 2;
  position_.y = grid_height_ / 2;
  velocity_ = {0.0, 0.0};
  acceleration_ = {0.0, 0.0};
  maxVelocity_ = 15;
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
  // class.
  setAtOrigin(std::move(atOrigin));

  // connect the dots: player's ship
  lines_.emplace_back(sLine{points_[0], points_[1]});
  lines_.emplace_back(sLine{points_[1], points_[2]});
  lines_.emplace_back(sLine{points_[3], points_[4]});

  // connect the dots: thruster
  thrustLines_.emplace_back(sLine{points_[5], points_[6]});
  thrustLines_.emplace_back(sLine{points_[6], points_[7]});

  // apply our starting angle and position
  rotateAndMovePoints();
}

void PlayerShip::update() {
  switch (rot_) {
  case kRotLeft_:
    angle_ -= 5;
    break;
  case kRotRight_:
    angle_ += 5;
    break;
  }

  updatePosition();
  rotateAndMovePoints();
  checkPointsAtEdges(0, (int)grid_width_, 0, (int)grid_height_);
}

void PlayerShip::draw(Renderer *const renderer) const {
  // draw ship
  GameObject::draw(renderer);
  // draw thruster
  if (thrust_) {
    drawThrust(renderer);
  }
}

void PlayerShip::rotateLeft() { rot_ = kRotLeft_; }
void PlayerShip::rotateRight() { rot_ = kRotRight_; }
void PlayerShip::rotateOff() { rot_ = kRotNone_; }
void PlayerShip::thrustOn() { thrust_ = true; }
void PlayerShip::thrustOff() { thrust_ = false; }
void PlayerShip::fire() {}
void PlayerShip::hyperspace() {}

void PlayerShip::updatePosition() {
  if (thrust_) {
    acceleration_.x = cos(angle_ * PI / 180.0);
    acceleration_.y = sin(angle_ * PI / 180.0);
  } else {
    acceleration_.x = 0.0;
    acceleration_.y = 0.0;
  }

  velocity_.x += acceleration_.x * 0.1; // accelleration was ramping up too
  velocity_.y += acceleration_.y * 0.1; // quickly, so we reduce magnitude here.

  if (velocity_.x > maxVelocity_) {
    velocity_.x = maxVelocity_;
  } else if (velocity_.x < -maxVelocity_) {
    velocity_.x = -maxVelocity_;
  }

  if (velocity_.y > maxVelocity_) {
    velocity_.y = maxVelocity_;
  }
  if (velocity_.y < -maxVelocity_) {
    velocity_.y = -maxVelocity_;
  }

  position_.x += velocity_.x;
  position_.y += velocity_.y;
  wrapCoordinates(position_);
}

void PlayerShip::drawThrust(Renderer *const renderer) const {
  drawObject(renderer, thrustLines_);
  drawGhost(renderer, thrustLines_);
}