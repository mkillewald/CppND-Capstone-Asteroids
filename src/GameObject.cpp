#include "GameObject.h"
#include "Game.h"
#include "Renderer.h"

#include <SDL.h>

#include <bitset>
#include <cstddef>

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

SDL_Color GameObject::colorRGBA() const { return colorRGBA_; }
void GameObject::setColorRGBA(int r, int g, int b, int a) {
  colorRGBA_.r = r;
  colorRGBA_.g = g;
  colorRGBA_.b = b;
  colorRGBA_.a = a;
}

// unsigned int GameObject::ID() const { return id_; }
GameObject::eRotDir GameObject::rotDir() const { return rotDir_; }
void GameObject::setRotDir(eRotDir rotDir) { rotDir_ = rotDir; }

sVector2f const &GameObject::position() const { return position_; } // public
sVector2f &GameObject::position() { return position_; }             // protected
void GameObject::setPosition(sVector2f position) { position_ = position; }

sVector2f &GameObject::velocity() { return velocity_; }
sVector2f GameObject::getVelocity() const { return velocity_; }
void GameObject::setVelocity(sVector2f velocity) { velocity_ = velocity; }

void GameObject::incVelocity(sVector2f velocity) {
  velocity_.x *= velocity.x;
  velocity_.y *= velocity.y;
}

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

int GameObject::radius() const { return radius_; }
void GameObject::setRadius(float radius) { radius_ = radius; }

bool GameObject::destroyed() const { return destroyed_; }
void GameObject::setDestroyed(bool destroyed) { destroyed_ = destroyed; }

// typical behaviour methods
void GameObject::update() {
  updatePosition();
  rotateMoveAndScalePoints(points_, position_, angle_, scale_);
  checkPointsAtEdges(0, static_cast<int>(grid_width_), 0,
                     static_cast<int>(grid_height_));
}

bool GameObject::collide(GameObject const &b) const {
  return collideObject(b) || collideGhost(b);
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

void GameObject::rotateMoveAndScalePoints(std::vector<SDL_Point> &points,
                                          sVector2f const &position,
                                          float const &angle,
                                          float const &scale) {
  float cosRot = cos(angle * PI / 180.0);
  float sinRot = sin(angle * PI / 180.0);
  for (int i = 0; i < points.size(); i++) {
    // apply rotatation to points atOrigin_ and save result in points_
    points[i].x =
        scale * (atOrigin_[i].x * cosRot - atOrigin_[i].y * sinRot) + 0.5;
    points[i].y =
        scale * (atOrigin_[i].x * sinRot + atOrigin_[i].y * cosRot) + 0.5;

    // move points to objects position
    points[i].x += position.x;
    points[i].y += position.y;
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
int GameObject::distance(sVector2f const &p1, sVector2f const &p2) const {
  return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

bool GameObject::collideObject(GameObject const &b) const {
  if (distance(position(), b.position()) <= radius() + b.radius()) {
    return true;
  }
  return false;
}

bool GameObject::collideGhostSection(GameObject const &b,
                                     sGFlags const &gflags) const {
  if (distance({position().x + gflags.s1x * static_cast<float>(grid_width_),
                position().y + gflags.s1y * static_cast<float>(grid_height_)},
               b.position()) <= radius() + b.radius()) {
    return true;
  }
  return false;
}

bool GameObject::collideGhost(GameObject const &b) const {
  // handle corners
  if (edgeFlags_.test(kLeftEdge_) && edgeFlags_.test(kTopEdge_)) {
    // ghost at bottom, right corner
    if (collideGhostSection(b, {1, 1, 0, 0})) {
      return true;
    }
  } else if (edgeFlags_.test(kTopEdge_) && edgeFlags_.test(kRightEdge_)) {
    // ghost at bottom, left corner
    if (collideGhostSection(b, {-1, 1, 0, 0})) {
      return true;
    }
  } else if (edgeFlags_.test(kRightEdge_) && edgeFlags_.test(kBottomEdge_)) {
    // ghost at top, left corner
    if (collideGhostSection(b, {-1, -1, 0, 0})) {
      return true;
    }
  } else if (edgeFlags_.test(kBottomEdge_) && edgeFlags_.test(kLeftEdge_)) {
    // ghost at top, right corner
    if (collideGhostSection(b, {1, -1, 0, 0})) {
      return true;
    }
  }

  // handle edges
  if (edgeFlags_.test(kLeftEdge_)) {
    // ghost at right edge
    if (collideGhostSection(b, {1, 0, 0, 0})) {
      return true;
    }
  } else if (edgeFlags_.test(kRightEdge_)) {
    // ghost at left edge
    if (collideGhostSection(b, {-1, 0, 0, 0})) {
      return true;
    }
  }
  if (edgeFlags_.test(kTopEdge_)) {
    // ghost at bottom edge
    if (collideGhostSection(b, {0, 1, 0, 0})) {
      return true;
    }
  } else if (edgeFlags_.test(kBottomEdge_)) {
    // ghost at top edge
    if (collideGhostSection(b, {0, -1, 0, 0})) {
      return true;
    }
  }
  return false;
}
