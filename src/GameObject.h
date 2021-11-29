#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Renderer.h"

#include <memory>
#include <vector>

struct position {
  int x;
  int y;
  int dx;
  int dy;
};

class GameObject {
public:
  // constructor / destructor
  GameObject();
  ~GameObject();

  // getters / setters
  unsigned int ID() const;

  // typical behaviour methods
  void update();
  void draw(color &color);
  void drawLine(line &line, color &color);

private:
  unsigned int id_;
  unsigned int points_;
  float angle_;
  position pos_;
  std::vector<line> lines_;
  std::shared_ptr<Renderer> renderer_;
};

#endif