#include "controller.h"

namespace s21 {
void Controller::LoadObject(std::string &file_name) {
  try {
    obj_ = parser_->Parse(file_name);
  } catch (std::exception) {
  }
}

size_t Controller::VertexCount() const { return obj_->VertexCount(); }
size_t Controller::FaceIndCount() const { return obj_->FaceIndCount(); }
const double *Controller::Vertices() const { return obj_->Vertices().data(); }
const int *Controller::FaceIndices() const {
  return obj_->FaceIndices().data();
}
bool Controller::Status() const { return obj_ == nullptr; }

void Controller::TranslateObject(double x, Axis a) { obj_->Translate(x, a); }
void Controller::RotateObject(double x, Axis a) { obj_->Rotate(x, a); }
void Controller::ScaleObject(double x) { obj_->Scale(x); }

}  // namespace s21
