#include <QApplication>

#include "view/mainwindow.h"

int main(int argc, char *argv[]) {
  setlocale(LC_NUMERIC, "C");
  QApplication a(argc, argv);
  s21::MainWindow w;
  w.show();
  return a.exec();
}
