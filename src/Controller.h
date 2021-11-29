#ifndef CONTROLLER_H
#define CONTROLLER_H

// forward declaration to avoid include cycle
class PlayerShip;

class Controller {
public:
  void handleInput(bool &running, PlayerShip &player) const;

private:
};

#endif