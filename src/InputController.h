#ifndef INPUTCONTROLLER_H
#define INPUTCONTROLLER_H

// forward declaration to avoid include cycle
class Game;
class HighScore;
class PlayerController;

class InputController {
public:
  void attract(Game *game) const;
  void ready(Game *game) const;
  void play(Game *game, PlayerController *player) const;
  void highScore(Game *game, HighScore *highScore) const;

private:
};

#endif