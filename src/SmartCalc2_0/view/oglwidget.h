#ifndef OGLWIDGET_H
#define OGLWIDGET_H

#include <QColor>
#include <QObject>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QtOpenGLWidgets>

#define RGB_MIN 1
#define RGB_MAX 255

class OGLWidget : public QOpenGLWidget, public QOpenGLFunctions {
  Q_OBJECT
 public:
  OGLWidget(QWidget *parent = nullptr);
  void paintGL() override;
  QString findFile;
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
  QOpenGLShaderProgram *prog = nullptr;
  double x, y, z;
};

#endif  // OGLWIDGET_H
