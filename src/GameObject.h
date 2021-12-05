#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL.h>

#include <bitset>
#include <vector>

#define PI 3.14159265

// forward declaration to avoid include cycle
class Renderer;

struct sGFlags {
  int s1x;
  int s1y;
  int s2x;
  int s2y;
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

class GameObject {
public:
  enum eRotate { kRotLeft_, kRotRight_, kRotNone_ };
  enum eEdge { kLeftEdge_, kRightEdge_, kTopEdge_, kBottomEdge_ };

  // constructor / destructor
  GameObject(const std::size_t grid_width, const std::size_t grid_height,
             float game_scale);
  ~GameObject();

  // getters / setters
  unsigned int ID() const;
  eRotate getRot() const;
  void setRot(eRotate rot);
  void setColorRGBA(int r, int g, int b, int a);

  // typical behaviour methods
  void update();
  void draw(Renderer *const renderer) const;

protected:
  const std::size_t grid_width_;
  const std::size_t grid_height_;
  float game_scale_;
  std::vector<SDL_Point> points_;
  std::bitset<4> edgeFlags_{0x0000};
  sVector2f position_;
  sVector2f acceleration_;
  sVector2f velocity_;
  float maxVelocity_;
  float angle_;
  float scale_;
  sColorRGBA color_;

  // getters / setters
  void setAtOrigin(std::vector<SDL_Point> atOrigin);

  // typical behaviour methods
  void updatePosition();
  void rotateMoveAndScalePoints();
  void wrapCoordinates(sVector2f &point);
  void checkPointsAtEdges(int const &left, int const &right, int const &top,
                          int const &bottom);
  void drawObject(Renderer *const renderer) const;
  void drawGhostLines(Renderer *const renderer, sGFlags const &gflags) const;
  void drawGhost(Renderer *const renderer) const;

private:
  std::vector<SDL_Point> atOrigin_;
  eRotate rot_ = kRotNone_;
  // const unsigned int id_;
  // cosnt unsigned int score_;
};

#endif