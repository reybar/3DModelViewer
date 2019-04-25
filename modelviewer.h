#ifndef MODELVIEWER_H
#define MODELVIEWER_H

#include <QMainWindow>

namespace Ui {
class ModelViewer;
}

class ModelViewer : public QMainWindow
{
    Q_OBJECT

public:
    explicit ModelViewer(QWidget *central = nullptr, QWidget *parent = nullptr);
    ~ModelViewer();

private:
    Ui::ModelViewer *ui;
};

#endif // MODELVIEWER_H
