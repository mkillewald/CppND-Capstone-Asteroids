#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL.h>

#include <bitset>
#include <vector>

#define PI 3.14159265

// forward declaration to avoid include cycle
class Renderer;

struct sLine {
  SDL_Point &p1;
  SDL_Point &p2;
};

struct sFlags {
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

enum eRotate { kRotLeft_, kRotRight_, kRotNone_ };

enum eEdge { kLeftEdge_, kRightEdge_, kTopEdge_, kBottomEdge_ };

class GameObject {
public:
  // constructor / destructor
  GameObject(const std::size_t grid_width, const std::size_t grid_height);
  ~GameObject();

  // getters / setters
  unsigned int ID() const;
  void setColorRGBA(int r, int g, int b, int a);

  // typical behaviour methods
  void update();
  void draw(Renderer *const renderer) const;

protected:
  const std::size_t grid_width_;
  const std::size_t grid_height_;
  std::vector<SDL_Point> points_;
  std::vector<sLine> lines_;
  std::bitset<4> edgeFlags_{0x0000};
  sVector2f position_;
  sVector2f acceleration_;
  sVector2f velocity_;
  float maxVelocity_;
  float angle_;
  eRotate rot_ = kRotNone_;
  sColorRGBA color_;

  void setAtOrigin(std::vector<SDL_Point> atOrigin);
  void updatePosition();
  void rotateAndMovePoints();
  void wrapCoordinates(sVector2f &point);
  void checkPointsAtEdges(int left, int right, int top, int bottom);
  void drawObject(Renderer *const renderer,
                  std::vector<sLine> const &lines) const;
  void drawGhost(Renderer *const renderer,
                 std::vector<sLine> const &lines) const;

private:
  std::vector<SDL_Point> atOrigin_;
  unsigned int id_;
  unsigned int score_;

  void drawGhostLines(Renderer *const renderer, std::vector<sLine> const &lines,
                      const sFlags flags) const;
};

#endif