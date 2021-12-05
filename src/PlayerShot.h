#ifndef PLAYERSHOT_H
#define PLAYERSHOT_H

#include "GameObject.h"

class PlayerShot : public GameObject {
public:
  PlayerShot(const std::size_t grid_width, const std::size_t grid_height,
             float game_scale);

private:
  bool isFired{false};
};

#endif