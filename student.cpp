#include "student.h"
#include "ui_student.h"
#include <iostream>

Student::Student(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Student)
{
    ui->setupUi(this);
    //Id = username;

    ui->std_name->setText("Hello");

}


Student::~Student()
{
    delete ui;
}
