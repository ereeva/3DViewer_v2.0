#ifndef VIEWER_V2_CONTROLLER_SETTINGS_H_
#define VIEWER_V2_CONTROLLER_SETTINGS_H_

#include <QSettings>
#include <QString>

class Color;

class Settings {
 public:
  Settings(QSettings *s) : settings_(s) {}
  QString Filename() const;

 private:
  QSettings *settings_;
};

class Color {
 public:
  void SetColor(double r, double g, double b) {
    r_ = r;
    g_ = g;
    b_ = b;
  }
  double R() const { return r_; }
  double G() const { return g_; }
  double B() const { return b_; }

 private:
  double r_{}, g_{}, b_{};
};

#endif  // VIEWER_V2_CONTROLLER_SETTINGS_H_