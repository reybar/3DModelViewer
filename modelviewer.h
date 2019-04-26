#ifndef MODELVIEWER_H
#define MODELVIEWER_H

#include <QMainWindow>
#include <Qt3DCore/QEntity>
#include <Qt3DRender/QCamera>
#include <Qt3DRender/QPointLight>
#include <Qt3DCore/QTransform>
#include <Qt3DWindow>
#include <QMainWindow>

#include <Qt3DExtras/QForwardRenderer>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QTorusMesh>

#include <QMouseEvent>
#include <QKeyEvent>
#include <QtGui>

#include <QTransform>


namespace Ui {
class ModelViewer;
}

class ModelViewer : public QMainWindow
{
    Q_OBJECT

public:
    explicit ModelViewer(QWidget *parent = nullptr);
    ~ModelViewer();

    void keyPressEvent(QKeyEvent *event);


private:
    Ui::ModelViewer *ui;

    void Camera(Qt3DExtras::Qt3DWindow *view);
    void KeyControls(QKeyEvent *event);

    Qt3DCore::QEntity *createScene();
    Qt3DCore::QEntity *model;
    Qt3DCore::QTransform *transform;

    QPoint m_lastPos;
};

#endif // MODELVIEWER_H
