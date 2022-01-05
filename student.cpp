#include "student.h"
#include "ui_student.h"
#include "databaseconnection.h"
#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
#include <QString>
#include <QtGui>
#include <QLabel>
#include <qlabel.h>
#include <QDialog>
#include <QAbstractItemModel>
#include <QDebug>
#include <QStringList>
#include <QTableWidget>
#include <QTableWidgetItem>

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
    //MySQL connection
    MYSQL *con = NULL;
    MYSQL_RES *res;
    MYSQL_ROW row = NULL;
    struct connection_details mysqlD;
    con = mysql_connection_setup(mysqlD);

    ui->setupUi(this);

    char std_id[50];
    QstringToCharArray(s_id, std_id);

    // ======================================================== //
    //               Student Personal Details
    // ======================================================== //

    char qry[200];
    //preparing the query
    strcpy(qry, "select * from student where id = ");
    strcat(qry, std_id);

    mysql_query(con,  qry);
    res = mysql_store_result(con);

    while((row = mysql_fetch_row(res)) != NULL){
        for(int i = 0; i < mysql_field_count(con); i++){
            ui->label_11->setText(row[0]);
            ui->label_3->setText(row[1]);
            ui->label_4->setText(row[2]);
            ui->label_16->setText(row[3]);
            ui->label_14->setText(row[4]);
            ui->label_4->adjustSize();
        }
    }

    mysql_free_result(res);



    // ======================================================== //
    //               Student Course Registered
    // ======================================================== //

    //preparing the query
    strcpy(qry, "select course_id, sec_id, semester, year, grade from takes where ID = ");
    strcat(qry, std_id);

    mysql_query(con,  qry);
    res = mysql_store_result(con);

    while((row = mysql_fetch_row(res)) != NULL){
        QTableWidgetItem *item;

        int row_num = mysql_num_rows(res);
        int col_num = mysql_field_count(con);

        int rowCount = 0, columnCount = 0;

        ui->tableWidget->setColumnCount(col_num);
        ui->tableWidget->insertRow(rowCount);

        //Adding the header of the table
        QStringList label;
        label << "Course Id" << "Group No" << "Semester" << "Year" << "Grade";
        ui->tableWidget->setHorizontalHeaderLabels(label);
        //Dynamically allocating...
        for(unsigned int j = 0; j < mysql_field_count(con); j++){
            item = new QTableWidgetItem;
            item->setText(row[j]);
            ui->tableWidget->setItem(rowCount, columnCount, item);

            //Resize rows, columns, and the table to fit content
            ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            ui->tableWidget->resizeColumnsToContents();
            ui->tableWidget->resizeRowsToContents();

            columnCount++;
        }
        rowCount++;
    }
    mysql_free_result(res);


    // ======================================================== //
    //               Student Registered in Class
    // ======================================================== //
    strcpy(qry, "select course_id from takes where ID = ");
    strcat(qry, std_id);
    mysql_query(con,  qry);
    res = mysql_store_result(con);


    QStringList course;

    while((row = mysql_fetch_row(res)) != NULL){
        for(unsigned int i = 0; i < mysql_field_count(con); i++){
            course.insert(i, row[i]);
        }

    }
    mysql_free_result(res);


    foreach(QString itm, course){
        char temp[200];
        QstringToCharArray(itm, temp);

        strcpy(qry, "select student.name, takes.ID, course_id from student, takes "
                    "where student.ID = takes.ID and course_id = \"");
        strcat(qry, temp);
        strcat(qry, "\";");

        //query start...
        mysql_query(con,  qry);
        res = mysql_store_result(con);

        //Adding the header of the table
        QStringList label;
        label << "Name" << "Student No" << "Course Id";
        ui->tableWidget_2->setHorizontalHeaderLabels(label);

        while((row = mysql_fetch_row(res)) != NULL){
            QTableWidgetItem *item;

            int row_num = mysql_num_rows(res);
            int col_num = mysql_field_count(con);

            int rowCount = 0, columnCount = 0;

            ui->tableWidget_2->setColumnCount(col_num);
            ui->tableWidget_2->insertRow(rowCount);

            for(unsigned int j = 0; j < mysql_field_count(con); j++){
                item = new QTableWidgetItem;
                item->setText(row[j]);
                ui->tableWidget_2->setItem(rowCount, columnCount, item);

                //Resize rows, columns, and the table to fit content
                ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
                ui->tableWidget_2->resizeColumnsToContents();
                ui->tableWidget_2->resizeRowsToContents();

                columnCount++;
            }
            rowCount++;
        }
    }

}

Student::~Student()
{
    delete ui;
}
