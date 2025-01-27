#ifndef PLAYERSHOT_H
#define PLAYERSHOT_H

#include "GameObject.h"

#include <cstddef>
#include <cstdint>

class PlayerShot : public GameObject {
public:
  PlayerShot(const std::size_t grid_width, const std::size_t grid_height,
             float game_scale);

  // getters / setters
  bool isFired() const;
  void setIsFired(bool isFired);

  // behavior methods
  void update();
  void fire(SDL_Point point_in, sVector2f velocity_in, float angle_in);
  void draw(Renderer *const renderer) const;

private:
  bool isFired_{false};
  std::uint32_t startTicks_;
  std::uint32_t tickLimit_{600};

  void updatePosition();
  void drawObject(Renderer *const renderer) const;
};

#endif