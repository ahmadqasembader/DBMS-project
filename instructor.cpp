#include "instructor.h"
#include "ui_instructor.h"

Instructor::Instructor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Instructor)
{
    ui->setupUi(this);
}

Instructor::~Instructor()
{
    delete ui;
}