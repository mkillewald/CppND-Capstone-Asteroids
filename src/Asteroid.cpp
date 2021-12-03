#include "Asteroid.h"

#include <iostream>

Asteroid::Asteroid(const std::size_t grid_width, const std::size_t grid_height,
                   float game_scale, int type)
    : GameObject(grid_width, grid_height, game_scale), type_(type) {
  setColorRGBA(0x00, 0x00, 0xFF, 0xFF);
  init();
}
Asteroid::~Asteroid() {}

void Asteroid::init() {
  acceleration_ = {0.0, 0.0};
  maxVelocity_ = 15;
  angle_ = 0;
  scale_ = 2.0 * game_scale_;

  switch (type_) {
  case kType1_:
    position_.x = 100;
    position_.y = 100;
    velocity_ = {0.4, 0.7};
    initType1();
    break;
  case kType2_:
    position_.x = grid_width_ - 100;
    position_.y = 100;
    velocity_ = {-0.8, 0.6};
    initType2();
    break;
  case kType3_:
    position_.x = grid_width_ - 100;
    position_.y = grid_height_ - 100;
    velocity_ = {-0.2, -0.9};
    initType3();
    break;
  case kType4_:
    position_.x = 100;
    position_.y = grid_height_ - 100;
    velocity_ = {0.9, -0.4};
    initType4();
    break;
  // TODO: placed this here just to test points.. move to UFO class
  case kTypeUFO_:
    position_.x = grid_width_ - 101;
    position_.y = 200;
    velocity_ = {-2.0, 0.0};
    scale_ = 1.0 * game_scale_;
    initUFO();
    break;
  }

  rotateMoveAndScalePoints();
}

void Asteroid::initType1() {
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

  // move atOrigin into private member atOrigin_ of parent class GameObject so
  // that its contents cannot be directly accessed or modified by the derived
  // class.
  setAtOrigin(std::move(atOrigin));
}

void Asteroid::initType2() {
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

// TODO: placed this here just to test points.. move to UFO class
void Asteroid::initUFO() {
  std::vector<SDL_Point> atOrigin;

  // points inferred from Ed Logg's Asteroids design sketches
  // https://sudonull.com/post/8376-How-to-create-a-vector-arcade-machine-Atari-Asteroids

  // asteroid type 3 at origin 160 X 160 (medium)
  // use scale 0.5 for small and 2.0 for large
  atOrigin.emplace_back(SDL_Point{-20, -60}); // 0
  atOrigin.emplace_back(SDL_Point{20, -60});  // 1
  atOrigin.emplace_back(SDL_Point{40, -20});  // 2
  atOrigin.emplace_back(SDL_Point{100, 20});  // 3
  atOrigin.emplace_back(SDL_Point{40, 60});   // 4
  atOrigin.emplace_back(SDL_Point{-40, 60});  // 5
  atOrigin.emplace_back(SDL_Point{-100, 20}); // 6
  atOrigin.emplace_back(SDL_Point{-40, -20}); // 7

  // copy atOrigin into points_
  points_ = atOrigin;

  // move atOrigin into private member atOrigin_ of parent class GameObject so
  // that its contents cannot be directly accessed or modified by the derived
  // class.
  setAtOrigin(std::move(atOrigin));
}