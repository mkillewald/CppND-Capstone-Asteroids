#include "Asteroid.h"
#include "Random.h"

#include <cstddef>

Asteroid::Asteroid(const std::size_t grid_width, const std::size_t grid_height,
                   float game_scale)
    : GameObject(grid_width, grid_height, game_scale),
      type_(Random::randomInt(0, 3)) {
  setColorRGBA(0xFF, 0xFF, 0xFF, 0x99);
  setAcceleration({0.0f, 0.0f});
  setMaxVelocity(15.0f);
  setAngle(0.0f);
  setScale(kLargeScale_ * gameScale());
  setRadius(kRadius_ * scale());

  // TODO: make sure to spawn outside "circle of safety"
  setPosition({Random::randomFloat(0.0f, grid_width),
               Random::randomFloat(0.0f, grid_height)});

  setVelocity({Random::randomSign() * Random::randomFloat(0.3, 1.0),
               Random::randomSign() * Random::randomFloat(0.3, 1.0)});
  initPoints();
}

void Asteroid::initPoints() {
  switch (type_) {
  case kType1_:
    initType1();
    break;
  case kType2_:
    initType2();
    break;
  case kType3_:
    initType3();
    break;
  case kType4_:
    initType4();
    break;
  }

  rotateMoveAndScalePoints(points_, position(), angle(), scale());
}

void Asteroid::initType1() {
  std::vector<SDL_Point> atOrigin;

  // points inferred from Ed Logg's Asteroids design sketches
  // https://sudonull.com/post/8376-How-to-create-a-vector-arcade-machine-Atari-Asteroids

  // asteroid type 1 at origin 160 X 160
  atOrigin.emplace_back(SDL_Point{-40, -80}); // 0
  atOrigin.emplace_back(SDL_Point{0, -40});   // 1
  atOrigin.emplace_back(SDL_Point{40, -80});  // 2
  atOrigin.emplace_back(SDL_Point{80, -40});  // 3
  atOrigin.emplace_back(SDL_Point{60, 0});    // 4
  atOrigin.emplace_back(SDL_Point{80, 40});   // 5
  atOrigin.emplace_back(SDL_Point{20, 80});   // 6
  atOrigin.emplace_back(SDL_Point{-40, 80});  // 7
  atOrigin.emplace_back(SDL_Point{-80, 40});  // 8
  atOrigin.emplace_back(SDL_Point{-80, -40}); // 9

  // copy atOrigin into points_
  points_ = atOrigin;

  // move atOrigin into private member atOrigin_ of base class GameObject so
  // that its contents cannot be directly accessed or modified by the derived
  // class.
  setAtOrigin(std::move(atOrigin));
}

void Asteroid::initType2() {
  std::vector<SDL_Point> atOrigin;

  // points inferred from Ed Logg's Asteroids design sketches
  // https://sudonull.com/post/8376-How-to-create-a-vector-arcade-machine-Atari-Asteroids

  // asteroid type 2 at origin 160 X 160
  atOrigin.emplace_back(SDL_Point{-40, -80}); // 0
  atOrigin.emplace_back(SDL_Point{0, -60});   // 1
  atOrigin.emplace_back(SDL_Point{40, -80});  // 2
  atOrigin.emplace_back(SDL_Point{80, -40});  // 3
  atOrigin.emplace_back(SDL_Point{40, -20});  // 4
  atOrigin.emplace_back(SDL_Point{80, 20});   // 5
  atOrigin.emplace_back(SDL_Point{40, 80});   // 6
  atOrigin.emplace_back(SDL_Point{-20, 60});  // 7
  atOrigin.emplace_back(SDL_Point{-40, 80});  // 8
  atOrigin.emplace_back(SDL_Point{-80, 40});  // 9
  atOrigin.emplace_back(SDL_Point{-60, 0});   // 10
  atOrigin.emplace_back(SDL_Point{-80, -40}); // 11

  // copy atOrigin into points_
  points_ = atOrigin;

  // move atOrigin into private member atOrigin_ of parent class GameObject so
  // that its contents cannot be directly accessed or modified by the derived
  // class.
  setAtOrigin(std::move(atOrigin));
}

