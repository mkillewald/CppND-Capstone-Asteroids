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

struct sVector2f {
  float x;
  float y;

  sVector2f operator+(sVector2f const &a); // not used
  sVector2f operator+(float const &a);     // not used
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
  sVector2f const &position() const;
  sVector2f getVelocity() const;
  float angle() const;
  int radius() const;
  bool destroyed() const;
  void setDestroyed(bool destroyed);

  // typical behaviour methods
  void update();
  bool collide(GameObject const &b) const;
  void draw(Renderer *const renderer) const;

  // TODO: should move this to private with public getters/setters ??
protected:
  std::vector<SDL_Point> points_;
  std::bitset<4> edgeFlags_{0x0000};

  // getters / setters
  void setAtOrigin(std::vector<SDL_Point> atOrigin);
  const std::size_t gridWidth() const;
  const std::size_t gridHeight() const;
  SDL_Color colorRGBA() const;
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
  void setRadius(float radius);

  // typical behaviour methods
  void updatePosition();
  void rotateMoveAndScalePoints(std::vector<SDL_Point> &points,
                                sVector2f const &position, float const &angle,
                                float const &scale);
  void wrapCoordinates(sVector2f &point);
  void checkPointsAtEdges(int const &left, int const &right, int const &top,
                          int const &bottom);
  virtual void drawObject(Renderer *const renderer) const;
  virtual void drawGhostLines(Renderer *const renderer,
                              sGFlags const &gflags) const;
  virtual void drawGhost(Renderer *const renderer) const;
  int distance(sVector2f const &p1, sVector2f const &p2) const;
  bool collideObject(GameObject const &b) const;
  bool collideGhostSection(GameObject const &b, sGFlags const &gflags) const;
  bool collideGhost(GameObject const &b) const;

private:
  // const unsigned int id_;
  const std::size_t grid_width_;
  const std::size_t grid_height_;

  std::vector<SDL_Point> atOrigin_;
  SDL_Color colorRGBA_;
  eRotDir rotDir_ = kRotNone_;
  sVector2f position_;
  sVector2f velocity_;
  sVector2f acceleration_;
  float maxVelocity_;
  float game_scale_;
  float scale_;
  float angle_;
  float radius_;
  bool destroyed_{false};
  // cosnt unsigned int score_;
};

#endif