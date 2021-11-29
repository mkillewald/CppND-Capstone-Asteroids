#include "GameObject.h"
#include "Game.h"
#include "Renderer.h"

#include <SDL.h>

// constructor / destructor
GameObject::GameObject() {}
GameObject::~GameObject() {}

// getters / setters
unsigned int GameObject::ID() const { return id_; }

// typical behaviour methods
void GameObject::update() {}

void GameObject::draw(Renderer *const renderer, color &color) const {
  for (auto &line : lines_) {
    renderer->drawLine(line, color);
  }
}