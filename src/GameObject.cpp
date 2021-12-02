#include "GameObject.h"
#include "Game.h"
#include "Renderer.h"

#include <SDL.h>

#include <bitset>

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

void GameObject::update() {
  updatePosition();
  rotateMoveAndScalePoints();
  checkPointsAtEdges(0, static_cast<int>(grid_width_), 0,
                     static_cast<int>(grid_height_));
}

void GameObject::draw(Renderer *const renderer) const {
  // draw object at position
  drawObject(renderer, lines_);

  // if any edgeFlags_ are set, draw object's "ghost"
  drawGhost(renderer, lines_);
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

void GameObject::checkPointsAtEdges(int left, int right, int top, int bottom) {
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

void GameObject::drawObject(Renderer *const renderer,
                            std::vector<sLine> const &lines) const {
  for (auto &line : lines) {
    renderer->drawLine(line, color_);
  }
}

void GameObject::drawGhostLines(Renderer *const renderer,
                                std::vector<sLine> const &lines,
                                sGFlags const &gflags) const {
  SDL_Point p1{0, 0};
  SDL_Point p2{0, 0};
  sLine ghostLine{p1, p2};
  for (auto &line : lines) {
    p1.x = line.p1.x + gflags.s1x * static_cast<int>(grid_width_);
    p1.y = line.p1.y + gflags.s1y * static_cast<int>(grid_height_);
    p2.x = line.p2.x + gflags.s2x * static_cast<int>(grid_width_);
    p2.y = line.p2.y + gflags.s2y * static_cast<int>(grid_height_);
    renderer->drawLine(ghostLine, color_);
  }
}

void GameObject::drawGhost(Renderer *const renderer,
                           std::vector<sLine> const &lines) const {
  // handle corners
  if (edgeFlags_.test(kLeftEdge_) && edgeFlags_.test(kTopEdge_)) {
    // draw ghost at bottom, right corner
    drawGhostLines(renderer, lines, {1, 1, 1, 1});
  } else if (edgeFlags_.test(kTopEdge_) && edgeFlags_.test(kRightEdge_)) {
    // draw ghost at bottom, left corner
    drawGhostLines(renderer, lines, {-1, 1, -1, 1});
  } else if (edgeFlags_.test(kRightEdge_) && edgeFlags_.test(kBottomEdge_)) {
    // draw ghost at top, left corner
    drawGhostLines(renderer, lines, {-1, -1, -1, -1});
  } else if (edgeFlags_.test(kBottomEdge_) && edgeFlags_.test(kLeftEdge_)) {
    // draw ghost at top, right corner
    drawGhostLines(renderer, lines, {1, -1, 1, -1});
  }

  // handle edges
  if (edgeFlags_.test(kLeftEdge_)) {
    // draw ghost at right edge
    drawGhostLines(renderer, lines, {1, 0, 1, 0});
  } else if (edgeFlags_.test(kRightEdge_)) {
    // draw ghost at left edge
    drawGhostLines(renderer, lines, {-1, 0, -1, 0});
  }
  if (edgeFlags_.test(kTopEdge_)) {
    // draw ghost at bottom edge
    drawGhostLines(renderer, lines, {0, 1, 0, 1});
  } else if (edgeFlags_.test(kBottomEdge_)) {
    // draw ghost at top edge
    drawGhostLines(renderer, lines, {0, -1, 0, -1});
  }
}