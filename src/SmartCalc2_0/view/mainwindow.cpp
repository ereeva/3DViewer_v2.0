#include "mainwindow.h"

#include <QOpenGLFunctions>
#include <QOpenGLWidget>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  oglwidget = new OGLWidget;

  ui->widget->allocate();
}

MainWindow::~MainWindow() {
  delete ui;
  delete oglwidget;
}

