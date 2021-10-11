

// #include "MainWindow.h"
// #include "MyOpenGLWidget.h"
// #include "MyWidget.h"

// #include "MyGraphicsView.h"
// #include "MyGraphicsView.h"
#include "MainWindow.h"


#include <QApplication>
// #include <QSurfaceFormat>
#include <QSplashScreen>
#include <QThread>

#include <stdio.h>
#include <stdlib.h>

#include <iostream>

int main(int argc, char* argv[])
{
    // Q_INIT_RESOURCE(helloscript);
    // Q_INIT_RESOURCE(application);

    // QSurfaceFormat format;
    // format.setDepthBufferSize(24);
    // QSurfaceFormat::setDefaultFormat(format);

    QApplication app(argc, argv);
    app.setOrganizationName("");
    app.setApplicationName("Application Example");
    app.setApplicationVersion("1.0.0");

	QPixmap pixmap(":/splashscreen.jpg");
	QSplashScreen splash(pixmap);
	splash.show();

	app.thread()->sleep(1); // wait for just 1 second and then show main window
	app.processEvents();

#ifndef QT_NO_OPENGL
    MainWindow mainWindow;
    mainWindow.resize(800,600);
    mainWindow.show();
	splash.finish(&mainWindow);
#else
    QLabel note("OpenGL Support required");
    note.show();
#endif

    return app.exec();
}

