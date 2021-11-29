#include "GameObject.h"
#include "Game.h"

#include <SDL.h>

// constructor / destructor
GameObject::GameObject() {}
GameObject::~GameObject() {}

// getters / setters
unsigned int GameObject::ID() const { return id_; }

// typical behaviour methods
void GameObject::update() {}

void GameObject::draw(color &color) {
  for (auto &line : lines_) {
    renderer_->drawLine(line, color);
  }
}