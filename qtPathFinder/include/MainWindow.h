

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>

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

private slots:

    void loadFile();
    void saveFile();

    void about();

    void addStartLocation();
    void addEndLocation();
    void addDeathStar();

    void generate();
    void clear();

protected:
    void keyPressEvent(QKeyEvent* event) override;

private:


    void readSettings();

    void closeEvent(QCloseEvent* event) override;

    void createActions();
    void createMenus();
    void createToolbars();
    void createStatusBar();

    QMenu* m_fileMenu;
    QMenu* m_settingsMenu;
    QMenu* m_helpMenu;

    QAction* m_loadAction;
    QAction* m_saveAction;
    QAction* m_exitAction;
    QAction* m_aboutAction;
    QAction* m_aboutQtAction;
    QAction* m_orderAction;

    Ui::MainWindow* ui;
};

#endif // MAINWINDOW_H
