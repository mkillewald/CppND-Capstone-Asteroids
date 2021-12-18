#ifndef INPUTCONTROLLER_H
#define INPUTCONTROLLER_H

// forward declaration to avoid include cycle
class Game;
class HUD;
class PlayerController;

class InputController {
public:
  void attract(Game *game) const;
  void ready(Game *game) const;
  void play(Game *game, PlayerController *player) const;
  void highScore(Game *game, HUD *hud, PlayerController *player) const;

private:
};

#endif