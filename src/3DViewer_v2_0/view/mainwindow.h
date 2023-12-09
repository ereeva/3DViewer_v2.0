#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "oglwidget.h"
#include "controller/controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_button_selectFile_clicked();

  void on_Slider_moveX_valueChanged(int value);

  void on_Slider_moveY_valueChanged(int value);

  void on_Slider_moveZ_valueChanged(int value);

  void on_Slider_rotateX_valueChanged(int value);

  void on_Slider_rotateY_valueChanged(int value);

  void on_Slider_rotateZ_valueChanged(int value);

  void on_Slider_scale_valueChanged(int value);

  void on_doubleSpinBox_scale_valueChanged(double arg1);

  void on_spinBox_moveX_valueChanged(int arg1);

  void on_spinBox_moveY_valueChanged(int arg1);

  void on_spinBox_moveZ_valueChanged(int arg1);

  void on_spinBox_rotateX_valueChanged(int arg1);

  void on_spinBox_rotateY_valueChanged(int arg1);

  void on_spinBox_rotateZ_valueChanged(int arg1);

 private:
  Ui::MainWindow *ui;
  OGLWidget *oglwidget;
  s21::Controller *controller;

  int FPS = 100;
  double posX = 0.0;
  double posY = 0.0;
  double posZ = 0.0;
  double scale = 1.0;
  double rotX = 0.0;
  double rotY = 0.0;
  double rotZ = 0.0;

};
#endif  // MAINWINDOW_H
