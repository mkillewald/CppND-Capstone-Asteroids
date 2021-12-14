#ifndef INPUTCONTROLLER_H
#define INPUTCONTROLLER_H

// forward declaration to avoid include cycle
class Game;
class PlayerController;

class InputController {
public:
  void attract(bool &running, Game *game) const;
  void ready(bool &running, Game *game) const;
  void play(bool &running, PlayerController *player) const;
  void highScore(bool &running, PlayerController *player) const;

private:
};

#endif