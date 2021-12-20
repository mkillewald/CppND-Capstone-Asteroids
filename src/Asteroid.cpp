#include "Asteroid.h"
#include "Game.h"

#include <cstddef>

Asteroid::Asteroid(const std::size_t grid_width, const std::size_t grid_height,
                   float game_scale, int type)
    : GameObject(grid_width, grid_height, game_scale), type_(type) {
  setColorRGBA(0xFF, 0xFF, 0xFF, 0x99);
  init();
}

void Asteroid::init() {
  setAcceleration({0.0f, 0.0f});
  setMaxVelocity(15.0f);
  setAngle(0.0f);
  setScale(2.0f * gameScale());

  switch (type_) {
  case kType1_:
    setPosition({100.0f, 100.0f});
    setVelocity({0.4f, 0.7f});
    initType1();
    break;
  case kType2_:
    setPosition({gridWidth() - 100.0f, 100.0f});
    setVelocity({-0.8f, 0.6f});
    initType2();
    break;
  case kType3_:
    setPosition({gridWidth() - 100.0f, gridHeight() - 100.0f});
    setVelocity({-0.2f, -0.9f});
    initType3();
    break;
  case kType4_:
    setPosition({100.0f, gridHeight() - 100.0f});
    setVelocity({0.9, -0.4});
    initType4();
    break;
  }

  rotateMoveAndScalePoints(points_, position(), angle(), scale());
}

void Asteroid::initType1() {
  setRadius(80.0f * scale());
  std::vector<SDL_Point> atOrigin;

  // points inferred from Ed Logg's Asteroids design sketches
  // https://sudonull.com/post/8376-How-to-create-a-vector-arcade-machine-Atari-Asteroids

  // asteroid type 1 at origin 160 X 160 (medium)
  // use scale 0.5 for small and 2.0 for large
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
  setRadius(80.0f * scale());
  std::vector<SDL_Point> atOrigin;

  // points inferred from Ed Logg's Asteroids design sketches
  // https://sudonull.com/post/8376-How-to-create-a-vector-arcade-machine-Atari-Asteroids

  // asteroid type 2 at origin 160 X 160 (medium)
  // use scale 0.5 for small and 2.0 for large
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
  setRadius(80.0f * scale());
  std::vector<SDL_Point> atOrigin;

  // points inferred from Ed Logg's Asteroids design sketches
  // https://sudonull.com/post/8376-How-to-create-a-vector-arcade-machine-Atari-Asteroids

  // asteroid type 3 at origin 160 X 160 (medium)
  // use scale 0.5 for small and 2.0 for large
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
  setRadius(80.0f * scale());
  std::vector<SDL_Point> atOrigin;

  // points inferred from Ed Logg's Asteroids design sketches
  // https://sudonull.com/post/8376-How-to-create-a-vector-arcade-machine-Atari-Asteroids

  // asteroid type 4 at origin 160 X 160 (medium)
  // use scale 0.5 for small and 2.0 for large
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