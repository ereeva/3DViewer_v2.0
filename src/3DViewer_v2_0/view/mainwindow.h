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

namespace Ui {
class MainWindow;
}

namespace s21 {

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

  /// @brief сохранение настроек стилей
  void SaveSettings();

  /// @brief восстановление настроек стилей
  void RestoreSettings();

  /// @brief заблокировать ui элементы преобразований
  /// @param заблокировать/разблокировать
  void setStateAffinsUI(bool state);

  /// @brief сбросить ui элементы до default
  void ClearControls();

  /// @brief стек для хранения выполненных комад, для возможности их отмены
  QStack<s21::ICommand *> commandStack_;
 signals:
  void commandExecuted();

 public slots:
  /// @brief переопределенная функция вызова команд
  /// @param класс команды, преобразованный до интерфейса ICommand и выполнить
  /// метод execute()
  void executeCommand(s21::ICommand *command);

  /// @brief достать из стека последнюю выполненную команду и выполнить ее метод
  /// undo()
  void undoLastCommand();
};

}  // namespace s21

#endif  // MAINWINDOW_H
