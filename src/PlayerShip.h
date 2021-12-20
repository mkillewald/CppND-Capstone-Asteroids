#ifndef PLAYERSHIP_H
#define PLAYERSHIP_H

#include "GameObject.h"

#include <cstddef>
#include <cstdint>

// forward declaration to avoid include cycle
class Renderer;

class PlayerShip : public GameObject {
public:
  // constructor / destructor
  PlayerShip(const std::size_t grid_width, const std::size_t grid_height,
             float game_scale);

  // getters / setters
  int maxShots() const;
  void setThrust(bool thrust);

  // typical behaviour methods
  void update();
  SDL_Point nose();
  void reset();
  void drawLife(Renderer *const renderer, int const &x, int const &y,
                SDL_Color const &color) const;

private:
  std::vector<SDL_Point> lifePoints_;
  bool thrust_{false};
  bool drawThrust_{false};
  int maxShots_{4};
  uint32_t thrustTicks_;
  uint32_t thrustTickLimit_{90};

  void init();
  void updatePosition();
  void drawObject(Renderer *const renderer) const;
  void drawGhostLines(Renderer *const renderer, sGFlags const &gFlags) const;
};

#endif