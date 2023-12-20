#ifndef COMMANDS_H
#define COMMANDS_H

#include <QColor>

#include "ICommand.h"
#include "oglwidget.h"
#include "ui_mainwindow.h"

namespace s21 {

class SetPointSizeCommand : public ICommand {
 private:
  Ui::MainWindow *ui_;
  float newValue_;
  float oldValue_;

 public:
  SetPointSizeCommand(Ui::MainWindow *ui, float size)
      : ui_(ui), newValue_(size), oldValue_(ui_->widget->pointSize) {}

  void execute() override { ui_->widget->pointSize = newValue_; }

  void undo() override { ui_->widget->pointSize = oldValue_; }
};

class SetLineSizeCommand : public ICommand {
 private:
  Ui::MainWindow *ui_;
  float newValue_;
  float oldValue_;

 public:
  SetLineSizeCommand(Ui::MainWindow *ui, float size)
      : ui_(ui), newValue_(size), oldValue_(ui_->widget->lineSize) {}

  void execute() override { ui_->widget->lineSize = newValue_; }

  void undo() override { ui_->widget->lineSize = oldValue_; }
};

class SetLineTypeCommand : public ICommand {
 private:
  Ui::MainWindow *ui_;
  bool newValue_;
  bool oldValue_;

 public:
  SetLineTypeCommand(Ui::MainWindow *ui, bool type)
      : ui_(ui), newValue_(type), oldValue_(ui_->widget->lineType) {}

  void execute() override { ui_->widget->lineType = newValue_; }

  void undo() override { ui_->widget->lineType = oldValue_; }
};

class SetPerspectiveCommand : public ICommand {
 private:
  Ui::MainWindow *ui_;
  bool newValue_;
  bool oldValue_;

 public:
  SetPerspectiveCommand(Ui::MainWindow *ui, bool perspective)
      : ui_(ui), newValue_(perspective), oldValue_(ui_->widget->perspective) {}

  void execute() override { ui_->widget->perspective = newValue_; }

  void undo() override { ui_->widget->perspective = oldValue_; }
};

class SetPointTypeCommand : public ICommand {
 private:
  Ui::MainWindow *ui_;
  int newValue_;
  int oldValue_;

 public:
  SetPointTypeCommand(Ui::MainWindow *ui, int type)
      : ui_(ui), newValue_(type), oldValue_(ui_->widget->pointType) {}

  void execute() override { ui_->widget->pointType = newValue_; }

  void undo() override { ui_->widget->pointType = oldValue_; }
};

// colors
class SetLineColorCommand : public ICommand {
 private:
  Ui::MainWindow *ui_;
  QColor newValue_;
  QColor oldValue_;

 public:
  SetLineColorCommand(Ui::MainWindow *ui, QColor color)
      : ui_(ui), newValue_(color), oldValue_(ui_->widget->lineColor) {}

  void execute() override { ui_->widget->lineColor = newValue_; }

  void undo() override { ui_->widget->lineColor = oldValue_; }
};

class SetPointColorCommand : public ICommand {
 private:
  Ui::MainWindow *ui_;
  QColor newValue_;
  QColor oldValue_;

 public:
  SetPointColorCommand(Ui::MainWindow *ui, QColor color)
      : ui_(ui), newValue_(color), oldValue_(ui_->widget->pointColor) {}

  void execute() override { ui_->widget->pointColor = newValue_; }

  void undo() override { ui_->widget->pointColor = oldValue_; }
};

class SetBackgroundColorCommand : public ICommand {
 private:
  Ui::MainWindow *ui_;
  QColor newValue_;
  QColor oldValue_;

 public:
  SetBackgroundColorCommand(Ui::MainWindow *ui, QColor color)
      : ui_(ui), newValue_(color), oldValue_(ui_->widget->backgroundColor) {}

  void execute() override { ui_->widget->backgroundColor = newValue_; }

  void undo() override { ui_->widget->backgroundColor = oldValue_; }
};

// affins
class translateObjectXCommand : public ICommand {
 protected:
  Ui::MainWindow *ui_;
  double newValue_;
  double oldValue_;

 public:
  translateObjectXCommand(Ui::MainWindow *ui, double value)
      : ui_(ui), newValue_(value), oldValue_(ui_->widget->posX) {}

  void execute() override {
    double result = (newValue_ / ui_->widget->FPS) - ui_->widget->posX;
    ui_->widget->posX = newValue_ / ui_->widget->FPS;
    ui_->widget->translateObject(result, 0, 0);
  }

