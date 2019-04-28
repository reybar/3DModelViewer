#include "modelviewer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ModelViewer *modelViewer =new ModelViewer();
    modelViewer->show();
    modelViewer->setWindowState(Qt::WindowMaximized);

    return a.exec();
}
