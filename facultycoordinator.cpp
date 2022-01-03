#include "facultycoordinator.h"
#include "ui_facultycoordinator.h"
#include <qmessagebox.h>
#include<QtGui>
#include <QDebug>
#include <iostream>
#include <cstring>
#include <sstream>
#include <string>


facultyCoordinator::facultyCoordinator(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::facultyCoordinator)
{
    ui->setupUi(this);
}

facultyCoordinator::facultyCoordinator(QString f_id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::facultyCoordinator)
{
    ui->setupUi(this);
    MYSQL_RES *res;
    MYSQL_ROW row = NULL;
    struct connection_details mysqlD;
    con = mysql_connection_setup(mysqlD);
    id = f_id;

    QStringListModel *model;
    model = new QStringListModel(this);
    QStringList list;

    mysql_query(con, "select dept_name from department");
    res = mysql_store_result(con);
    while((row = mysql_fetch_row(res)) != NULL){
        list<<row[0];
    }
    model->setStringList(list);
    ui->comboBox->setModel(model);
    ui->comboBox_2->setModel(model);
    ui->comboBox_3->setModel(model);

    mysql_free_result(res);
}

facultyCoordinator::~facultyCoordinator()
{
    delete ui;
    mysql_close(con);
}


void facultyCoordinator::on_pushButton_clicked()
{
    char course_id[20];
    char title[30];
    char dept[40];
    int credit;
    if(ui->lineEdit->text() == NULL){
       QMessageBox::information(this, "ID not entered", "ID field cannot be empty");
    }
    else if(ui->lineEdit_4->text() == NULL){
        QMessageBox::information(this, "Title not entered", "Title field cannot be empty");

    }
    QstringToCharArray(ui->lineEdit->text(), course_id);
    //std::cout<<course_id;
    QstringToCharArray(ui->lineEdit_4->text(), title);
    //std::cout<<title;
    QstringToCharArray(ui->comboBox->currentText(), dept);
    qDebug()<<ui->comboBox->currentText();
    std::cout<<"The department entered is "<<dept <<std::endl;
    credit = ui->lineEdit_6->text().toInt();

    std::ostringstream str;
    str<<"insert ignore into course values('" <<course_id <<"', '"
      << title <<"', '" <<dept <<"', " <<credit <<")";
    std::string query = str.str();
    //std::string query = "insert into course values('Eco222', 'Economics', 'History', 4)";
    //char query[] = "insert into course values('Eco222', 'Economics', 'History', 4)";
    //std::cout<<query;
    int res = mysql_query(con, query.c_str());

    if(res == 0){
        QMessageBox::information(this, "Success", "Course was successfully inserted");
        std::cout<<query;
    }
    else{
        std::cout<<query;
        QMessageBox::information(this, "failed", "Failed to insert new course");
    }
}


void facultyCoordinator::on_pushButton_3_clicked()
{
    char course_id[20];
    char title[30];
    char dept[40];
    double salary;
    if(ui->lineEdit_2->text() == NULL){
       QMessageBox::information(this, "ID not entered", "ID field cannot be empty");
    }
    else if(ui->lineEdit_7->text() == NULL){
        QMessageBox::information(this, "Name not entered", "Name field cannot be empty");

    }
    QstringToCharArray(ui->lineEdit_2->text(), course_id);
    QstringToCharArray(ui->lineEdit_7->text(), title);
    QstringToCharArray(ui->comboBox_2->currentText(), dept);
    salary = ui->lineEdit_9->text().toDouble();

    std::ostringstream str;
    str<<"insert ignore into instructor values('" <<course_id <<"', '"
      << title <<"', '" <<dept <<"', " <<salary <<")";
    std::string query = str.str();

    int res = mysql_query(con, query.c_str());

    if(res == 0){
        QMessageBox::information(this, "Success", "Instructor was successfully inserted");
        std::cout<<query;
    }
    else{
        std::cout<<query;
        QMessageBox::information(this, "failed", "Failed to insert new Instructor");
    }
}

void facultyCoordinator::on_pushButton_4_clicked()
{
    char course_id[20];
    char title[30];
    char dept[40];
    int tot_cred = 0;
    double cgpa = 0;
    if(ui->lineEdit_3->text() == NULL){
       QMessageBox::information(this, "ID not entered", "ID field cannot be empty");
    }
    else if(ui->lineEdit_10->text() == NULL){
        QMessageBox::information(this, "Name not entered", "Name field cannot be empty");

    }
    QstringToCharArray(ui->lineEdit_3->text(), course_id);
    QstringToCharArray(ui->lineEdit_10->text(), title);
    QstringToCharArray(ui->comboBox_2->currentText(), dept);
    tot_cred = ui->lineEdit_12->text().toInt();
    cgpa = ui->lineEdit_13->text().toDouble();

    std::ostringstream str;
    str<<"insert ignore into student values('" <<course_id <<"', '"
      << title <<"', '" <<dept <<"', " <<tot_cred <<", " <<cgpa <<")";
    std::string query = str.str();

    int res = mysql_query(con, query.c_str());

    if(res == 0){
        QMessageBox::information(this, "Success", "Student was successfully inserted");
        std::cout<<query;
    }
    else{
        std::cout<<query;
        QMessageBox::information(this, "failed", "Failed to insert new Student");
    }
}
