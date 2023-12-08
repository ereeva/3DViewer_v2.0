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

  // Рисование прямоугольника
  glBegin(GL_QUADS);
  glColor3f(1.0f, 0.0f, 0.0f);
  glVertex2f(-0.5f, -0.5f);
  glVertex2f(0.5f, -0.5f);
  glVertex2f(0.5f, 0.5f);
  glVertex2f(-0.5f, 0.5f);
  glEnd();
}

void OGLWidget::allocate() {
  update();
}
