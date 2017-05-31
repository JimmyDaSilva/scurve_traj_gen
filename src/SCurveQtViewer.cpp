#include "SCurveQtWidget.hpp"
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QMainWindow window;
  SCurveQtWidget *widget = new SCurveQtWidget();
  window.setCentralWidget(widget);
  window.setWindowState(Qt::WindowMaximized);
  window.show();
  return a.exec();
}