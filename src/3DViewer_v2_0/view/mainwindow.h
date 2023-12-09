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

 private:
  Ui::MainWindow *ui;
  OGLWidget *oglwidget;
  s21::Controller *controller;

};
#endif  // MAINWINDOW_H
