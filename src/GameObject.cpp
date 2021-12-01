#include "GameObject.h"
#include "Game.h"
#include "Renderer.h"

#include <SDL.h>
#include <iostream>

// constructor / destructor
GameObject::GameObject(const std::size_t grid_width,
                       const std::size_t grid_height)
    : grid_width_(grid_width), grid_height_(grid_height) {}
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
  wrapCoordinates(position_);
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

void GameObject::wrapCoordinates(sVector2f &point) {
  // create toroidal mapping. mmm.. donuts!
  if (point.x < 0.0) {
    point.x += (float)grid_width_;
  } else if (point.x >= (float)grid_width_) {
    point.x -= (float)grid_width_;
  }

  if (point.y < 0.0) {
    point.y += (float)grid_height_;
  } else if (point.y >= (float)grid_height_) {
    point.y -= (float)grid_height_;
  }
}

void GameObject::update() {
  updatePosition();
  rotateAndMovePoints();
}

void GameObject::drawGhost(Renderer *const renderer) const {
  bool left = false;
  bool right = false;
  bool top = false;
  bool bottom = false;
  for (auto &point : points_) {
    if (point.x < 0) {
      left = true;
    } else if (point.x > (int)grid_width_) {
      right = true;
    }

    if (point.y < 0) {
      top = true;
    } else if (point.y > (int)grid_height_) {
      bottom = true;
    }
  }

  SDL_Point p1{0, 0};
  SDL_Point p2{0, 0};
  sLine ghostLine{p1, p2};
  if (left) {
    // draw ghost at right edge
    for (auto &line : lines_) {
      p1.x = line.p1.x + (int)grid_width_;
      p1.y = line.p1.y;
      p2.x = line.p2.x + (int)grid_width_;
      p2.y = line.p2.y;
      renderer->drawLine(ghostLine, color_);
    }

  } else if (right) {
    // draw ghost at left edge
    for (auto &line : lines_) {
      p1.x = line.p1.x - (int)grid_width_;
      p1.y = line.p1.y;
      p2.x = line.p2.x - (int)grid_width_;
      p2.y = line.p2.y;
      renderer->drawLine(ghostLine, color_);
    }
  }

  if (top) {
    for (auto &line : lines_) {
      p1.x = line.p1.x;
      p1.y = line.p1.y + (int)grid_height_;
      p2.x = line.p2.x;
      p2.y = line.p2.y + (int)grid_height_;
      renderer->drawLine(ghostLine, color_);
    }
  } else if (bottom) {
    for (auto &line : lines_) {
      p1.x = line.p1.x;
      p1.y = line.p1.y - (int)grid_height_;
      p2.x = line.p2.x;
      p2.y = line.p2.y - (int)grid_height_;
      renderer->drawLine(ghostLine, color_);
    }
  }
}

void GameObject::draw(Renderer *const renderer) const {
  for (auto &line : lines_) {
    renderer->drawLine(line, color_);
  }

  // if any point in object has crossed a window edge, aslo draw its ghost
  // also draw its "ghost"
  drawGhost(renderer);
}