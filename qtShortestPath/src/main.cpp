

#include <QApplication>

#include "MyGrid.h"


int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    app.setOrganizationName("");
    app.setApplicationName("qtShortestPath");
    app.setApplicationVersion("1.0.0");

    std::clog << "spacebar to iterate through the algorithm" << std::endl;

    MyGrid w;
    w.show();

    return app.exec();
}
