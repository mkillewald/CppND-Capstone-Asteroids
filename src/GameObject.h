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

  sVector2f operator+(sVector2f const &a);
  sVector2f operator+(float const &a);
};

class GameObject {
public:
  enum eRotDir { kRotLeft_, kRotRight_, kRotNone_ };
  enum eEdge { kLeftEdge_, kRightEdge_, kTopEdge_, kBottomEdge_ };

  // constructor / destructor
  GameObject(const std::size_t grid_width, const std::size_t grid_height,
             float game_scale);

  // getters / setters
  unsigned int ID() const;
  void setRotDir(eRotDir rot);
  sVector2f getVelocity() const;
  float angle() const;

  // typical behaviour methods
  void update();
  void draw(Renderer *const renderer) const;

  // TODO: should move this to private with public getters/setters ??
protected:
  std::vector<SDL_Point> points_;
  std::bitset<4> edgeFlags_{0x0000};

  // getters / setters
  void setAtOrigin(std::vector<SDL_Point> atOrigin);
  const std::size_t gridWidth() const;
  const std::size_t gridHeight() const;
  sColorRGBA colorRGBA() const;
  void setColorRGBA(int r, int g, int b, int a);
  eRotDir rotDir() const;
  sVector2f &position();
  void setPosition(sVector2f velocity);
  sVector2f &velocity();
  void setVelocity(sVector2f velocity);
  sVector2f &acceleration();
  void setAcceleration(sVector2f acceleration);
  float maxVelocity() const;
  void setMaxVelocity(float maxVelocity);
  float gameScale() const;
  float scale() const;
  void setScale(float scale);
  void setAngle(float angle);

  // typical behaviour methods
  void updatePosition();
  void rotateMoveAndScalePoints();
  void wrapCoordinates(sVector2f &point);
  void checkPointsAtEdges(int const &left, int const &right, int const &top,
                          int const &bottom);
  virtual void drawObject(Renderer *const renderer) const;
  virtual void drawGhostLines(Renderer *const renderer,
                              sGFlags const &gflags) const;
  virtual void drawGhost(Renderer *const renderer) const;

private:
  // const unsigned int id_;
  std::vector<SDL_Point> atOrigin_;
  const std::size_t grid_width_;
  const std::size_t grid_height_;
  sColorRGBA colorRGBA_;
  eRotDir rotDir_ = kRotNone_;
  sVector2f position_;
  sVector2f velocity_;
  sVector2f acceleration_;
  float maxVelocity_;
  float game_scale_;
  float scale_;
  float angle_;
  // cosnt unsigned int score_;
};

#endif