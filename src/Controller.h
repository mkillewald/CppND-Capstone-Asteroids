#ifndef CONTROLLER_H
#define CONTROLLER_H

// forward declaration to avoid include cycle
class PlayerShip;

// class based off Snake Game example code:
// https://github.com/udacity/CppND-Capstone-Snake-Game

class Controller {
public:
  void handleInput(bool &running, PlayerShip &player) const;

private:
};

#endif