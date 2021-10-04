



#include "MainWindow.h"
#include "ui_MainWindow.h"

// #include "ObstacleItem.h"

#include <QSettings>
#include <QMessageBox>
#include <QRandomGenerator>
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

    ui->m_addStartLocButton->setIcon(QPixmap(":/start.png"));
    ui->m_addStartLocButton->setToolTip(QString("Add Start Location Identifier"));

    // ui->m_remStartLocButton->setIcon(QPixmap(":/rando.png"));
    // ui->m_addStartLocButton->setToolTip(QString("Remove Start Location Identifier"));

    ui->m_addEndLocButton->setIcon(QPixmap(":/end.png"));
    ui->m_addEndLocButton->setToolTip(QString("Add End Location Identifier"));

    // ui->m_remEndLocButton->setIcon(QPixmap(":/rando.png"));
    // ui->m_remEndLocButton->setToolTip(QString("Remove End Location Identifier"));

    ui->m_addObsButton->setIcon(QPixmap(":/obs.png"));
    ui->m_addObsButton->setToolTip(QString("Add Obstacle"));

    // ui->m_remObsButton->setIcon(QPixmap(":/rando.png"));
    // ui->m_remObsButton->setToolTip(QString("Remove Obstacle"));

    connect(ui->m_ownshipRadius, SIGNAL(valueChanged(double)),
            ui->m_graphicsWidget, SLOT(updateOwnshipRadius(double)));


    connect(ui->m_addStartLocButton, SIGNAL(clicked()),
            this, SLOT(addStartLocation()));

    connect(ui->m_addEndLocButton, SIGNAL(clicked()),
            this, SLOT(addEndLocation()));
    
    // Obstacles
    connect(ui->m_addObsButton, SIGNAL(clicked()),
            this, SLOT(addObstacle()));


    // When the reset button is selected, return all the
    // options to default.
    connect(ui->m_clearButton, SIGNAL(clicked()), 
            this, SLOT(clear()));

    connect(ui->m_generateButton, SIGNAL(clicked()), 
            this, SLOT(generate()));


    // Update the scene if the map size is changed.
    connect(ui->m_mapWidth, SIGNAL(valueChanged(int)),
            ui->m_graphicsWidget, SLOT(updateSceneWidth(int)));

    connect(ui->m_mapHeight, SIGNAL(valueChanged(int)),
            ui->m_graphicsWidget, SLOT(updateSceneHeight(int)));



    // If the map bounds is changed, it's possible that
    // the start and end locations and obstacles could be out of bounds.

    // Set the initial scene size.
    ui->m_graphicsWidget->updateSceneSize(ui->m_mapWidth->value(),
                                          ui->m_mapHeight->value());

    // qApp->setStyleSheet("QGroupBox {  border: 1px solid gray;}");

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
    std::clog << "MainWindow::createActions()" << std::endl;

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

    m_aboutAction = new QAction(tr("&About"), this);
    m_aboutAction->setStatusTip(tr("Show the application's About dialog"));
    connect(m_aboutAction, SIGNAL(triggered()), this, SLOT(about()));

    m_aboutQtAction = new QAction(tr("About &Qt"), this);
    m_aboutQtAction->setStatusTip(tr("Show the Qt library's About box."));
    connect(m_aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

}
void MainWindow::createMenus()
{
    std::clog << "MainWindow::createMenus()" << std::endl;

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
    std::clog << "MainWindow::generateRandomStartLoc()" << std::endl;

    // int mapWidthMax = ui->m_mapWidth->value();
    // int mapHeightMax = ui->m_mapHeight->value();
    // int mapWidthMin = ui->m_mapWidth->minimum();
    // int mapHeightMin = ui->m_mapHeight->minimum();

    // int randomX = (int) QRandomGenerator::global()->bounded(mapWidthMin, mapWidthMax);
    // int randomY = (int) QRandomGenerator::global()->bounded(mapHeightMin, mapHeightMax);

    // ui->m_startLocX->setValue(randomX);
    // ui->m_startLocY->setValue(randomY);
    // ui->m_graphicsWidget->addStartLocation(randomX, randomY, ui->m_ownshipRadius->value());

    statusBar()->showMessage(QString("Adding Start location at (0,0)"), 3000);
    ui->m_graphicsWidget->addStartLocation(0, 0, ui->m_ownshipRadius->value());

    // Disable the Add button.
    // ui->m_addStartLocButton->setEnabled(false);
    // ui->m_remStartLocButton->setEnabled(true);
}

