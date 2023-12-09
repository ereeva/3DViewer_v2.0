#include "oglwidget.h"

OGLWidget::OGLWidget(QWidget *parent) : QOpenGLWidget{parent} {}
void OGLWidget::initializeGL() {
  initializeOpenGLFunctions();
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//  glEnable(GL_DEPTH_TEST);
}

void OGLWidget::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void OGLWidget::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT);
  if (data_ != nullptr) {
    glVertexPointer(3, GL_DOUBLE, 0, data_->Vertices());
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnable(GL_POINT_SMOOTH);
    glDisable(GL_POINT_SMOOTH);
    glDrawArrays(GL_POINTS, 0, data_->VertexCount());

    glLineStipple(1, 0x00FF);
    glDrawElements(GL_LINES, data_->FaceIndCount(), GL_UNSIGNED_INT, data_->FaceIndices());
    glDisableClientState(GL_VERTEX_ARRAY);
  }
}

void OGLWidget::allocate(s21::Controller *&controller) {
  data_ = controller;
  update();
}

void OGLWidget::translateObject(double x, double y, double z) {
  data_->TranslateObject(x, s21::X);
  data_->TranslateObject(y, s21::Y);
  data_->TranslateObject(z, s21::Z);

  update();
}

void OGLWidget::rotateObjectX(double x) {
  data_->RotateObjectX(x);
  update();
}

void OGLWidget::rotateObjectY(double y) {
  data_->RotateObject(y, s21::Y);
  update();
}

void OGLWidget::rotateObjectZ(double z) {
  data_->RotateObject(z, s21::Z);
  update();
}

void OGLWidget::scaleObject(double x) {
  data_->ScaleObject(x);
  update();
}
