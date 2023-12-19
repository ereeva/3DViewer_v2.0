#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <qgifglobal.h>
#include <qgifimage.h>

#include <QMainWindow>
#include <QSettings>
#include <QStack>
#include <QTimer>

#include "ICommand.h"
#include "controller/controller.h"
#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class ICommand;

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

  void on_radioButton_solid_clicked();

  void on_radioButton_dashed_clicked();

  void on_Slider_lineSize_valueChanged(int value);

  void on_radioButton_parallel_clicked();

  void on_radioButton_central_clicked();

  void on_Slider_pointSize_valueChanged(int value);

  void on_radioButton_none_clicked();

  void on_radioButton_circle_clicked();

  void on_radioButton_sqare_clicked();

  void on_button_BG_color_clicked();

  void on_button_point_color_clicked();

  void on_button_line_color_clicked();

  void on_button_JPG_clicked();

  void on_button_BPM_clicked();

  void on_button_GIF_clicked();

  void RecordGif();

  void updateUI();

  void on_button_Undo_clicked();

 private:
  Ui::MainWindow *ui;
  s21::Controller *controller_;

  QSettings *settings_;

  QGifImage *gif_;
  QTimer *timer_;

  int FPS = 100;
  double posX = 0.0;
  double posY = 0.0;
  double posZ = 0.0;
  double scale = 1.0;
  double rotX = 0.0;
  double rotY = 0.0;
  double rotZ = 0.0;

  void SaveSettings();
  void RestoreSettings();
  void setStateAffinsUI(bool state);

  // commands
  s21::ICommand *solidLineCommand;
  s21::ICommand *dashedLineCommand;
  // s21::ICommand *setPointSizeCommand;

  QStack<s21::ICommand *> commandStack_;
 signals:
  void commandExecuted();

 public slots:
  void executeCommand(s21::ICommand *command);
  void undoLastCommand();
};
#endif  // MAINWINDOW_H
