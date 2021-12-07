#include "PlayerShip.h"
#include "Renderer.h"

PlayerShip::PlayerShip(const std::size_t grid_width,
                       const std::size_t grid_height, float game_scale)
    : GameObject(grid_width, grid_height, game_scale) {
  setColorRGBA(0x00, 0x00, 0xFF, 0xFF);
  init();
}

void PlayerShip::init() {
  setPosition({gridWidth() / 2.0f, gridHeight() / 2.0f});
  setVelocity({0.0f, 0.0f});
  setAcceleration({0.0f, 0.0f});
  setMaxVelocity(15.0f);
  setAngle(-90.0f); // ship faces top of window
  setScale(1.0f * gameScale());

  // points used from Ed Logg's Asteroids design document
  // https://sudonull.com/post/8376-How-to-create-a-vector-arcade-machine-Atari-Asteroids

  // player's ship at origin
  std::vector<SDL_Point> atOrigin;
  atOrigin.emplace_back(SDL_Point{-40, 32});  // 0
  atOrigin.emplace_back(SDL_Point{56, 0});    // 1
  atOrigin.emplace_back(SDL_Point{-40, -32}); // 2
  atOrigin.emplace_back(SDL_Point{-24, -16}); // 3
  atOrigin.emplace_back(SDL_Point{-24, 16});  // 4

  // thruster at origin
  atOrigin.emplace_back(SDL_Point{-24, -16}); // 5
  atOrigin.emplace_back(SDL_Point{-56, 0});   // 6
  atOrigin.emplace_back(SDL_Point{-24, 16});  // 7

  // copy atOrigin into points_
  points_ = atOrigin;

  // move atOrigin into private member atOrigin_ of base class GameObject so
  // that its contents cannot be directly accessed or modified by the derived
  // class.
  setAtOrigin(std::move(atOrigin));

  // apply our starting angle and position
  rotateMoveAndScalePoints();
}

int PlayerShip::maxShots() const { return maxShots_; }
void PlayerShip::setThrust(bool thrust) { thrust_ = thrust; }

void PlayerShip::update() {
  switch (rotDir()) {
  case kRotLeft_:
    setAngle(angle() - 5);
    break;
  case kRotRight_:
    setAngle(angle() + 5);
    break;
  }

  updatePosition();
  rotateMoveAndScalePoints();
  checkPointsAtEdges(0, static_cast<int>(gridWidth()), 0,
                     static_cast<int>(gridHeight()));
}

SDL_Point PlayerShip::nose() { return points_[1]; }

void PlayerShip::updatePosition() {
  if (thrust_) {
    acceleration().x = cos(angle() * PI / 180.0);
    acceleration().y = sin(angle() * PI / 180.0);
  } else {
    acceleration().x = 0.0;
    acceleration().y = 0.0;
  }
  velocity().x += acceleration().x * 0.1; // accelleration was ramping up too
  velocity().y += acceleration().y * 0.1; // quickly, so we divide by 10

  if (velocity().x > maxVelocity()) {
    velocity().x = maxVelocity();
  } else if (velocity().x < -maxVelocity()) {
    velocity().x = -maxVelocity();
  }

  if (velocity().y > maxVelocity()) {
    velocity().y = maxVelocity();
  }
  if (velocity().y < -maxVelocity()) {
    velocity().y = -maxVelocity();
  }

  position().x += velocity().x;
  position().y += velocity().y;
  wrapCoordinates(position());
}

void PlayerShip::drawObject(Renderer *const renderer) const {
  // draw ship
  int next;
  for (int i = 0; i < 5; i++) {
    if (i == 4) {
      next = 0;
    } else {
      next = i + 1;
    }
    renderer->drawLine(points_[i], points_[next], colorRGBA());
  }

  // draw thruster
  if (thrust_) {
    // TODO: make thruster blink
    renderer->drawLine(points_[5], points_[6], colorRGBA());
    renderer->drawLine(points_[6], points_[7], colorRGBA());
  }
}

void PlayerShip::drawGhostLines(Renderer *const renderer,
                                sGFlags const &gflags) const {
  SDL_Point p1{0, 0};
  SDL_Point p2{0, 0};
  int next;
  for (int i = 0; i < 7; i++) {
    if (i == 4) {
      next = 0;
    } else {
      next = i + 1;
    }
    if (i > 4 && !thrust_) {
      // TODO: make thruster blink
      break;
    }
    p1.x = points_[i].x + gflags.s1x * static_cast<int>(gridWidth());
    p1.y = points_[i].y + gflags.s1y * static_cast<int>(gridHeight());
    p2.x = points_[next].x + gflags.s2x * static_cast<int>(gridWidth());
    p2.y = points_[next].y + gflags.s2y * static_cast<int>(gridHeight());
    renderer->drawLine(p1, p2, colorRGBA());
  }
}