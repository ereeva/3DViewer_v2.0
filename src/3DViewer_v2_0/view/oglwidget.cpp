#include "oglwidget.h"

OGLWidget::OGLWidget(QWidget *parent) : QOpenGLWidget{parent} {}
void OGLWidget::initializeGL() {
  initializeOpenGLFunctions();
  //glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//  glEnable(GL_DEPTH_TEST);
}

void OGLWidget::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void OGLWidget::paintGL() {
  glClearColor(backgroundColor.redF(), backgroundColor.greenF(),
               backgroundColor.blueF(), 1);
  glClear(GL_COLOR_BUFFER_BIT);

  // styles
  glLineWidth(lineSize);
  glPointSize(pointSize);
  glColor3f(lineColor.redF(), lineColor.greenF(), lineColor.blueF());
  if (lineType) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x0101);
  } else {
    glDisable(GL_LINE_STIPPLE);
  }
  if (pointType == 1) {
    glEnable(GL_POINT_SMOOTH);
  } else if (pointType == 2) {
    glDisable(GL_POINT_SMOOTH);
  }

  if (data_ != nullptr) {
    glVertexPointer(3, GL_DOUBLE, 0, data_->Vertices());
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnable(GL_POINT_SMOOTH);
    glDisable(GL_POINT_SMOOTH);
    glDrawArrays(GL_POINTS, 0, data_->VertexCount());

    //glColor3d(pointColor.redF(), pointColor.greenF(), pointColor.blueF());
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
