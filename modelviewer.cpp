#include "modelviewer.h"
#include "ui_modelviewer.h"

ModelViewer::ModelViewer(QWidget *parent) :
    QMainWindow (parent),
    ui(new Ui::ModelViewer)
{
    ui->setupUi(this);

    Qt3DExtras::Qt3DWindow *view = new Qt3DExtras::Qt3DWindow();
    QWidget *widget = QWidget::createWindowContainer(view);

    view->setRootEntity(startScene());
    view->defaultFrameGraph()->setClearColor(QColor(QRgb(0x42f4bc)));
    Camera(view);

    this->setCentralWidget(widget);
}

ModelViewer::~ModelViewer()
{
    delete ui;
}


void ModelViewer::keyPressEvent(QKeyEvent *event)
{
    KeyControls(event);
}

void ModelViewer::KeyControls(QKeyEvent *event){
    if (event->modifiers().testFlag(Qt::ControlModifier)){
        if(event->key()==Qt::Key_Up){
            transform->setRotationX(transform->rotationX()-5);
        }
        if(event->key()==Qt::Key_Down){
            transform->setRotationX(transform->rotationX()+5);
        }
        if(event->key()==Qt::Key_Left){
            transform->setRotationY(transform->rotationY()-5);
        }
        if(event->key()==Qt::Key_Right){
            transform->setRotationY(transform->rotationY()+5);
        }
    }else if (event->modifiers().testFlag(Qt::ShiftModifier)) {
        if(event->key()==Qt::Key_Up){
            transform->setTranslation(QVector3D(transform->translation().x(),transform->translation().y(),transform->translation().z()-2));
        }
        if(event->key()==Qt::Key_Down){
            transform->setTranslation(QVector3D(transform->translation().x(),transform->translation().y(),transform->translation().z()+2));
        }
    }else{
        if(event->key()==Qt::Key_Up){
            transform->setTranslation(QVector3D(transform->translation().x(),transform->translation().y()+2,transform->translation().z()));
        }
        if(event->key()==Qt::Key_Down){
            transform->setTranslation(QVector3D(transform->translation().x(),transform->translation().y()-2,transform->translation().z()));
        }
        if(event->key()==Qt::Key_Left){
            transform->setTranslation(QVector3D(transform->translation().x()-2,transform->translation().y(),transform->translation().z()));
        }
        if(event->key()==Qt::Key_Right){
            transform->setTranslation(QVector3D(transform->translation().x()+2,transform->translation().y(),transform->translation().z()));
        }
    }
}

void ModelViewer::Camera(Qt3DExtras::Qt3DWindow *view)
{
    Qt3DRender::QCamera *camera = view->camera();
    camera->lens()->setPerspectiveProjection(45.0f,16.0f/9.0f, 0.1f, 1000.0f);
    camera->setPosition(QVector3D(0, 0, 40));
    camera->setViewCenter(QVector3D(0, 0, 0));
}

Qt3DCore::QEntity *ModelViewer::startScene()
{
    Qt3DCore::QEntity *rootEntity = new Qt3DCore::QEntity();

    Qt3DRender::QMaterial *material = new Qt3DExtras::QPhongMaterial(rootEntity);
    model = new Qt3DCore::QEntity(rootEntity);
    Qt3DExtras::QTorusMesh *torusMesh = new Qt3DExtras::QTorusMesh;
    torusMesh->setRadius(5);
    torusMesh->setMinorRadius(1);
    torusMesh->setRings(100);
    torusMesh->setSlices(20);

    transform = new Qt3DCore::QTransform;
    transform->setScale3D(QVector3D(1, 1, 1));
    transform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(1, 0, 0), 0));


    Qt3DCore::QEntity *lightEntity = new Qt3DCore::QEntity(rootEntity);
    Qt3DRender::QPointLight *light = new Qt3DRender::QPointLight(lightEntity);
    light->setColor("red");
    light->setIntensity(1);
    lightEntity->addComponent(light);
    Qt3DCore::QTransform *lightTransform = new Qt3DCore::QTransform(lightEntity);
    lightTransform->setTranslation(QVector3D(0,0,40));
    lightEntity->addComponent(lightTransform);

    model->addComponent(torusMesh);
    model->addComponent(transform);
    model->addComponent(material);

    return rootEntity;

}

Qt3DCore::QEntity *ModelViewer::createScene(Qt3DRender::QMesh *mesh)
{
    Qt3DCore::QEntity *rootEntity = new Qt3DCore::QEntity();

    Qt3DRender::QMaterial *material = new Qt3DExtras::QPhongMaterial(rootEntity);
    model = new Qt3DCore::QEntity(rootEntity);

    transform = new Qt3DCore::QTransform;
    transform->setScale3D(QVector3D(1, 1, 1));
    transform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(1, 0, 0), 0));


    Qt3DCore::QEntity *lightEntity = new Qt3DCore::QEntity(rootEntity);
    Qt3DRender::QDirectionalLight *light = new Qt3DRender::QDirectionalLight(lightEntity);
    light->setColor("white");
    light->setIntensity(1);
    lightEntity->addComponent(light);
    Qt3DCore::QTransform *lightTransform = new Qt3DCore::QTransform(lightEntity);
    lightTransform->setTranslation(QVector3D(0,0,40));
    lightEntity->addComponent(lightTransform);

    model->addComponent(mesh);
    model->addComponent(transform);
    model->addComponent(material);

    return rootEntity;

}


void ModelViewer::on_actionOpen_File_triggered()
{
    QString filename= QFileDialog::getOpenFileName(this,"Open file");
    QFile file(filename);
    currentFile = filename;
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this,"Warning", "Cannot open "+file.errorString());
    }
    setWindowTitle(filename);
    Qt3DRender::QMesh *mesh = new Qt3DRender::QMesh();
    QUrl data =QUrl::fromLocalFile(filename);
    mesh->setSource(data);



    Qt3DExtras::Qt3DWindow *view = new Qt3DExtras::Qt3DWindow();
    QWidget *widget = QWidget::createWindowContainer(view);

    view->setRootEntity(createScene(mesh));
    view->defaultFrameGraph()->setClearColor(QColor(QRgb(0x42f4bc)));
    Camera(view);

    this->setCentralWidget(widget);
}
