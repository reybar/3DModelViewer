#include "modelviewer.h"
#include "ui_modelviewer.h"

ModelViewer::ModelViewer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ModelViewer)
{
    ui->setupUi(this);
}

ModelViewer::~ModelViewer()
{
    delete ui;
}