void Asteroid::initType3() {
  std::vector<SDL_Point> atOrigin;

  // points inferred from Ed Logg's Asteroids design sketches
  // https://sudonull.com/post/8376-How-to-create-a-vector-arcade-machine-Atari-Asteroids

  // asteroid type 3 at origin 160 X 160
  atOrigin.emplace_back(SDL_Point{-20, -80}); // 0
  atOrigin.emplace_back(SDL_Point{40, -80});  // 1
  atOrigin.emplace_back(SDL_Point{80, -20});  // 2
  atOrigin.emplace_back(SDL_Point{80, 20});   // 3
  atOrigin.emplace_back(SDL_Point{40, 80});   // 4
  atOrigin.emplace_back(SDL_Point{0, 80});    // 5
  atOrigin.emplace_back(SDL_Point{0, 20});    // 6
  atOrigin.emplace_back(SDL_Point{-40, 80});  // 7
  atOrigin.emplace_back(SDL_Point{-80, 20});  // 8
  atOrigin.emplace_back(SDL_Point{-40, 0});   // 9
  atOrigin.emplace_back(SDL_Point{-80, -20}); // 10

  // copy atOrigin into points_
  points_ = atOrigin;

  // move atOrigin into private member atOrigin_ of parent class GameObject so
  // that its contents cannot be directly accessed or modified by the derived
  // class.
  setAtOrigin(std::move(atOrigin));
}

void Asteroid::initType4() {
  std::vector<SDL_Point> atOrigin;

  // points inferred from Ed Logg's Asteroids design sketches
  // https://sudonull.com/post/8376-How-to-create-a-vector-arcade-machine-Atari-Asteroids

  // asteroid type 4 at origin 160 X 160
  atOrigin.emplace_back(SDL_Point{-40, -80}); // 0
  atOrigin.emplace_back(SDL_Point{20, -80});  // 1
  atOrigin.emplace_back(SDL_Point{80, -40});  // 2
  atOrigin.emplace_back(SDL_Point{80, -20});  // 3
  atOrigin.emplace_back(SDL_Point{20, 0});    // 4
  atOrigin.emplace_back(SDL_Point{80, 40});   // 5
  atOrigin.emplace_back(SDL_Point{40, 80});   // 6
  atOrigin.emplace_back(SDL_Point{20, 60});   // 7
  atOrigin.emplace_back(SDL_Point{-40, 80});  // 8
  atOrigin.emplace_back(SDL_Point{-80, 20});  // 9
  atOrigin.emplace_back(SDL_Point{-80, -40}); // 10
  atOrigin.emplace_back(SDL_Point{-20, -40}); // 11

  // copy atOrigin into points_
  points_ = atOrigin;

  // move atOrigin into private member atOrigin_ of parent class GameObject so
  // that its contents cannot be directly accessed or modified by the derived
  // class.
  setAtOrigin(std::move(atOrigin));
}

std::uint32_t Asteroid::getScore() const {
  switch (size_) {
  case kLarge_:
    return 20;
    break;
  case kMedium_:
    return 50;
    break;
  case kSmall_:
    return 100;
    break;
  default:
    return 0;
    break;
  }
}

void Asteroid::hit() {
  // TODO: explode asteroid
  switch (size_) {
  case (kLarge_):
    size_ = kMedium_;
    setScale(kMediumScale_ * gameScale());
    setRadius(kRadius_ * scale());
    break;
  case (kMedium_):
    size_ = kSmall_;
    setScale(kSmallScale_ * gameScale());
    setRadius(kRadius_ * scale());
    break;
  case (kSmall_):
    setDestroyed(true);
    return;
    break;
  }
}