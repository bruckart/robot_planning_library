



#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QSettings>
#include <QMessageBox>
// #include <QRandomGenerator>
#include <QFileDialog>


#include <iostream>


MainWindow::MainWindow(QWidget* parent)
:
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    createActions();
    createMenus();
    // createToolbars();
    createStatusBar();

    ui->m_addBb8Start->setIcon(QPixmap(":/bb8.jpg"));
    ui->m_addBb8Start->setToolTip(QString("Add BB-8 Start Location"));

    ui->m_addBb8End->setIcon(QPixmap(":/earth.png"));
    ui->m_addBb8End->setToolTip(QString("Add BB-8 End Location"));

    ui->m_addDeathStarButton->setIcon(QPixmap(":/deathstar.png"));
    ui->m_addDeathStarButton->setToolTip(QString("Add Death Star"));

    // connect(ui->m_ownshipRadius, SIGNAL(valueChanged(double)),
    //         ui->m_graphicsWidget, SLOT(updateOwnshipRadius(double)));


    connect(ui->m_addBb8Start, SIGNAL(clicked()),
            this, SLOT(addStartLocation()));

    connect(ui->m_addBb8End, SIGNAL(clicked()),
            this, SLOT(addEndLocation()));
    
    // Obstacles
    connect(ui->m_addDeathStarButton, SIGNAL(clicked()),
            this, SLOT(addDeathStar()));


    // When the reset button is selected, return all the
    // options to default.
    connect(ui->m_clearButton, SIGNAL(clicked()), 
            this, SLOT(clear()));

    connect(ui->m_generateButton, SIGNAL(clicked()), 
            this, SLOT(generate()));


    // Update the scene if the map size is changed.
    connect(ui->m_mapWidth, SIGNAL(valueChanged(int)),
            ui->m_graphicsView, SLOT(updateSceneWidth(int)));

    connect(ui->m_mapHeight, SIGNAL(valueChanged(int)),
            ui->m_graphicsView, SLOT(updateSceneHeight(int)));


    setWindowTitle(tr("qtPathFinder"));

    readSettings();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About Application"),
        tr("qtPathFinder facilitates the planning and performance of the PathFinder library."));
}

void MainWindow::createActions()
{
    m_loadAction = new QAction(tr("&Load"), this);
    m_loadAction->setShortcut(tr("Ctrl-L"));
    m_loadAction->setStatusTip(tr("Load the PathFinder scene."));
    connect(m_loadAction, SIGNAL(triggered()),
            this, SLOT(loadFile()));

    m_saveAction = new QAction(tr("&Save"), this);
    m_saveAction->setShortcut(tr("Ctrl-S"));
    m_saveAction->setStatusTip(tr("Save the PathFinder Scene"));
    connect(m_saveAction, SIGNAL(triggered()),
            this, SLOT(saveFile()));

    m_exitAction = new QAction(tr("E&xit"), this);
    m_exitAction->setShortcut(tr("Ctrl-Q"));
    m_exitAction->setStatusTip(tr("Exit the application"));
    connect(m_exitAction, SIGNAL(triggered()), this, SLOT(close()));

    m_orderAction = new QAction(tr("&Execute Order 66"), this);
    m_orderAction->setStatusTip(tr("Execute Order 66"));
    m_orderAction->setEnabled(false);
    // connect(m_aboutAction, SIGNAL(triggered()), this, SLOT(about()));


    m_aboutAction = new QAction(tr("&About"), this);
    m_aboutAction->setStatusTip(tr("Show the application's About dialog"));
    connect(m_aboutAction, SIGNAL(triggered()), this, SLOT(about()));

    m_aboutQtAction = new QAction(tr("About &Qt"), this);
    m_aboutQtAction->setStatusTip(tr("Show the Qt library's About box."));
    connect(m_aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

}
void MainWindow::createMenus()
{
    m_fileMenu = menuBar()->addMenu(tr("&File"));

    m_fileMenu->addAction(m_loadAction);
    m_fileMenu->addAction(m_saveAction);
    m_fileMenu->addAction(m_exitAction);

    // m_settingsMenu = menuBar()->addMenu(tr("&Settings"));
    // m_settingsMenu->addAction()
    // m_settingsMenu->addAction()

    m_helpMenu = menuBar()->addMenu(tr("&Help"));
    m_helpMenu->addAction(m_aboutAction);
    m_helpMenu->addAction(m_aboutQtAction);
    m_helpMenu->addAction(m_orderAction);
}

void MainWindow::createToolbars()
{
}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    switch (event->key())
    {
        case Qt::Key_Escape:
            close();
            break;
        default:
            QMainWindow::keyPressEvent(event);
    }
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    QSettings settings("shield.ai", "qtPathFinder");
    
    // Geometry
    settings.setValue("geometry", saveGeometry());
    settings.setValue("windowState", saveState());
}

void MainWindow::readSettings()
{
    QSettings settings("shield.ai", "qtPathFinder");

    this->restoreGeometry(settings.value("geometry").toByteArray());
    this->restoreState(settings.value("windowState").toByteArray());
}

void MainWindow::addStartLocation()
{
    statusBar()->showMessage(QString("Adding BB-8 Start Location at (0,0)"), 3000);
    ui->m_graphicsView->addStartLocation(0, 0, ui->m_ownshipRadius->value());

}

void MainWindow::addEndLocation()
{
    statusBar()->showMessage(QString("Adding BB-8 End location at (0,0)"), 3000);
    ui->m_graphicsView->addEndLocation(0, 0, ui->m_ownshipRadius->value());
}

void MainWindow::addDeathStar()
{
    statusBar()->showMessage(QString("Adding a Death Star at (0,0)"), 3000);

    ui->m_graphicsView->addDeathStar(0, 0, ui->m_deathstarRadius->value());  
}

void MainWindow::generate()
{
    statusBar()->showMessage(QString("Generating Path"), 3000);
    ui->m_graphicsView->generatePath();
}

void MainWindow::clear()
{
    statusBar()->showMessage(QString("Clearing Scene"), 3000);
    ui->m_graphicsView->clear();
}

void MainWindow::loadFile()
{
    QString fn = QFileDialog::getOpenFileName(
        this,
        tr("Specify PathFinder File"), 
        QDir::homePath(),
        tr("PathFinder Files (*.pf)"));

    std::clog << "fileName=" << fn.toStdString() << std::endl;

    statusBar()->showMessage(QString("Loading file: " + fn), 3000);


    ui->m_graphicsView->loadFile(fn);
}

void MainWindow::saveFile()
{
    QString fn = QFileDialog::getOpenFileName(
        this,
        tr("Specify PathFinder File"), 
        QDir::homePath(),
        tr("PathFinder Files (*.pf)"));

    statusBar()->showMessage(QString("Saving file: " + fn), 3000);

    std::clog << "fileName=" << fn.toStdString() << std::endl;

    ui->m_graphicsView->saveFile(fn);
}

