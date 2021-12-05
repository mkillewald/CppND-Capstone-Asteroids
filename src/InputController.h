#ifndef INPUTCONTROLLER_H
#define INPUTCONTROLLER_H

// forward declaration to avoid include cycle
class PlayerController;

// class based off Snake Game example code:
// https://github.com/udacity/CppND-Capstone-Snake-Game

class InputController {
public:
  void handleInput(bool &running, PlayerController *player) const;

private:
};

#endif