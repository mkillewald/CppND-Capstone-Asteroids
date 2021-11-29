#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>

// forward declaration to avoid include cycle
class Renderer;

struct line {
  int x1;
  int y1;
  int x2;
  int y2;
};

struct color {
  int r;
  int g;
  int b;
  int a;
};

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
  void init();
  void update();
  void draw(Renderer *const renderer, color &color) const;

protected:
  std::vector<line> lines_;

private:
  unsigned int id_;
  unsigned int score_;
  float angle_;
  position pos_;
};

#endif