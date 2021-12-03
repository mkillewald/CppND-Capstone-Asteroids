#ifndef UFO_H
#define UFO_H

#include "GameObject.h"

// forward declaration to avoid include cycle
class Renderer;

class UFO : public GameObject {
public:
  enum eUFOSize {

    // internal Atari Coin-Op nicknames of Saucer sizes "Sluggo" and "Mr. Bill"
    // https://sudonull.com/post/8376-How-to-create-a-vector-arcade-machine-Atari-Asteroids

    kSluggo_, // large (dumb)
    kMrBill_  // small (smart)
  };

  // constructor / destructor
  UFO(const std::size_t grid_width, const std::size_t grid_height,
      float game_scale, eUFOSize size);
  ~UFO();

  // getters / setters

  // typical behaviour methods
  void draw(Renderer *const renderer) const;

private:
  eUFOSize size_ = kSluggo_;

  void init();
  void drawObject(Renderer *const renderer) const;
  void drawGhostLines(Renderer *const renderer, sGFlags const &gFlags) const;
  void drawGhost(Renderer *const renderer) const;
};

#endif