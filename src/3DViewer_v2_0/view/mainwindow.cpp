#include "mainwindow.h"

#include <QOpenGLFunctions>
#include <QOpenGLWidget>

#include <QFileDialog>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), oglwidget(new OGLWidget), controller(new s21::Controller) {
  ui->setupUi(this);
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
    ui->label_fileName->setText("error path");
  }

}
