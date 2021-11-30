#include "GameObject.h"
#include "Game.h"
#include "Renderer.h"

#include <SDL.h>

// constructor / destructor
GameObject::GameObject() {}
GameObject::~GameObject() {}

// getters / setters
unsigned int GameObject::ID() const { return id_; }
void GameObject::setColorRGBA(int r, int g, int b, int a) {
  color_.r = r;
  color_.g = g;
  color_.b = b;
  color_.a = a;
}

void GameObject::setAtOrigin(std::vector<SDL_Point> atOrigin) {
  atOrigin_ = std::move(atOrigin);
}

// typical behaviour methods
void GameObject::updatePosition() {
  position_.x += velocity_.x;
  position_.y += velocity_.y;
}

void GameObject::rotateAndMovePoints() {
  float cosRot = cos(angle_ * PI / 180.0);
  float sinRot = sin(angle_ * PI / 180.0);
  for (int i = 0; i < atOrigin_.size(); i++) {
    // apply rotatation to points atOrigin_ and save result in points_
    points_[i].x = (atOrigin_[i].x * cosRot - atOrigin_[i].y * sinRot) + 0.5;
    points_[i].y = (atOrigin_[i].x * sinRot + atOrigin_[i].y * cosRot) + 0.5;

    // move points to objects position
    points_[i].x += position_.x;
    points_[i].y += position_.y;
  }
}

void GameObject::update() {
  updatePosition();
  rotateAndMovePoints();
}

void GameObject::draw(Renderer *const renderer) const {
  for (auto &line : lines_) {
    renderer->drawLine(line, color_);
  }
}