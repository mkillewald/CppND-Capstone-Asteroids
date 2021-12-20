#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <cstdint>
#include <string>
#include <vector>

struct sEntry {
  uint32_t score_;
  std::string tag_;
};

class HighScore {
public:
  // constructor / destructor
  HighScore();
  //   ~HighScore();

  // getters / setters
  std::string initials() const;
  void setInitials();
  std::string tableSlots();
  std::string tableScores();
  std::string tableInitials();

  // behavior methods
  void initInitials();
  void readScores();
  void updateScores();
  void saveScores();
  void charUp();
  void charDown();
  void charSelect();

private:
  const std::string chars_{"ABCDEFGHIJKLMNOPQRSTUVWXYZ_"};

  int charIndex_{0};
  int initialIndex_{0};
  int maxSlots_{10};
  uint32_t highScore_;
  std::string initials_{"A__"};
  std::vector<sEntry> table_;
};

#endif