#include "UFO.h"

UFO::UFO(const std::size_t grid_width, const std::size_t grid_height,
         float game_scale)
    : GameObject(grid_width, grid_height, game_scale) {}
UFO::~UFO() {}