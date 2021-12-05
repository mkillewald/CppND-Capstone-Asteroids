#ifndef PLAYERSHIP_H
#define PLAYERSHIP_H

#include "GameObject.h"

#include <cstddef>

// forward declaration to avoid include cycle
class Renderer;

class PlayerShip : public GameObject {
public:
  // constructor / destructor
  PlayerShip(const std::size_t grid_width, const std::size_t grid_height,
             float game_scale);
  ~PlayerShip();

  // getters / setters
  void setThrust(bool thrust);

  // typical behaviour methods
  void update();
  void draw(Renderer *const renderer) const;

private:
  void init();
  void updatePosition();
  void drawObject(Renderer *const renderer) const;
  void drawGhostLines(Renderer *const renderer, sGFlags const &gFlags) const;
  void drawGhost(Renderer *const renderer) const;

  bool thrust_ = false;
  std::vector<SDL_Point *> thrustLines_;
};

#endif