#include "parser.h"

#include <algorithm>
#include <cmath>
#include <fstream>
#include <limits>
#include <memory>
#include <string>
#include <vector>

namespace s21 {

std::unique_ptr<Object> Parser::Parse(const std::string &file_name) {
  std::ifstream file(file_name);
  if (!file) throw std::runtime_error("file does not exist");

  ClearData();
  std::string line;
  while (std::getline(file, line)) {
    if (line[0] == 'v' && line[1] == ' ')
      ParseVertice(line);
    else if (line[0] == 'f' && line[1] == ' ')
      ParseFace(line);
  }
  Normalize();
  auto obj = std::make_unique<Object>(v_, f_);
  return obj;
}

void Parser::ParseVertice(std::string &line) {
  for (size_t pos{2}, i{0}, j{0}; i < 3; ++i, pos += j) {
    double n = std::stod(line.substr(pos), &j);
    v_.push_back(n);
    UpdateMinMax(n, i);
  }
}

void Parser::ParseFace(std::string &line) {
  size_t pos{2};
  int first = std::stoi(line.substr(pos++)) - 1;
  f_.push_back(first);
  for (size_t size{line.size()}; pos < size; ++pos)
    if (std::isdigit(line[pos]) && std::isspace(line[pos - 1])) {
      int n = std::stoi(line.substr(pos)) - 1;
      f_.push_back(n);
      f_.push_back(n);
    }
  f_.push_back(first);
}

void Parser::ClearData() {
  v_.clear();
  f_.clear();
  min_[0] = min_[1] = min_[2] = std::numeric_limits<double>::max();
  max_[0] = max_[1] = max_[2] = std::numeric_limits<double>::lowest();
}

void Parser::UpdateMinMax(double n, size_t i) {
  if (n < min_[i]) min_[i] = n;
  if (n > max_[i]) max_[i] = n;
}

void Parser::Normalize() {
  std::array<double, 3> mid{};
  for (int i = 0; i < 3; ++i) mid[i] = (min_[i] + max_[i]) / 2;
  double coef =
      1 / std::max({std::fabs(min_[0] - max_[0]), std::fabs(min_[1] - max_[1]),
                    std::fabs(min_[2] - max_[2])});

  for (size_t i = 0; i < v_.size(); ++i) v_[i] = coef * (v_[i] - mid[i % 3]);
}

}  // namespace s21
