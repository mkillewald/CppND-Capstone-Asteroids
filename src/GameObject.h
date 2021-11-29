#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL.h>

#include <vector>

// forward declaration to avoid include cycle
class Renderer;

struct sLine {
  int x1;
  int y1;
  int x2;
  int y2;
};

struct sColor {
  int r;
  int g;
  int b;
  int a;
};

enum eRotate { left_, right_, none_ };

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
  std::vector<sLine> lines_;
  SDL_Point pos_;
  SDL_Point vel_;
  float angle_;
  eRotate rot_ = none_;
  sColor color_;

private:
  unsigned int id_;
  unsigned int score_;
};

#endif