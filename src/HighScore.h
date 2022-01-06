#ifndef HIGHSCORE_H
#define HIGHSCORE_H
#include <string>
#include <vector>

struct sEntry {
  std::string score_;
  std::string tag_;
};

class HighScore {
public:
  // constructor / destructor
  HighScore();
  //   ~HighScore();

  // getters / setters
  std::string tag() const;
  void setTag();
  std::string highScore() const;
  std::string tableSlots() const;
  std::string tableScores() const;
  std::string tableTags() const;

  // behavior methods
  void initTag();
  void readScores();
  void updateScores();
  void saveScores();
  void charUp();
  void charDown();
  void charSelect();

private:
  const std::string kHSPath_{"Asteroids.hiscore"};
  const std::string chars_{"ABCDEFGHIJKLMNOPQRSTUVWXYZ_"};
  const int maxSlots_{10};

  int charIndex_{0};
  int tagIndex_{0};
  std::string tag_{"A__"};
  std::vector<sEntry> table_;
};

#endif