#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <cstdint>
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
  void setP1High(bool high);
  void setP2High(bool high);
  std::string tag() const;
  void setTag();
  std::uint32_t topScore() const;
  void setTopScore(std::uint32_t score);
  std::string tableSlots() const;
  std::string tableScores() const;
  std::string tableTags() const;

  // behavior methods
  void initTag();
  void readScores();
  void writeScores();
  bool scoreIsHigh(std::uint32_t score);
  void addEntryToTable(sEntry newEntry);
  void saveEntry();
  void charUp();
  void charDown();
  void charSelect();

private:
  const std::string kHSPath_{"Asteroids.hiscore"};
  const std::string kChars_{"ABCDEFGHIJKLMNOPQRSTUVWXYZ_"};
  const int kMaxSlots_{10};

  Game *const game_ = nullptr;

  bool p1High_{false};
  bool p2High_{false};
  int charIndex_{0};
  int tagIndex_{0};
  std::string tag_{"A__"};
  std::vector<sEntry> table_;
  std::uint32_t topScore_;

  void updateTopScore();
};

#endif