#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL.h>

#include <vector>

#define PI 3.14159265

// forward declaration to avoid include cycle
class Renderer;

struct sLine {
  SDL_Point &p1;
  SDL_Point &p2;
};

struct sColorRGBA {
  int r;
  int g;
  int b;
  int a;
};

struct sVector2f {
  float x;
  float y;
};

enum eRotate { left_, right_, none_ };

class GameObject {
public:
  // constructor / destructor
  GameObject();
  ~GameObject();

  // getters / setters
  unsigned int ID() const;
  void setColorRGBA(int r, int g, int b, int a);

  // typical behaviour methods
  void updatePosition();
  void rotateAndMovePoints();
  void update();
  void draw(Renderer *const renderer) const;

protected:
  std::vector<SDL_Point> points_;
  std::vector<sLine> lines_;
  sVector2f position_;
  sVector2f acceleration_;
  sVector2f velocity_;
  float maxVelocity_;
  float angle_;
  eRotate rot_ = none_;
  sColorRGBA color_;

  void setAtOrigin(std::vector<SDL_Point> atOrigin);

private:
  std::vector<SDL_Point> atOrigin_;
  unsigned int id_;
  unsigned int score_;
};

#endif