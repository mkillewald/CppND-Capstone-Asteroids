#include "HighScore.h"

#include <fstream>
#include <sstream>
#include <string>

// TODO: update talbe and high score

HighScore::HighScore() {
  readScores();
  initTag();
}

std::string HighScore::tag() const { return tag_; }

void HighScore::setTag() {
  tag_.replace(tagIndex_, 1, chars_.substr(charIndex_, 1));
}

std::string HighScore::highScore() const { return table_[0].score_; }

std::string HighScore::tableSlots() const {
  if (table_[0].score_ == "00") {
    return "";
  } else {
    std::string line;
    for (int i = 1; i <= table_.size(); i++) {
      line += std::to_string(i) + ".\n";
    }
    return line;
  }
}

std::string HighScore::tableScores() const {
  if (table_[0].score_ == "00") {
    return "";
  } else {
    std::string line;
    for (auto &entry : table_) {
      line += entry.score_ + "\n";
    }
    return line;
  }
}

std::string HighScore::tableTags() const {
  if (table_[0].score_ == "00") {
    return "";
  } else {
    std::string line;
    for (auto &entry : table_) {
      line += entry.tag_ + "\n";
    }
    return line;
  }
}

void HighScore::initTag() {
  charIndex_ = 0;
  tagIndex_ = 0;
  tag_ = "A__";
}

void HighScore::readScores() {
  std::ifstream filestream(kHSPath_);
  if (filestream.is_open()) {
    int slot = 0;
    std::string line, score, tag;
    while (std::getline(filestream, line) && slot < maxSlots_) {
      std::istringstream linestream(line);
      linestream >> score >> tag;
      table_.emplace_back(sEntry{score, tag});
    }
    filestream.close();
  } else {
    // file could not be opened or does not exist
    table_.emplace_back(sEntry{"00", ""});
  }
}

void HighScore::saveScores() {
  std::ofstream filestream(kHSPath_, std::ofstream::trunc);
  if (filestream.is_open()) {
    for (auto &entry : table_) {
      filestream << entry.score_ << " " << entry.tag_ << "\n";
    }
    filestream.close();
  }
}

void HighScore::charUp() {
  if (charIndex_ == chars_.size() - 1) {
    charIndex_ = 0;
  } else {
    charIndex_++;
  }
  setTag();
}

void HighScore::charDown() {
  if (charIndex_ == 0) {
    charIndex_ = chars_.size() - 1;
  } else {
    charIndex_--;
  }
  setTag();
}

void HighScore::charSelect() {
  if (tagIndex_ == 2) {
    // TODO: save entry
  } else {
    charIndex_ = 0;
    tagIndex_++;
  }
  setTag();
}