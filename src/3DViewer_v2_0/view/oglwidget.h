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

 protected:
  void initializeGL() override;
  void resizeGL(int w, int h) override;

 public slots:
  void allocate(s21::Controller *&controller);

 private:
  s21::Controller *data_ = nullptr;
};

#endif  // OGLWIDGET_H
