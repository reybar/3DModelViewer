#ifndef MODELVIEWER_H
#define MODELVIEWER_H

#include <QMainWindow>
#include <Qt3DCore/QEntity>
#include <Qt3DRender/QCamera>
#include <Qt3DRender/QPointLight>
#include <Qt3DRender/QDirectionalLight>
#include <Qt3DCore/QTransform>
#include <Qt3DWindow>
#include <QMainWindow>

#include <Qt3DExtras/QForwardRenderer>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QTorusMesh>

#include <QMouseEvent>
#include <QKeyEvent>
#include <QTransform>

#include <QFile>
#include <QFileDialog>
#include <QString>
#include <QMessageBox>
#include <QMesh>
#include <QUrl>


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


private slots:
    void on_actionOpen_File_triggered();

private:
    Ui::ModelViewer *ui;

    void Camera(Qt3DExtras::Qt3DWindow *view);
    void KeyControls(QKeyEvent *event);

    Qt3DCore::QEntity *startScene();
    Qt3DCore::QEntity *createScene(Qt3DRender::QMesh *mesh);
    Qt3DCore::QEntity *model;
    Qt3DCore::QTransform *transform;

    QString currentFile = "";
};

#endif // MODELVIEWER_H
