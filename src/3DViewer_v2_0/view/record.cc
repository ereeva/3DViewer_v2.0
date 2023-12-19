#include <QFileDialog>

#include "mainwindow.h"

void MainWindow::on_button_BPM_clicked() {
  QString path = QFileDialog::getSaveFileName(this, ("Save as BMP"),
                                              "image.bmp", "BMP (*.bmp)");

  if (!path.isNull()) ui->widget->grabFramebuffer().save(path, "bmp");
}

void MainWindow::on_button_JPG_clicked() {
  QString path = QFileDialog::getSaveFileName(this, ("Save as JPEG"),
                                              "image.jpeg", "JPEG (*.jpeg)");

  if (!path.isNull()) ui->widget->grabFramebuffer().save(path, "jpeg");
}

void MainWindow::on_button_GIF_clicked() {
  gif_ = new QGifImage;
  timer_ = new QTimer(this);
  gif_->setDefaultDelay(100);
  connect(timer_, SIGNAL(timeout()), this, SLOT(RecordGif()));
  timer_->start(100);
}

void MainWindow::RecordGif() {
  static int count = 0;
  gif_->addFrame(
      ui->widget->grabFramebuffer().scaled(
          QSize(640, 480), Qt::IgnoreAspectRatio, Qt::SmoothTransformation),
      0);

  ++count;
  if (count == 50) {
    timer_->stop();
    QString path = QFileDialog::getSaveFileName(this, ("Save GIF"), "image.gif",
                                                "GIF (*.gif)");
    if (!path.isNull()) gif_->save(path);
    delete timer_;
    delete gif_;
    count = 0;
  }
}
