#ifndef OGLWIDGET_H
#define OGLWIDGET_H

//#include <QObject>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
//#include <QtOpenGLWidgets>

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
};

#endif  // OGLWIDGET_H
