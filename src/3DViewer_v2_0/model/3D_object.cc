#include "3D_object.h"

#include <cmath>
#include <cstddef>
#include <vector>

namespace s21 {

Object::Object(std::vector<double> &v, std::vector<int> &f) {
  v.swap(vertices_);
  f.swap(face_indices_);
}

const std::vector<double> &Object::Vertices() const { return vertices_; }
const std::vector<int> &Object::FaceIndices() const { return face_indices_; }

size_t Object::VertexCount() const { return vertices_.size(); }
size_t Object::FaceIndCount() const { return face_indices_.size(); }

void Object::Translate(double x, Axis axis) {
  for (size_t i = 0 + axis; i < vertices_.size(); i += 3) vertices_[i] += x;
}

void Object::Rotate(double x, Axis axis) {
  for (size_t i = 0; i < vertices_.size(); i += 3) {
    double y = vertices_[i + (axis + 1) % 3];
    double z = vertices_[i + (axis + 2) % 3];
    vertices_[i + (axis + 1) % 3] = cos(x) * y - sin(x) * z;
    vertices_[i + (axis + 2) % 3] = cos(x) * y + sin(x) * z;
  }
}

void Object::Scale(double x) {
  if (x != 0)
    for (size_t i = 0; i < vertices_.size(); ++i) vertices_[i] *= x;
}

}  // namespace s21
