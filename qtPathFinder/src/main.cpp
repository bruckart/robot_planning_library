

// #include "MainWindow.h"
// #include "MyOpenGLWidget.h"
// #include "MyWidget.h"

#include "MyGraphicsWidget.h"
// #include "MyGraphicsView.h"
#include "MainWindow.h"


#include <QApplication>
#include <QSurfaceFormat>

#include <stdio.h>
#include <stdlib.h>

#include <iostream>

int main(int argc, char* argv[])
{
    // Q_INIT_RESOURCE(helloscript);
    // Q_INIT_RESOURCE(application);

    std::clog << "Hello World" << std::endl;

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);

    QApplication app(argc, argv);
    app.setOrganizationName("");
    app.setApplicationName("Application Example");
    app.setApplicationVersion("1.0.0");

    // std::clog << "MyWidget create" << std::endl;
    // MyWidget mw;
    // mw.resize(800,600);
    // mw.show();
    // mw.setWindowTitle(
    //   QApplication::translate("top leve", 
    //                           "top level widget"));

#ifndef QT_NO_OPENGL
    // MyOpenGLWidget w;
    // w.setWindowTitle(QApplication::translate("qtOpenGl",
    //                  "qtOpenGL"));
    // w.show();



#else
    QLabel note("OpenGL Support required");
    note.show();
#endif

    MainWindow mainWindow;
    mainWindow.resize(800,600);
    mainWindow.show();

    // MyGraphicsWidget gw;
    // gw.resize(800,600);
    // gw.show();

    // MyGraphicsView view;
    // view.resize(800,600);
    // view.show();


    return app.exec();
}

