#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL.h>

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

class GameObject {
public:
  // constructor / destructor
  GameObject();
  ~GameObject();

  // getters / setters
  unsigned int ID() const;
  void setColor(int r, int g, int b, int a);

  // typical behaviour methods
  void update();
  void draw(Renderer *const renderer) const;

protected:
  std::vector<line> lines_;
  SDL_Point pos_;
  SDL_Point vel_;
  float angle_;
  color color_;

private:
  unsigned int id_;
  unsigned int score_;
};

#endif