#ifndef VIEWER_V2_CONTROLLER_CONTROLLER_H_
#define VIEWER_V2_CONTROLLER_CONTROLLER_H_

#include "../model/3D_object.h"
#include "../model/parser.h"

namespace s21 {
class Controller {
 public:
  Controller() : parser_(std::make_unique<Parser>()) {}
  ~Controller() = default;

  void LoadObject(std::string &file_name);

  size_t VertexCount() const;
  size_t FaceIndCount() const;
  const double *Vertices() const;
  const int *FaceIndices() const;

  void TranslateObject(double x, Axis a);
  void RotateObject(double x, Axis a);
  void ScaleObject(double x);
  bool Status() const;

 private:
  std::unique_ptr<Object> obj_;
  std::unique_ptr<Parser> parser_;
};
}  // namespace s21

#endif
