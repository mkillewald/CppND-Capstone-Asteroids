#include "Random.h"

#include <random>

std::random_device Random::rd_;
std::mt19937 Random::engine_(rd_());

int Random::randomSign() { return Random::randomInt(0, 1) ? -1 : 1; }

int Random::randomInt(int min, int max) {
  std::uniform_int_distribution<int> dist(min, max);
  return dist(engine_);
}

float Random::randomFloat(float min, float max) {
  std::uniform_real_distribution<float> dist(min, max);
  return dist(engine_);
}