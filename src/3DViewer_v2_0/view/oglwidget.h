#ifndef OGLWIDGET_H
#define OGLWIDGET_H

#include <QOpenGLFunctions>
#include <QOpenGLWidget>

#include "../controller/controller.h"

namespace s21 {

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

  /// @brief получение контроллера
  /// @param контроллер
  void allocate(s21::Controller *&controller);

  // affins
  /// @brief движение объекта
  /// @param ось X, ось Y, ось Z
  void translateObject(double x, double y, double z);

  /// @brief поворот объекта по оси X
  /// @param угол
  void rotateObjectX(double x);

  /// @brief поворот объекта по оси Y
  /// @param угол
  void rotateObjectY(double y);

  /// @brief поворот объекта по оси Z
  /// @param угол
  void rotateObjectZ(double z);

  /// @brief увеличение/уменьшение объекта
  /// @param параметр скейлинга
  void scaleObject(double x);

 private:
  s21::Controller *data_ = nullptr;

  /// @brief задать проекцию
  void SetProjectionType() const;

  /// @brief отрисовка линий
  void DrawVertices();

  /// @brief отрисовка точек
  void DrawEdges();
};

}  // namespace s21

#endif  // OGLWIDGET_H
