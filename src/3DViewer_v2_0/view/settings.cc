#include "mainwindow.h"

enum ProjectionType { kParallel, kCentral };
enum EdgeType { kSolid, kDashed };
enum VertexType { kNone, kCircle, kSquare };

void MainWindow::SaveSettings_() {
  // settings_->setValue("background_color", backgroundColor);
  // settings_->setValue("edge_color", lineColor);
  // settings_->setValue("vertex_color", pointColor);

  if (ui_->radioButton->isChecked()) {
    settings_->setValue("projection_type", kParallel);
  } else {
    settings_->setValue("projection_type", kCentral);
  }

  settings_->setValue("edge_thickness", ui_->Slider_lineSize->value());

  if (ui_->radioButton_solid->isChecked()) {
    settings_->setValue("edge_type", kSolid);
  } else {
    settings_->setValue("edge_type", kDashed);
  }

  settings_->setValue("vertex_size", ui_->Slider_pointSize->value());

  if (ui_->radioButton_circle->isChecked()) {
    settings_->setValue("vertex_type", kCircle);
  } else if (ui_->radioButton_sqare->isChecked()) {
    settings_->setValue("vertex_type", kSquare);
  } else {
    settings_->setValue("vertex_type", kNone);
  }
}

void MainWindow::RestoreSettings_() {
  // QColor backgroundColor =
  // settings_->value("background_color").value<QColor>; QColor lineColor =
  // settings_->value("edge_color").value<QColor>; QColor pointColor =
  // settings_->value("vertex_color").value<QColor>;

  if (settings_->value("projection_type") == kParallel)
    ui_->radioButton->setChecked();
  else
    ui_->radioButton_central->setChecked();

  ui_->Slider_lineSize->setValue(settings_->value("edge_thickness", 1).toInt());

  if (settings_->value("edge_type") == kSolid)
    ui_->radioButton_solid->setChecked();
  else
    ui_->radioButton_dashed->setChecked();

  ui_->Slider_pointSize->setValue(settings_->value("vertex_size", 1).toInt());

  if (settings_->value("vertex_type") == kCircle)
    ui_->radioButton_circle->setChecked();
  if (settings_->value("vertex_type") == kSquare)
    ui_->radioButton_sqare->setChecked();
  else
    ui_->radioButton_none->setChecked();
}