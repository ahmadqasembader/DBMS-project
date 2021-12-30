#include "facultycoordinator.h"
#include "ui_facultycoordinator.h"

facultyCoordinator::facultyCoordinator(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::facultyCoordinator)
{
    ui->setupUi(this);
}

facultyCoordinator::facultyCoordinator(QString id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::facultyCoordinator)
{
    sId = id;
    ui->setupUi(this);
}

facultyCoordinator::~facultyCoordinator()
{
    delete ui;
}

