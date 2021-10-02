

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>

namespace Ui
{
  class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent=0);

    virtual ~MainWindow() override;

private:
    Ui::MainWindow* ui;

};

#endif // MAINWINDOW_H
