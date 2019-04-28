#ifndef SCENE_H
#define SCENE_H

#include <QObject>
#include <QWidget>

#include <Qt3DCore/QEntity>
#include <Qt3DRender/QCamera>
#include <Qt3DRender/QPointLight>
#include <Qt3DRender/QDirectionalLight>
#include <Qt3DCore/QTransform>
#include <Qt3DWindow>

#include <Qt3DExtras/QForwardRenderer>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QTorusMesh>

#include <QKeyEvent>
#include <QTransform>
#include <QMesh>

class Scene : public QObject
{
    Q_OBJECT
public:
    explicit Scene(Qt3DExtras::Qt3DWindow *, QObject *parent=nullptr);

    void NewScene(Qt3DRender::QMesh *);
    void KeyControls(QKeyEvent *event);


public slots:
    void LightXChanged(int angle);
    void LightYChanged(int angle);
    void LightZChanged(int angle);

private:
    Qt3DCore::QEntity *rootEntity;
    Qt3DCore::QEntity *model;
    Qt3DCore::QTransform *transform;
    Qt3DRender::QDirectionalLight *light;

    void StartScene();
    void Camera(Qt3DExtras::Qt3DWindow *view);
    void SetupMesh(Qt3DRender::QMesh *mesh);
    void SetupTransform();
    void SetupMaterial();
    void SetupLighting();
};

#endif // SCENE_H
