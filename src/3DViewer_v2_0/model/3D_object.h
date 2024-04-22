#ifndef VIEWER_V2_MODEL_3D_OBJECT_H_
#define VIEWER_V2_MODEL_3D_OBJECT_H_

#include <cstddef>
#include <vector>

namespace s21 {

enum Axis { X, Y, Z };

class Object {
 public:
  Object() = default;
  Object(std::vector<double> &v, std::vector<int> &f);
  ~Object() = default;

  /// @brief аксессор к вектору вершин
  const std::vector<double> &Vertices() const;
  /// @brief аксессор к вектору полигонов
  const std::vector<int> &FaceIndices() const;
  size_t VertexCount() const;
  size_t FaceIndCount() const;

  /// @brief функция параллельного переноса
  /// @param x величина сдвига
  /// @param axis ось сдвига
  void Translate(double x, Axis axis);
  /// @brief функция поворота
  /// @param x угол поворота
  /// @param axis ось, вокруг которой производится поворот
  void Rotate(double x, Axis axis);
  /// @brief функция масштабирования
  /// @param x коэффициент масштабирования
  void Scale(double x);

 private:
  std::vector<double> vertices_{};
  std::vector<int> face_indices_{};
};

}  // namespace s21

#endif  // VIEWER_V2_MODEL_3D_OBJECT_H_
