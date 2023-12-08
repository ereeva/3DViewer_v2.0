#ifndef OGLWIDGET_H
#define OGLWIDGET_H

//#include <QObject>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
//#include <QtOpenGLWidgets>

class OGLWidget : public QOpenGLWidget, public QOpenGLFunctions {
  Q_OBJECT
 public:
  OGLWidget(QWidget *parent = nullptr);
  void paintGL() override;

 protected:
  void initializeGL() override;
  void resizeGL(int w, int h) override;

 public slots:
  void allocate();
};

#endif  // OGLWIDGET_H
