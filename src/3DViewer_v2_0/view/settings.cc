#include "mainwindow.h"


enum ProjectionType { kParallel, kCentral };
enum EdgeType { kSolid, kDashed };
enum VertexType { kNone, kCircle, kSquare };

void MainWindow::SaveSettings() {
  // settings_->setValue("background_color", backgroundColor);
  // settings_->setValue("edge_color", lineColor);
  // settings_->setValue("vertex_color", pointColor);

  if (ui->radioButton->isChecked()) {
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
  // QColor backgroundColor =
  // settings_->value("background_color").value<QColor>; QColor lineColor =
  // settings_->value("edge_color").value<QColor>; QColor pointColor =
  // settings_->value("vertex_color").value<QColor>;

  if (settings_->value("projection_type") == kParallel)
    ui->radioButton->setChecked(true);
  else
    ui->radioButton_central->setChecked(true);

  ui->Slider_lineSize->setValue(settings_->value("edge_thickness", 1).toInt());

  if (settings_->value("edge_type") == kDashed)
    ui->radioButton_dashed->setChecked(true);
  else
    ui->radioButton_solid->setChecked(true);

  ui->Slider_pointSize->setValue(settings_->value("vertex_size", 1).toInt());

  if (settings_->value("vertex_type") == kCircle)
    ui->radioButton_circle->setChecked(true);
  if (settings_->value("vertex_type") == kSquare)
    ui->radioButton_sqare->setChecked(true);
  else
    ui->radioButton_none->setChecked(true);
}
