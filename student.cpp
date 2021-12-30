#include "student.h"
#include "ui_student.h"
#include <iostream>

Student::Student(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Student)
{
    ui->setupUi(this);
}

Student::Student(QWidget *parent, QString name) :
    QDialog(parent),
    ui(new Ui::Student)
{
    ui->setupUi(this);
    Id = name;
    ui->label_3->setText(Id);
}


Student::~Student()
{
    delete ui;
}
