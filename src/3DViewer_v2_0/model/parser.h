#ifndef VIEWER_V2_MODEL_PARSER_H_
#define VIEWER_V2_MODEL_PARSER_H_

#include <array>
#include <memory>
#include <string>
#include <vector>

#include "3D_object.h"

namespace s21 {

class Parser {
 public:
  Parser() = default;
  ~Parser() = default;

  /// @brief парсер obj файлов
  /// @param file_name путь до файла
  /// @return указатель на полученный в результате парсинга Object
  std::unique_ptr<Object> Parse(const std::string &file_name);

 private:
  std::vector<double> v_{};
  std::vector<int> f_{};
  std::array<double, 3> min_{};
  std::array<double, 3> max_{};

  void ParseVertice(std::string &line);
  void ParseFace(std::string &line);
  void ClearData();
  void UpdateMinMax(double n, size_t i);
  void Normalize();
};

}  // namespace s21

#endif  // VIEWER_V2_MODEL_PARSER_H_
