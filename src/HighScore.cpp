#include "HighScore.h"

#include <string>

// TODO: read table and high score from file
// TODO: update talbe and high score
// TODO: write table and high score to file

HighScore::HighScore() { initInitials(); }

std::string HighScore::initials() const { return initials_; }

void HighScore::setInitials() {
  initials_.replace(initialIndex_, 1, chars_.substr(charIndex_, 1));
}

// TODO: finish this
std::string HighScore::tableSlots() {
  return "1.\n2.\n3.\n4.\n5.\n6.\n7.\n8.\n9.\n10.";
}

// TODO: finish this
std::string HighScore::tableScores() {
  return "39020\n15110\n3480\n2810\n1460\n1060\n680\n360\n240\n90";
}

// TODO: finish this
std::string HighScore::tableInitials() {
  return "KEX\nA\nAAA\nAAA\nAAA\nA\nA\nA\nDAA\nA";
}

void HighScore::initInitials() {
  charIndex_ = 0;
  initialIndex_ = 0;
  initials_ = "A__";
}

void HighScore::charUp() {
  if (charIndex_ == chars_.size() - 1) {
    charIndex_ = 0;
  } else {
    charIndex_++;
  }
  setInitials();
}

void HighScore::charDown() {
  if (charIndex_ == 0) {
    charIndex_ = chars_.size() - 1;
  } else {
    charIndex_--;
  }
  setInitials();
}

void HighScore::charSelect() {
  if (initialIndex_ == 2) {
    // TODO: save entry
  } else {
    charIndex_ = 0;
    initialIndex_++;
  }
  setInitials();
}