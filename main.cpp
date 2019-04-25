#include "modelviewer.h"
#include <QApplication>

#include <Qt3DCore/QEntity>
#include <Qt3DRender/QCamera>
#include <Qt3DCore/QTransform>
#include <Qt3DWindow>
#include <QMainWindow>

#include <Qt3DExtras/QForwardRenderer>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QCylinderMesh>
#include <Qt3DExtras/QSphereMesh>
#include <Qt3DExtras/QTorusMesh>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Qt3DExtras::Qt3DWindow *view = new Qt3DExtras::Qt3DWindow();
    QWidget *widget = QWidget::createWindowContainer(view);

    ModelViewer *modelViewer =new ModelViewer(widget);

    Qt3DCore::QEntity *rootEntity = new Qt3DCore::QEntity();

    //camera
    Qt3DRender::QCamera *camera = view->camera();
    camera->lens()->setPerspectiveProjection(45.0f,16.0f/9.0f, 0.1f, 1000.0f);
    camera->setPosition(QVector3D(0, 0, 40));
    camera->setViewCenter(QVector3D(0, 0, 0));

    Qt3DRender::QMaterial *material = new Qt3DExtras::QPhongMaterial();
    Qt3DCore::QEntity *torusEntity = new Qt3DCore::QEntity(rootEntity);
    Qt3DExtras::QTorusMesh *torusMesh = new Qt3DExtras::QTorusMesh;
    torusMesh->setRadius(5);
    torusMesh->setMinorRadius(1);
    torusMesh->setRings(100);
    torusMesh->setSlices(20);

    Qt3DCore::QTransform *torusTransform = new Qt3DCore::QTransform;
    torusTransform->setScale3D(QVector3D(1, 1, 1));
    torusTransform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(1, 0, 0), 0));

    torusEntity->addComponent(torusMesh);
    torusEntity->addComponent(torusTransform);
    torusEntity->addComponent(material);

    view->defaultFrameGraph()->setClearColor(QColor(QRgb(0x42f4bc)));
    view->setRootEntity(rootEntity);

    modelViewer->show();

    return a.exec();
}
