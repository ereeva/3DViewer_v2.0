#include "mainwindow.h"

#include <QColor>
#include <QColorDialog>
#include <QFileDialog>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QSettings>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      controller_(&s21::Controller::getInstance()),
      settings_(new QSettings("3DViewer", "")) {
  ui->setupUi(this);
  RestoreSettings();
  setStateAffinsUI(true);
}

MainWindow::~MainWindow() {
  SaveSettings();
  delete settings_;
  delete ui;
  delete controller_;
}

void MainWindow::on_button_selectFile_clicked() {
  QString fileName = QFileDialog::getOpenFileName(this, tr("Select a file"),
                                                  QDir::homePath(), tr(""));

  std::string str = fileName.toStdString();
  try {
    controller_->LoadObject(str);
  } catch (...) {
    ui->label_fileName->setText("error path or file");
    setStateAffinsUI(true);
    return;
  }

  ui->widget->allocate(controller_);

  ui->label_fileName->setText("  " + fileName);
  ui->label_edgesCount->setText(QString::number(controller_->FaceIndCount()));
  ui->label_verticesCount->setText(QString::number(controller_->VertexCount()));

  setStateAffinsUI(false);
}

void MainWindow::setStateAffinsUI(bool state) {
  ui->spinBox_moveX->setDisabled(state);
  ui->spinBox_moveY->setDisabled(state);
  ui->spinBox_moveZ->setDisabled(state);
  ui->spinBox_rotateX->setDisabled(state);
  ui->spinBox_rotateY->setDisabled(state);
  ui->spinBox_rotateZ->setDisabled(state);
  ui->doubleSpinBox_scale->setDisabled(state);

  ui->Slider_rotateX->setDisabled(state);
  ui->Slider_rotateY->setDisabled(state);
  ui->Slider_rotateZ->setDisabled(state);
  ui->Slider_moveX->setDisabled(state);
  ui->Slider_moveY->setDisabled(state);
  ui->Slider_moveZ->setDisabled(state);
  ui->Slider_scale->setDisabled(state);
}

//
// Start transformations
//
void MainWindow::on_Slider_moveX_valueChanged(int value) {
  double result = (double)value / FPS - posX;
  posX = (double)value / FPS;
  ui->spinBox_moveX->blockSignals(true);
  ui->spinBox_moveX->setValue(value);
  ui->spinBox_moveX->blockSignals(false);

  ui->widget->translateObject(result, 0, 0);
}

void MainWindow::on_Slider_moveY_valueChanged(int value) {
  double result = (double)value / FPS - posY;
  posY = (double)value / FPS;
  ui->spinBox_moveY->blockSignals(true);
  ui->spinBox_moveY->setValue(value);
  ui->spinBox_moveY->blockSignals(false);

  ui->widget->translateObject(0, result, 0);
}

void MainWindow::on_Slider_moveZ_valueChanged(int value) {
  double result = (double)value / FPS - posZ;
  posZ = (double)value / FPS;
  ui->spinBox_moveZ->blockSignals(true);
  ui->spinBox_moveZ->setValue(value);
  ui->spinBox_moveZ->blockSignals(false);

  ui->widget->translateObject(0, 0, result);
}

void MainWindow::on_Slider_rotateX_valueChanged(int value) {
  double result = (double)value / 100 - rotX;
  rotX = (double)value / 100;
  ui->spinBox_rotateX->blockSignals(true);
  ui->spinBox_rotateX->setValue(value);
  ui->spinBox_rotateX->blockSignals(false);

  ui->widget->rotateObjectX(result);
}

void MainWindow::on_Slider_rotateY_valueChanged(int value) {
  double result = (double)value / 100 - rotY;
  rotY = (double)value / 100;
  ui->spinBox_rotateY->blockSignals(true);
  ui->spinBox_rotateY->setValue(value);
  ui->spinBox_rotateY->blockSignals(false);

  ui->widget->rotateObjectY(result);
}

void MainWindow::on_Slider_rotateZ_valueChanged(int value) {
  double result = (double)value / 100 - rotZ;
  rotZ = (double)value / 100;
  ui->spinBox_rotateZ->blockSignals(true);
  ui->spinBox_rotateZ->setValue(value);
  ui->spinBox_rotateZ->blockSignals(false);

  ui->widget->rotateObjectZ(result);
}

void MainWindow::on_Slider_scale_valueChanged(int value) {
  double result = (double)value / (FPS * 10.0) / scale;
  scale = (double)value / (FPS * 10.0);
  ui->doubleSpinBox_scale->blockSignals(true);
  ui->doubleSpinBox_scale->setValue(scale);
  ui->doubleSpinBox_scale->blockSignals(false);

  ui->widget->scaleObject(result);
}

void MainWindow::on_doubleSpinBox_scale_valueChanged(double arg1) {
  int res = (int)(arg1 * 1000.0);
  ui->Slider_scale->setSliderPosition(res);
  ui->Slider_scale->setValue(res);
}

void MainWindow::on_spinBox_moveX_valueChanged(int arg1) {
  ui->Slider_moveX->setSliderPosition(arg1);
  ui->Slider_moveX->setValue(arg1);
}

void MainWindow::on_spinBox_moveY_valueChanged(int arg1) {
  ui->Slider_moveY->setSliderPosition(arg1);
  ui->Slider_moveY->setValue(arg1);
}

void MainWindow::on_spinBox_moveZ_valueChanged(int arg1) {
  ui->Slider_moveZ->setSliderPosition(arg1);
  ui->Slider_moveZ->setValue(arg1);
}

void MainWindow::on_spinBox_rotateX_valueChanged(int arg1) {
  ui->Slider_rotateX->setSliderPosition(arg1);
  ui->Slider_rotateX->setValue(arg1);
}

void MainWindow::on_spinBox_rotateY_valueChanged(int arg1) {
  ui->Slider_rotateY->setSliderPosition(arg1);
  ui->Slider_rotateY->setValue(arg1);
}

void MainWindow::on_spinBox_rotateZ_valueChanged(int arg1) {
  ui->Slider_rotateZ->setSliderPosition(arg1);
  ui->Slider_rotateZ->setValue(arg1);
}
//
// End transformations
//

//
// Start styles
//
void MainWindow::on_radioButton_solid_clicked() {
  ui->widget->setLineType(false);
}

void MainWindow::on_radioButton_dashed_clicked() {
  ui->widget->setLineType(true);
}

void MainWindow::on_Slider_lineSize_valueChanged(int value) {
  ui->widget->setLineSize((float)value);
}

void MainWindow::on_radioButton_parallel_clicked() {
  ui->widget->setPerspective(false);
}

void MainWindow::on_radioButton_central_clicked() {
  ui->widget->setPerspective(true);
}

void MainWindow::on_Slider_pointSize_valueChanged(int value) {
  ui->widget->setPointSize((float)value);
}

void MainWindow::on_radioButton_none_clicked() { ui->widget->setPointType(0); }

void MainWindow::on_radioButton_circle_clicked() {
  ui->widget->setPointType(1);
}

void MainWindow::on_radioButton_sqare_clicked() { ui->widget->setPointType(2); }

void MainWindow::on_button_line_color_clicked() {
  ui->widget->setLineColor(
      QColorDialog::getColor(Qt::white, this, "Choose line color"));
}

void MainWindow::on_button_BG_color_clicked() {
  ui->widget->setBackgroudColor(
      QColorDialog::getColor(Qt::white, this, "Choose background color"));
}

void MainWindow::on_button_point_color_clicked() {
  ui->widget->setPointColor(
      QColorDialog::getColor(Qt::white, this, "Choose point color"));
}
//
// End styles
//
