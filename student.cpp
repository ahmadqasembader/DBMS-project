#include "student.h"
#include "ui_student.h"
#include <iostream>

Student::Student(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Student)
{
    ui->setupUi(this);
}

Student::Student(QWidget *parent, QString s_id) :
    QDialog(parent),
    ui(new Ui::Student)
{
    ui->setupUi(this);
    id = s_id;
    ui->label_3->setText(id);
}

Student::~Student()
{
    delete ui;
}