  void undo() override {
    double result = (oldValue_)-ui_->widget->posX;
    ui_->widget->posX = oldValue_;
    ui_->widget->translateObject(result, 0, 0);
  }
};

class translateObjectYCommand : public ICommand {
 protected:
  Ui::MainWindow *ui_;
  double newValue_;
  double oldValue_;

 public:
  translateObjectYCommand(Ui::MainWindow *ui, double value)
      : ui_(ui), newValue_(value), oldValue_(ui_->widget->posY) {}

  void execute() override {
    double result = (newValue_ / ui_->widget->FPS) - ui_->widget->posY;
    ui_->widget->posY = newValue_ / ui_->widget->FPS;
    ui_->widget->translateObject(0, result, 0);
  }

  void undo() override {
    double result = (oldValue_)-ui_->widget->posY;
    ui_->widget->posY = oldValue_;
    ui_->widget->translateObject(0, result, 0);
  }
};

class translateObjectZCommand : public ICommand {
 protected:
  Ui::MainWindow *ui_;
  double newValue_;
  double oldValue_;

 public:
  translateObjectZCommand(Ui::MainWindow *ui, double value)
      : ui_(ui), newValue_(value), oldValue_(ui_->widget->posZ) {}

  void execute() override {
    double result = (newValue_ / ui_->widget->FPS) - ui_->widget->posZ;
    ui_->widget->posZ = newValue_ / ui_->widget->FPS;
    ui_->widget->translateObject(0, 0, result);
  }

  void undo() override {
    double result = (oldValue_)-ui_->widget->posZ;
    ui_->widget->posZ = oldValue_;
    ui_->widget->translateObject(0, 0, result);
  }
};

class rotateObjectXCommand : public ICommand {
 protected:
  Ui::MainWindow *ui_;
  double newValue_;
  double oldValue_;

 public:
  rotateObjectXCommand(Ui::MainWindow *ui, double value)
      : ui_(ui), newValue_(value), oldValue_(ui_->widget->rotX) {}

  void execute() override {
    double result = newValue_ / ui_->widget->FPS - ui_->widget->rotX;
    ui_->widget->rotX = newValue_ / ui_->widget->FPS;
    ui_->widget->rotateObjectX(result);
  }

  void undo() override {
    double result = oldValue_ - ui_->widget->rotX;
    ui_->widget->rotX = oldValue_;
    ui_->widget->rotateObjectX(result);
  }
};

class rotateObjectYCommand : public ICommand {
 protected:
  Ui::MainWindow *ui_;
  double newValue_;
  double oldValue_;

 public:
  rotateObjectYCommand(Ui::MainWindow *ui, double value)
      : ui_(ui), newValue_(value), oldValue_(ui_->widget->rotY) {}

  void execute() override {
    double result = newValue_ / ui_->widget->FPS - ui_->widget->rotY;
    ui_->widget->rotY = newValue_ / ui_->widget->FPS;
    ui_->widget->rotateObjectY(result);
  }

  void undo() override {
    double result = oldValue_ - ui_->widget->rotY;
    ui_->widget->rotY = oldValue_;
    ui_->widget->rotateObjectY(result);
  }
};

class rotateObjectZCommand : public ICommand {
 protected:
  Ui::MainWindow *ui_;
  double newValue_;
  double oldValue_;

 public:
  rotateObjectZCommand(Ui::MainWindow *ui, double value)
      : ui_(ui), newValue_(value), oldValue_(ui_->widget->rotZ) {}

  void execute() override {
    double result = newValue_ / ui_->widget->FPS - ui_->widget->rotZ;
    ui_->widget->rotZ = newValue_ / ui_->widget->FPS;
    ui_->widget->rotateObjectZ(result);
  }

  void undo() override {
    double result = oldValue_ - ui_->widget->rotZ;
    ui_->widget->rotZ = oldValue_;
    ui_->widget->rotateObjectZ(result);
  }
};

class scaleObjectCommand : public ICommand {
 protected:
  Ui::MainWindow *ui_;
  double newValue_;
  double oldValue_;

 public:
  scaleObjectCommand(Ui::MainWindow *ui, double value)
      : ui_(ui), newValue_(value), oldValue_(ui_->widget->scale) {}

  void execute() override {
    double result = newValue_ / (ui_->widget->FPS) / ui_->widget->scale;
    ui_->widget->scale = newValue_ / (ui_->widget->FPS);
    ui_->widget->scaleObject(result);
  }

  void undo() override {
    double result = oldValue_ / ui_->widget->scale;
    ui_->widget->scale = oldValue_;
    ui_->widget->scaleObject(result);
  }
};

}  // namespace s21

#endif  // COMMANDS_H
