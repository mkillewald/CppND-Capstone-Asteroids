#include "GameObject.h"
#include "Game.h"
#include "Renderer.h"

#include <SDL.h>

#include <bitset>

sVector2f sVector2f::operator+(sVector2f const &a) {
  x += a.x;
  y += a.y;
  return {x, y};
}

sVector2f sVector2f::operator+(float const &a) {
  x += a;
  y += a;
  return {x, y};
}

// constructor / destructor
GameObject::GameObject(const std::size_t grid_width,
                       const std::size_t grid_height, float game_scale)
    : grid_width_(grid_width), grid_height_(grid_height),
      game_scale_(game_scale) {}

// getters / setters
void GameObject::setAtOrigin(std::vector<SDL_Point> atOrigin) {
  atOrigin_ = std::move(atOrigin);
}

const std::size_t GameObject::gridWidth() const { return grid_width_; }
const std::size_t GameObject::gridHeight() const { return grid_height_; }

sColorRGBA GameObject::colorRGBA() const { return colorRGBA_; }
void GameObject::setColorRGBA(int r, int g, int b, int a) {
  colorRGBA_.r = r;
  colorRGBA_.g = g;
  colorRGBA_.b = b;
  colorRGBA_.a = a;
}

// unsigned int GameObject::ID() const { return id_; }
GameObject::eRotDir GameObject::rotDir() const { return rotDir_; }
void GameObject::setRotDir(eRotDir rotDir) { rotDir_ = rotDir; }

sVector2f &GameObject::position() { return position_; }
void GameObject::setPosition(sVector2f position) { position_ = position; }

sVector2f &GameObject::velocity() { return velocity_; }
sVector2f GameObject::getVelocity() const { return velocity_; }
void GameObject::setVelocity(sVector2f velocity) { velocity_ = velocity; }

sVector2f &GameObject::acceleration() { return acceleration_; }
void GameObject::setAcceleration(sVector2f acceleration) {
  acceleration_ = acceleration;
}

float GameObject::maxVelocity() const { return maxVelocity_; }
void GameObject::setMaxVelocity(float maxVelocity) {
  maxVelocity_ = maxVelocity;
}

float GameObject::gameScale() const { return game_scale_; };

float GameObject::scale() const { return scale_; }
void GameObject::setScale(float scale) { scale_ = scale; }

float GameObject::angle() const { return angle_; }
void GameObject::setAngle(float angle) { angle_ = angle; }

// typical behaviour methods
void GameObject::update() {
  updatePosition();
  rotateMoveAndScalePoints();
  checkPointsAtEdges(0, static_cast<int>(grid_width_), 0,
                     static_cast<int>(grid_height_));
}

void GameObject::draw(Renderer *const renderer) const {
  // draw object at position
  drawObject(renderer);

  // if any edgeFlags_ are set, draw object's "ghost"
  drawGhost(renderer);
}

void GameObject::updatePosition() {
  position_.x += velocity_.x;
  position_.y += velocity_.y;
  wrapCoordinates(position_);
}

void GameObject::rotateMoveAndScalePoints() {
  float cosRot = cos(angle_ * PI / 180.0);
  float sinRot = sin(angle_ * PI / 180.0);
  for (int i = 0; i < atOrigin_.size(); i++) {
    // apply rotatation to points atOrigin_ and save result in points_
    points_[i].x =
        scale_ * (atOrigin_[i].x * cosRot - atOrigin_[i].y * sinRot) + 0.5;
    points_[i].y =
        scale_ * (atOrigin_[i].x * sinRot + atOrigin_[i].y * cosRot) + 0.5;

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

void GameObject::checkPointsAtEdges(int const &left, int const &right,
                                    int const &top, int const &bottom) {
  edgeFlags_.reset();
  for (auto &point : points_) {
    if (point.x < left) {
      edgeFlags_.set(kLeftEdge_);
    } else if (point.x > right) {
      edgeFlags_.set(kRightEdge_);
    }

    if (point.y < top) {
      edgeFlags_.set(kTopEdge_);
    } else if (point.y > bottom) {
      edgeFlags_.set(kBottomEdge_);
    }
  }
}

// assumes object is a simple closed polygon
void GameObject::drawObject(Renderer *const renderer) const {
  for (int i = 0; i < points_.size(); i++) {
    if (i == points_.size() - 1) {
      renderer->drawLine(points_[i], points_[0], colorRGBA());
    } else {
      renderer->drawLine(points_[i], points_[i + 1], colorRGBA());
    }
  }
}

// assumes object is a simple closed polygon
void GameObject::drawGhostLines(Renderer *const renderer,
                                sGFlags const &gflags) const {
  SDL_Point p1{0, 0};
  SDL_Point p2{0, 0};
  int next;
  for (int i = 0; i < points_.size(); i++) {
    if (i == points_.size() - 1) {
      next = 0;
    } else {
      next = i + 1;
    }
    p1.x = points_[i].x + gflags.s1x * static_cast<int>(grid_width_);
    p1.y = points_[i].y + gflags.s1y * static_cast<int>(grid_height_);
    p2.x = points_[next].x + gflags.s2x * static_cast<int>(grid_width_);
    p2.y = points_[next].y + gflags.s2y * static_cast<int>(grid_height_);
    renderer->drawLine(p1, p2, colorRGBA());
  }
}

// assumes object is a simple closed polygon
void GameObject::drawGhost(Renderer *const renderer) const {
  // handle corners
  if (edgeFlags_.test(kLeftEdge_) && edgeFlags_.test(kTopEdge_)) {
    // draw ghost at bottom, right corner
    drawGhostLines(renderer, {1, 1, 1, 1});
  } else if (edgeFlags_.test(kTopEdge_) && edgeFlags_.test(kRightEdge_)) {
    // draw ghost at bottom, left corner
    drawGhostLines(renderer, {-1, 1, -1, 1});
  } else if (edgeFlags_.test(kRightEdge_) && edgeFlags_.test(kBottomEdge_)) {
    // draw ghost at top, left corner
    drawGhostLines(renderer, {-1, -1, -1, -1});
  } else if (edgeFlags_.test(kBottomEdge_) && edgeFlags_.test(kLeftEdge_)) {
    // draw ghost at top, right corner
    drawGhostLines(renderer, {1, -1, 1, -1});
  }

  // handle edges
  if (edgeFlags_.test(kLeftEdge_)) {
    // draw ghost at right edge
    drawGhostLines(renderer, {1, 0, 1, 0});
  } else if (edgeFlags_.test(kRightEdge_)) {
    // draw ghost at left edge
    drawGhostLines(renderer, {-1, 0, -1, 0});
  }
  if (edgeFlags_.test(kTopEdge_)) {
    // draw ghost at bottom edge
    drawGhostLines(renderer, {0, 1, 0, 1});
  } else if (edgeFlags_.test(kBottomEdge_)) {
    // draw ghost at top edge
    drawGhostLines(renderer, {0, -1, 0, -1});
  }
}