#include "modelviewer.h"
#include "ui_modelviewer.h"

ModelViewer::ModelViewer(QWidget *central,QWidget *parent) :
    QMainWindow (parent),
    ui(new Ui::ModelViewer)
{
    ui->setupUi(this);
    this->setCentralWidget(central);
}

ModelViewer::~ModelViewer()
{
    delete ui;
}
