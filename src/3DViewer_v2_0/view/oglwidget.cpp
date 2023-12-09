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
