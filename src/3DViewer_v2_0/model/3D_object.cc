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

void Object::RotateX(double angle) {
  for (size_t i = 0; i < vertices_.size(); i += 3) {
    double temp_y = vertices_[i + 1 % 3];
    double temp_z = vertices_[i + 2 % 3];
    vertices_[i + (0 + 1) % 3] = cos(angle) * temp_y + sin(angle) * temp_z;
    vertices_[i + (0 + 2) % 3] = sin(angle) * -temp_y + cos(angle) * temp_z;
  }
}

void Object::RotateY(double angle) {
  for (size_t i = 0; i < vertices_.size(); i += 3) {
    double temp_x = vertices_[i + 0 % 3];
    double temp_z = vertices_[i + 2 % 3];
    vertices_[i + (0 + 0) % 3] = cos(angle) * temp_x + sin(angle) * temp_z;
    vertices_[i + (0 + 2) % 3] = sin(angle) * -temp_x + cos(angle) * temp_z;
  }
}

void Object::RotateZ(double angle) {
  for (size_t i = 0; i < vertices_.size(); i += 3) {
    double temp_x = vertices_[i + 0 % 3];
    double temp_y = vertices_[i + 1 % 3];
    vertices_[i + (0 + 0) % 3] = cos(angle) * temp_x + sin(angle) * temp_y;
    vertices_[i + (0 + 1) % 3] = cos(angle) * temp_y - sin(angle) * temp_x;
  }
}

void Object::Scale(double x) {
  if (x != 0)
    for (size_t i = 0; i < vertices_.size(); ++i) vertices_[i] *= x;
}

}  // namespace s21
