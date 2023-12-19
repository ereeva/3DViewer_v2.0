#include "mainwindow.h"

enum ProjectionType { kParallel, kCentral };
enum EdgeType { kSolid, kDashed };
enum VertexType { kNone, kCircle, kSquare };

void MainWindow::SaveSettings() {
  settings_->setValue("background_color", ui->widget->backgroundColor);
  settings_->setValue("edge_color", ui->widget->lineColor);
  settings_->setValue("vertex_color", ui->widget->pointColor);
  
  if (ui->radioButton_parallel->isChecked()) {
    settings_->setValue("projection_type", kParallel);
  } else {
    settings_->setValue("projection_type", kCentral);
  }

  settings_->setValue("edge_thickness", ui->Slider_lineSize->value());

  if (ui->radioButton_solid->isChecked()) {
    settings_->setValue("edge_type", kSolid);
  } else {
    settings_->setValue("edge_type", kDashed);
  }

  settings_->setValue("vertex_size", ui->Slider_pointSize->value());

  if (ui->radioButton_circle->isChecked()) {
    settings_->setValue("vertex_type", kCircle);
  } else if (ui->radioButton_sqare->isChecked()) {
    settings_->setValue("vertex_type", kSquare);
  } else {
    settings_->setValue("vertex_type", kNone);
  }
}

void MainWindow::RestoreSettings() {
  ui->widget->backgroundColor =
      settings_->value("background_color").value<QColor>();
  ui->widget->lineColor = settings_->value("edge_color").value<QColor>();
  ui->widget->pointColor = settings_->value("vertex_color").value<QColor>();

  if (settings_->value("projection_type").toInt() == kParallel) {
    ui->radioButton_parallel->setChecked(true);
    ui->widget->perspective = false;
  } else {
    ui->radioButton_central->setChecked(true);
    ui->widget->perspective = true;
  }

  ui->Slider_lineSize->setValue(settings_->value("edge_thickness", 1).toInt());

  if (settings_->value("edge_type").toInt() == kDashed) {
    ui->radioButton_dashed->setChecked(true);
    ui->widget->lineType = true;
  } else {
    ui->radioButton_solid->setChecked(true);
    ui->widget->lineType = false;
  }

  ui->Slider_pointSize->setValue(settings_->value("vertex_size", 1).toInt());

  if (settings_->value("vertex_type").toInt() == kCircle) {
    ui->radioButton_circle->setChecked(true);
    ui->widget->pointType = 1;
  } else if (settings_->value("vertex_type").toInt() == kSquare) {
    ui->radioButton_sqare->setChecked(true);
    ui->widget->pointType = 2;
  } else {
    ui->radioButton_none->setChecked(true);
    ui->widget->pointType = 0;
  }
}
