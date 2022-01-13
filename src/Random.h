#ifndef RANDOM_H
#define RANDUM_H

#include <random>

class Random {
public:
  static int randomInt(int min, int max);
  static float randomFloat(float min, float max);
  static int randomSign();

private:
  static std::random_device rd_;
  static std::mt19937 engine_;
};

#endif