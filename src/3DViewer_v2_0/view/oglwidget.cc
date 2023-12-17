#define GL_SILENCE_DEPRECATION
#include "oglwidget.h"

OGLWidget::OGLWidget(QWidget *parent) : QOpenGLWidget{parent} {}
void OGLWidget::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);
}

void OGLWidget::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void OGLWidget::paintGL() {
  glClearColor(backgroundColor.redF(), backgroundColor.greenF(),
               backgroundColor.blueF(), 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if (data_ != nullptr) {
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0, data_->Vertices());
    glEnable(GL_CULL_FACE);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    SetProjectionType();
    DrawVertices();
    DrawEdges();

    glDisableClientState(GL_VERTEX_ARRAY);
  }
}

void OGLWidget::SetProjectionType() const {
  if (perspective) {
    glFrustum(-0.8, 0.8, -0.6, 0.6, 1, 100);
    glTranslatef(0, 0, -3);
  } else
    glOrtho(-1, 1, -0.75, 0.75, -100, 100);
}

void OGLWidget::DrawVertices() {
  if (pointType != 0) {
    if (pointType == 1) {
      glEnable(GL_POINT_SMOOTH);
    } else if (pointType == 2) {
      glDisable(GL_POINT_SMOOTH);
    }
    glPointSize(pointSize);
    glColor3d(pointColor.redF(), pointColor.greenF(), pointColor.blueF());

    glDrawArrays(GL_POINTS, 0, data_->VertexCount() / 3);
  }
}

void OGLWidget::DrawEdges() {
  if (lineType) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x0101);
  } else {
    glDisable(GL_LINE_STIPPLE);
  }
  glLineWidth(lineSize);
  glColor3f(lineColor.redF(), lineColor.greenF(), lineColor.blueF());

  glDrawElements(GL_LINES, data_->FaceIndCount(), GL_UNSIGNED_INT,
                 data_->FaceIndices());
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
  data_->RotateObject(x, s21::X);
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