void MainWindow::removeStartLocation()
{
    std::clog << "MainWindow::removeStartLocation()" << std::endl;

    ui->m_graphicsWidget->removeStartLocation();
    // ui->m_addStartLocButton->setEnabled(true);
    // ui->m_remStartLocButton->setEnabled(true);
}

void MainWindow::addEndLocation()
{
    std::clog << "MainWindow::addEndLocation()" << std::endl;

    // int mapWidthMax = ui->m_mapWidth->value();
    // int mapHeightMax = ui->m_mapHeight->value();
    // int mapWidthMin = ui->m_mapWidth->minimum();
    // int mapHeightMin = ui->m_mapHeight->minimum();

    // int randomX = (int) QRandomGenerator::global()->bounded(mapWidthMin, mapWidthMax);
    // int randomY = (int) QRandomGenerator::global()->bounded(mapHeightMin, mapHeightMax);

    // ui->m_endLocX->setValue(randomX);
    // ui->m_endLocY->setValue(randomY);
    // ui->m_graphicsWidget->addEndLocation(randomX, randomY, ui->m_ownshipRadius->value());
    
    // if the radius of the ownship end position does not match
    // the start position, then return



    statusBar()->showMessage(QString("Adding End location at (0,0)"), 3000);
    ui->m_graphicsWidget->addEndLocation(0, 0, ui->m_ownshipRadius->value());

    // ui->m_addEndLocButton->setEnabled(false);
    // ui->m_remEndLocButton->setEnabled(true);
}

void MainWindow::removeEndLocation()
{
    std::clog << "MainWindow::removeEndLocation()" << std::endl;

    // ui->m_graphicsWidget->remEndLocation(randomX, randomY, ui->m_ownshipRadius->value());
    ui->m_graphicsWidget->removeEndLocation();
    // ui->m_addEndLocButton->setEnabled(true);
    // ui->m_remEndLocButton->setEnabled(false);
}

void MainWindow::addObstacle()
{
    std::clog << "MainWindow::addObstacle()" << std::endl;
    statusBar()->showMessage(QString("Adding Obstacle at (0,0)"), 3000);

    ui->m_graphicsWidget->addObstacle(0, 0, ui->m_obstacleRadius->value());
}

void MainWindow::removeObstacle()
{
    std::clog << "MainWindow::removeObstacle()" << std::endl;

}

void MainWindow::generate()
{
    statusBar()->showMessage(QString("Generating Path"), 3000);
    ui->m_graphicsWidget->generate();

}

void MainWindow::clear()
{
    statusBar()->showMessage(QString("Clearing Scene"), 3000);
    ui->m_graphicsWidget->clear();
}

void MainWindow::loadFile()
{
    std::clog << "MainWindow::loadFile()" << std::endl;

    QString fn = QFileDialog::getOpenFileName(
        this,
        tr("Specify PathFinder File"), 
        QDir::homePath(),
        tr("PathFinder Files (*.pf)"));

    std::clog << "fileName=" << fn.toStdString() << std::endl;

    statusBar()->showMessage(QString("Loading file: " + fn), 3000);


    ui->m_graphicsWidget->loadFile(fn);
}

void MainWindow::saveFile()
{
    std::clog << "MainWindow::saveFile()" << std::endl;

    QString fn = QFileDialog::getOpenFileName(
        this,
        tr("Specify PathFinder File"), 
        QDir::homePath(),
        tr("PathFinder Files (*.pf)"));

    statusBar()->showMessage(QString("Saving file: " + fn), 3000);



    std::clog << "fileName=" << fn.toStdString() << std::endl;


    ui->m_graphicsWidget->saveFile(fn);
}

