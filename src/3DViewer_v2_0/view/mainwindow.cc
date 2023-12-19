#include "mainwindow.h"

#include <QColor>
#include <QColorDialog>
#include <QFileDialog>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QSettings>
#include <QSignalBlocker>

#include "Commands.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      controller_(&s21::Controller::getInstance()),
      settings_(new QSettings("3DViewer", "")) {
  ui->setupUi(this);
  RestoreSettings();
  setStateAffinsUI(true);

  connect(this, SIGNAL(commandExecuted()), this, SLOT(updateUI()));
}

MainWindow::~MainWindow() {
  SaveSettings();
  delete settings_;
  delete ui;
}

void MainWindow::on_button_selectFile_clicked() {
  ClearControls();
  QString fileName = QFileDialog::getOpenFileName(
      this, tr("Select a file"), QDir::homePath(), "Obj files (*.obj)");

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
  executeCommand(dynamic_cast<s21::ICommand*>(
      new s21::translateObjectXCommand(ui, (double)value)));
}

void MainWindow::on_Slider_moveY_valueChanged(int value) {
  executeCommand(dynamic_cast<s21::ICommand*>(
      new s21::translateObjectYCommand(ui, (double)value)));
}

void MainWindow::on_Slider_moveZ_valueChanged(int value) {
  executeCommand(dynamic_cast<s21::ICommand*>(
      new s21::translateObjectZCommand(ui, (double)value)));
}

void MainWindow::on_Slider_rotateX_valueChanged(int value) {
  executeCommand(dynamic_cast<s21::ICommand*>(
      new s21::rotateObjectXCommand(ui, (double)value)));
}

void MainWindow::on_Slider_rotateY_valueChanged(int value) {
  executeCommand(dynamic_cast<s21::ICommand*>(
      new s21::rotateObjectYCommand(ui, (double)value)));
}

void MainWindow::on_Slider_rotateZ_valueChanged(int value) {
  executeCommand(dynamic_cast<s21::ICommand*>(
      new s21::rotateObjectZCommand(ui, (double)value)));
}

void MainWindow::on_Slider_scale_valueChanged(int value) {
  executeCommand(dynamic_cast<s21::ICommand*>(
      new s21::scaleObjectCommand(ui, (double)value)));
}

void MainWindow::on_doubleSpinBox_scale_valueChanged(double arg1) {
  executeCommand(dynamic_cast<s21::ICommand*>(
      new s21::scaleObjectCommand(ui, arg1 * ui->widget->FPS)));
}

void MainWindow::on_spinBox_moveX_valueChanged(int arg1) {
  executeCommand(dynamic_cast<s21::ICommand*>(
      new s21::translateObjectXCommand(ui, (double)arg1)));
}

void MainWindow::on_spinBox_moveY_valueChanged(int arg1) {
  executeCommand(dynamic_cast<s21::ICommand*>(
      new s21::translateObjectYCommand(ui, (double)arg1)));
}

void MainWindow::on_spinBox_moveZ_valueChanged(int arg1) {
  executeCommand(dynamic_cast<s21::ICommand*>(
      new s21::translateObjectZCommand(ui, (double)arg1)));
}

void MainWindow::on_spinBox_rotateX_valueChanged(int arg1) {
  executeCommand(dynamic_cast<s21::ICommand*>(
      new s21::rotateObjectXCommand(ui, (double)arg1)));
}

void MainWindow::on_spinBox_rotateY_valueChanged(int arg1) {
  executeCommand(dynamic_cast<s21::ICommand*>(
      new s21::rotateObjectYCommand(ui, (double)arg1)));
}

void MainWindow::on_spinBox_rotateZ_valueChanged(int arg1) {
  executeCommand(dynamic_cast<s21::ICommand*>(
      new s21::rotateObjectZCommand(ui, (double)arg1)));
}
//
// End transformations
//

//
// Start styles
//

void MainWindow::on_Slider_lineSize_valueChanged(int value) {
  executeCommand(dynamic_cast<s21::ICommand*>(
      new s21::SetLineSizeCommand(ui, (float)value)));
}

void MainWindow::on_Slider_pointSize_valueChanged(int value) {
  executeCommand(dynamic_cast<s21::ICommand*>(
      new s21::SetPointSizeCommand(ui, (float)value)));
}

void MainWindow::on_radioButton_solid_clicked() {
  executeCommand(
      dynamic_cast<s21::ICommand*>(new s21::SetLineTypeCommand(ui, false)));
}

void MainWindow::on_radioButton_dashed_clicked() {
  executeCommand(
      dynamic_cast<s21::ICommand*>(new s21::SetLineTypeCommand(ui, true)));
}

void MainWindow::on_radioButton_parallel_clicked() {
  executeCommand(
      dynamic_cast<s21::ICommand*>(new s21::SetPerspectiveCommand(ui, false)));
}

void MainWindow::on_radioButton_central_clicked() {
  executeCommand(
      dynamic_cast<s21::ICommand*>(new s21::SetPerspectiveCommand(ui, true)));
}

void MainWindow::on_radioButton_none_clicked() {
  executeCommand(
      dynamic_cast<s21::ICommand*>(new s21::SetPointTypeCommand(ui, 0)));
}

void MainWindow::on_radioButton_circle_clicked() {
  executeCommand(
      dynamic_cast<s21::ICommand*>(new s21::SetPointTypeCommand(ui, 1)));
}

