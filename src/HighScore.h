#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <cstddef>
#include <string>
#include <vector>

struct sEntry {
  std::string score_;
  std::string tag_;
};

// forward declaration to avoid include cycle
class Game;

class HighScore {
public:
  // constructor / destructor
  HighScore(Game *const game);
  //   ~HighScore();

  // getters / setters
  std::string tag() const;
  void setTag();
  std::string topScore() const;
  std::string tableSlots() const;
  std::string tableScores() const;
  std::string tableTags() const;

  // behavior methods
  void initTag();
  void readScores();
  bool scoreIsHigh(uint32_t score);
  void addEntry(sEntry newEntry);
  void saveScores();
  void charUp();
  void charDown();
  void charSelect();

private:
  const std::string kHSPath_{"Asteroids.hiscore"};
  const std::string kChars_{"ABCDEFGHIJKLMNOPQRSTUVWXYZ_"};
  const int kMaxSlots_{10};

  Game *const game_ = nullptr;

  int charIndex_{0};
  int tagIndex_{0};
  uint32_t scoreIn_;
  std::string tag_{"A__"};
  std::vector<sEntry> table_;

  void setScoreIn(uint32_t score);
};

#endif