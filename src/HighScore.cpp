#include "HighScore.h"
#include "Game.h"

#include <algorithm>
#include <cstdint>
#include <fstream>
#include <sstream>
#include <string>

// TODO: save most recent p1 and p2 score

HighScore::HighScore(Game *const game) : game_(game) {
  readScores();
  initTag();
}

void HighScore::setP1High(bool isHigh) { p1High_ = isHigh; }
void HighScore::setP2High(bool isHigh) { p2High_ = isHigh; }

std::string HighScore::tag() const { return tag_; }

void HighScore::setTag() {
  tag_.replace(tagIndex_, 1, kChars_.substr(charIndex_, 1));
}

std::string HighScore::topScore() const { return table_[0].score_; }

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
    while (std::getline(filestream, line) && slot < kMaxSlots_) {
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

void HighScore::writeScores() {
  std::ofstream filestream(kHSPath_, std::ofstream::trunc);
  if (filestream.is_open()) {
    for (auto &entry : table_) {
      filestream << entry.score_ << " " << entry.tag_ << "\n";
    }
    filestream.close();
  }
}

bool HighScore::scoreIsHigh(std::uint32_t score) {
  if (score <= 0) {
    return false;
  } else if (table_.size() < kMaxSlots_) {
    return true;
  } else if (score > stoul(table_.back().score_)) {
    return true;
  } else {
    return false;
  }
}

void HighScore::addEntryToTable(sEntry newEntry) {
  if (table_.size() > 0 &&
      (table_[0].score_ == "00" || table_.size() == kMaxSlots_)) {
    table_.pop_back();
  }

  table_.emplace_back(newEntry);

  if (table_.size() > 1) {
    std::sort(table_.begin(), table_.end(), [](sEntry &a, sEntry &b) {
      return stoul(a.score_) > stoul(b.score_);
    });
  }
}

void HighScore::saveEntry() {
  // TODO: if 2 player game and both players get high scores, add checks to see
  // if either player's score would negate the other players high score entry.
  // If so, do not give that player a chance to enter score, since it would
  // immediately be wiped out anyway.
  addEntryToTable(
      sEntry{std::to_string(game_->currentPlayer()->score()), tag()});
  writeScores();
  game_->hud()->updateTableWidth();
  if (game_->numPlayers() == 2 && game_->currentPlayer() == game_->player1() &&
      p2High_) {
    game_->setCurrentPlayer(game_->player2());
  } else {
    game_->setState(Game::kAttract_);
  }
}

void HighScore::charUp() {
  if (charIndex_ == kChars_.size() - 1) {
    charIndex_ = 0;
  } else {
    charIndex_++;
  }
  setTag();
}

void HighScore::charDown() {
  if (charIndex_ == 0) {
    charIndex_ = kChars_.size() - 1;
  } else {
    charIndex_--;
  }
  setTag();
}

void HighScore::charSelect() {
  if (tagIndex_ == 2) {
    setTag();
    saveEntry();
    initTag();
  } else {
    charIndex_ = 0;
    tagIndex_++;
    setTag();
  }
}