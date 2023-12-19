#ifndef OGLWIDGET_H
#define OGLWIDGET_H

// #include <QObject>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
// #include <QtOpenGLWidgets>

#include "../controller/controller.h"

class OGLWidget : public QOpenGLWidget, public QOpenGLFunctions {
  Q_OBJECT
 public:
  OGLWidget(QWidget *parent = nullptr);
  void paintGL() override;

  // settings
  QColor backgroundColor;
  bool lineType = false;
  float lineSize = 1;
  float pointSize = 5;
  int pointType = 0;
  QColor pointColor = QColor(255, 0, 0);
  bool perspective = false;
  QColor lineColor = QColor(0, 255, 0);

  int FPS = 100;
  double posX = 0.0;
  double posY = 0.0;
  double posZ = 0.0;
  double scale = 1.0;
  double rotX = 0.0;
  double rotY = 0.0;
  double rotZ = 0.0;

 protected:
  void initializeGL() override;
  void resizeGL(int w, int h) override;

 public slots:
  void allocate(s21::Controller *&controller);

  // affins
  void translateObject(double x, double y, double z);
  void rotateObjectX(double x);
  void rotateObjectY(double y);
  void rotateObjectZ(double z);
  void scaleObject(double x);

 private:
  s21::Controller *data_ = nullptr;

  void SetProjectionType() const;
  void DrawVertices();
  void DrawEdges();
};

#endif  // OGLWIDGET_H