void MainWindow::on_radioButton_sqare_clicked() {
  executeCommand(
      dynamic_cast<s21::ICommand*>(new s21::SetPointTypeCommand(ui, 2)));
}

void MainWindow::on_button_BG_color_clicked() {
  executeCommand(
      dynamic_cast<s21::ICommand*>(new s21::SetBackgroundColorCommand(
          ui,
          QColorDialog::getColor(Qt::white, this, "Choose background color"))));
}

void MainWindow::on_button_line_color_clicked() {
  executeCommand(dynamic_cast<s21::ICommand*>(new s21::SetLineColorCommand(
      ui, QColorDialog::getColor(Qt::white, this, "Choose line color"))));
}

void MainWindow::on_button_point_color_clicked() {
  executeCommand(dynamic_cast<s21::ICommand*>(new s21::SetPointColorCommand(
      ui, QColorDialog::getColor(Qt::white, this, "Choose point color"))));
}
//
// End styles
//

void MainWindow::updateUI() {
  QSignalBlocker blocker1(ui->spinBox_moveX);
  QSignalBlocker blocker2(ui->Slider_moveX);
  double posX = ui->widget->posX * ui->widget->FPS;
  ui->spinBox_moveX->setValue(posX);
  ui->Slider_moveX->setValue(posX);
  //  ui->Slider_moveX->setSliderPosition(posX);

  QSignalBlocker blocker3(ui->spinBox_moveY);
  QSignalBlocker blocker4(ui->Slider_moveY);
  double posY = ui->widget->posY * ui->widget->FPS;
  ui->spinBox_moveY->setValue(posY);
  ui->Slider_moveY->setValue(posY);

  QSignalBlocker blocker5(ui->spinBox_moveZ);
  QSignalBlocker blocker6(ui->Slider_moveZ);
  double posZ = ui->widget->posZ * ui->widget->FPS;
  ui->spinBox_moveZ->setValue(posZ);
  ui->Slider_moveZ->setValue(posZ);

  QSignalBlocker blocker7(ui->spinBox_rotateX);
  QSignalBlocker blocker8(ui->Slider_rotateX);
  double rotX = ui->widget->rotX * ui->widget->FPS;
  ui->spinBox_rotateX->setValue(rotX);
  ui->Slider_rotateX->setValue(rotX);

  QSignalBlocker blocker9(ui->spinBox_rotateY);
  QSignalBlocker blocker10(ui->Slider_rotateY);
  double rotY = ui->widget->rotY * ui->widget->FPS;
  ui->spinBox_rotateY->setValue(rotY);
  ui->Slider_rotateY->setValue(rotY);

  QSignalBlocker blocker11(ui->spinBox_rotateZ);
  QSignalBlocker blocker12(ui->Slider_rotateZ);
  double rotZ = ui->widget->rotZ * ui->widget->FPS;
  ui->spinBox_rotateZ->setValue(rotZ);
  ui->Slider_rotateZ->setValue(rotZ);

  QSignalBlocker blocker13(ui->doubleSpinBox_scale);
  QSignalBlocker blocker14(ui->Slider_scale);
  double scale = ui->widget->scale;
  ui->doubleSpinBox_scale->setValue(scale);
  ui->Slider_scale->setValue(scale * ui->widget->FPS);

  QSignalBlocker blocker15(ui->Slider_pointSize);
  ui->Slider_pointSize->setValue(ui->widget->pointSize);

  QSignalBlocker blocker16(ui->Slider_lineSize);
  ui->Slider_lineSize->setValue(ui->widget->lineSize);

  QRadioButton* radioButtonToClick1 =
      (ui->widget->lineType) ? ui->radioButton_dashed : ui->radioButton_solid;
  radioButtonToClick1->blockSignals(true);
  radioButtonToClick1->click();
  radioButtonToClick1->blockSignals(false);

  QRadioButton* radioButtonToClick2 = (ui->widget->perspective)
                                          ? ui->radioButton_central
                                          : ui->radioButton_parallel;
  radioButtonToClick2->blockSignals(true);
  radioButtonToClick2->click();
  radioButtonToClick2->blockSignals(false);

  QRadioButton* radioButtonToClick3 = nullptr;
  if (ui->widget->pointType == 1)
    radioButtonToClick3 = ui->radioButton_circle;
  else if (ui->widget->pointType == 2)
    radioButtonToClick3 = ui->radioButton_sqare;
  else
    radioButtonToClick3 = ui->radioButton_none;

  radioButtonToClick3->blockSignals(true);
  radioButtonToClick3->click();
  radioButtonToClick3->blockSignals(false);

  ui->widget->update();
}

void MainWindow::on_button_Undo_clicked() { undoLastCommand(); }

void MainWindow::executeCommand(s21::ICommand* command) {
  if (command) {
    commandStack_.push(command);
    command->execute();
    emit commandExecuted();
  }
}

void MainWindow::undoLastCommand() {
  if (!commandStack_.isEmpty()) {
    s21::ICommand* command = commandStack_.pop();
    command->undo();
    emit commandExecuted();
    delete command;
  }
}

void MainWindow::ClearControls() {
  ui->Slider_moveX->setValue(0);
  ui->Slider_moveY->setValue(0);
  ui->Slider_moveZ->setValue(0);

  ui->Slider_rotateX->setValue(0);
  ui->Slider_rotateY->setValue(0);
  ui->Slider_rotateZ->setValue(0);

  ui->Slider_scale->setValue(100);
}