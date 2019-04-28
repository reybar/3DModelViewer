#include "scene.h"
#include "modelviewer.h"

Scene::Scene(Qt3DExtras::Qt3DWindow *view, QObject *parent) : QObject (parent)
{
    rootEntity = new Qt3DCore::QEntity();
    view->setRootEntity(rootEntity);
    view->defaultFrameGraph()->setClearColor(QColor(QRgb(0x42f4bc)));
    Camera(view);
    StartScene();

}

void Scene::Camera(Qt3DExtras::Qt3DWindow *view)
{
    Qt3DRender::QCamera *camera = view->camera();
    camera->lens()->setPerspectiveProjection(45.0f,16.0f/9.0f, 0.1f, 1000.0f);
    camera->setPosition(QVector3D(0, 0, 40));
    camera->setViewCenter(QVector3D(0, 0, 0));
}

void Scene::StartScene()
{
    model = new Qt3DCore::QEntity(rootEntity);

    Qt3DExtras::QTorusMesh *torusMesh = new Qt3DExtras::QTorusMesh(model);
    torusMesh->setRadius(5);
    torusMesh->setMinorRadius(1);
    torusMesh->setRings(100);
    torusMesh->setSlices(20);
    model->addComponent(torusMesh);

    SetupTransform();
    SetupMaterial();
    SetupLighting();

}

void Scene::NewScene(Qt3DRender::QMesh *mesh)
{
    delete model;
    model = new Qt3DCore::QEntity(rootEntity);

    SetupMesh(mesh);
    SetupTransform();
    SetupMaterial();
    SetupLighting();
}

void Scene::SetupMesh(Qt3DRender::QMesh *mesh)
{
    model->addComponent(mesh);
}

void Scene::SetupTransform()
{
    transform = new Qt3DCore::QTransform(model);
    transform->setScale3D(QVector3D(1, 1, 1));
    transform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(1, 0, 0), 0));
    model->addComponent(transform);
}

void Scene::SetupMaterial()
{
    Qt3DRender::QMaterial *material = new Qt3DExtras::QPhongMaterial(model);
    model->addComponent(material);
}

void Scene::SetupLighting()
{
    Qt3DCore::QEntity *lightEntity = new Qt3DCore::QEntity(rootEntity);
    light = new Qt3DRender::QDirectionalLight(lightEntity);
    light->setColor("white");
    light->setIntensity(1);
    light->setWorldDirection(QVector3D(0,0,-1));

    lightEntity->addComponent(light);
}

void Scene::KeyControls(QKeyEvent *event){
    if (event->modifiers().testFlag(Qt::ControlModifier)){
        if(event->key()==Qt::Key_Up){
            transform->setRotationX(transform->rotationX()-6);
        }
        if(event->key()==Qt::Key_Down){
            transform->setRotationX(transform->rotationX()+6);
        }
        if(event->key()==Qt::Key_Left){
            transform->setRotationY(transform->rotationY()-6);
        }
        if(event->key()==Qt::Key_Right){
            transform->setRotationY(transform->rotationY()+6);
        }
    }else if (event->modifiers().testFlag(Qt::ShiftModifier)) {
        if(event->key()==Qt::Key_Up){
            transform->setTranslation(QVector3D(transform->translation().x(),transform->translation().y(),transform->translation().z()-1));
        }
        if(event->key()==Qt::Key_Down){
            transform->setTranslation(QVector3D(transform->translation().x(),transform->translation().y(),transform->translation().z()+1));
        }
    }else{
        if(event->key()==Qt::Key_Up){
            transform->setTranslation(QVector3D(transform->translation().x(),transform->translation().y()+1,transform->translation().z()));
        }
        if(event->key()==Qt::Key_Down){
            transform->setTranslation(QVector3D(transform->translation().x(),transform->translation().y()-1,transform->translation().z()));
        }
        if(event->key()==Qt::Key_Left){
            transform->setTranslation(QVector3D(transform->translation().x()-1,transform->translation().y(),transform->translation().z()));
        }
        if(event->key()==Qt::Key_Right){
            transform->setTranslation(QVector3D(transform->translation().x()+1,transform->translation().y(),transform->translation().z()));
        }
    }
}

void Scene::LightXChanged(int angle)
{
    light->setWorldDirection(QVector3D(angle,light->worldDirection().y(),light->worldDirection().z()));
}

void Scene::LightYChanged(int angle)
{
    light->setWorldDirection(QVector3D(light->worldDirection().x(),angle,light->worldDirection().z()));
}

void Scene::LightZChanged(int angle)
{
    light->setWorldDirection(QVector3D(light->worldDirection().x(),light->worldDirection().y(),angle));
}
