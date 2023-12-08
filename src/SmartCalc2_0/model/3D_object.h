#ifndef VIEWER_V2_MODEL_3D_OBJECT_H_
#define VIEWER_V2_MODEL_3D_OBJECT_H_

#include <cstddef>
#include <vector>

namespace s21 {

enum Axis { X, Y, Z };

class Object {
 public:
  Object(std::vector<double> &v, std::vector<int> &f) ;
  ~Object() = default;

  const std::vector<double> &Vertices() const ;
  const std::vector<int> &FaceIndices() const ;
  size_t VertexCount() const ;
  size_t FaceIndCount() const ;

  void Translate(double x, Axis axis) ;
  void Rotate(double x, Axis axis) ;
  void Scale(double x) ;

 private:
  std::vector<double> vertices_{};
  std::vector<int> face_indices_{};
};

}  // namespace s21

#endif  // VIEWER_V2_MODEL_3D_OBJECT_H_
