#include "GameObject.h"
#include "Game.h"
#include "Renderer.h"

#include <SDL.h>

// constructor / destructor
GameObject::GameObject() {}
GameObject::~GameObject() {}

// getters / setters
unsigned int GameObject::ID() const { return id_; }
void GameObject::setColor(int r, int g, int b, int a) {
  color_.r = r;
  color_.g = g;
  color_.b = b;
  color_.a = a;
}

// typical behaviour methods
void GameObject::update() {}

void GameObject::draw(Renderer *const renderer) const {
  for (auto &line : lines_) {
    renderer->drawLine(line, pos_, color_);
  }
}