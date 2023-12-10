#include "mainwindow.h"

#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QColor>
#include <QColorDialog>
#include <QFileDialog>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), oglwidget(new OGLWidget), controller(new s21::Controller) {
  ui->setupUi(this);
  settings_.setValue("background", "red");
}

MainWindow::~MainWindow() {
  delete ui;
  delete oglwidget;
  delete controller;
}

void MainWindow::on_button_selectFile_clicked() {
  QString fileName = QFileDialog::getOpenFileName(this, tr("Select a file"),
                                                   QDir::homePath(), tr(""));
//  ui->label_fileName->setText("  " + fileName);
  // костыль для очистки предыдущей модели
  delete controller;
  controller = new s21::Controller;

//  потом убрать в отдельный метод
  std::string str = fileName.toStdString();
//  std::string str = "obj/cat.obj";
  try {
    controller->LoadObject(str);
    ui->label_fileName->setText("  " + fileName);

    size_t edgesCount = controller->FaceIndCount();
    ui->label_edgesCount->setText(QString::number(edgesCount));

    size_t verticesCount = controller->VertexCount();
    ui->label_verticesCount->setText(QString::number(verticesCount));

    ui->widget->allocate(controller);
  } catch (...) {
    ui->label_fileName->setText("error path or file");
  }

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
  ui->widget->lineType = false;
  ui->widget->update();
}

void MainWindow::on_radioButton_dashed_clicked() {
  ui->widget->lineType = true;
  ui->widget->update();
}

void MainWindow::on_Slider_lineSize_valueChanged(int value) {
  ui->widget->lineSize = (float)value;
  ui->widget->update();
}

void MainWindow::on_radioButton_clicked() {
  ui->widget->perspective = false;
  ui->widget->update();
}

void MainWindow::on_radioButton_central_clicked() {
  ui->widget->perspective = true;
  ui->widget->update();
}

void MainWindow::on_Slider_pointSize_valueChanged(int value) {
  ui->widget->pointSize = (float)value;
  ui->widget->update();
}

void MainWindow::on_radioButton_none_clicked() {
  ui->widget->pointType = 0;
  ui->widget->update();
}

void MainWindow::on_radioButton_circle_clicked() {
  ui->widget->pointType = 1;
  ui->widget->update();
}

void MainWindow::on_radioButton_sqare_clicked() {
  ui->widget->pointType = 2;
  ui->widget->update();
}

void MainWindow::on_button_JPG_2_clicked() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Choose color");
  ui->widget->lineColor = color;
  ui->widget->update();
}

void MainWindow::on_button_JPG_3_clicked() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Choose color");
  ui->widget->backgroundColor = color;
  ui->widget->update();
}

void MainWindow::on_button_JPG_4_clicked() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Choose color");
  ui->widget->pointColor = color;
  ui->widget->update();
}
//
// End styles
//


