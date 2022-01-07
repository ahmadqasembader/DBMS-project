#include "instructor.h"
#include "ui_instructor.h"
#include "databaseconnection.h"
#include <iostream>
#include <sstream>
#include <cstring>
#include <QString>
#include<QtGui>
#include <mysql/mysql.h>
#include <QAbstractItemModel>
#include <QStringList>
#include <QTableWidget>
#include <QTableWidgetItem>


Instructor::Instructor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Instructor)
{
    ui->setupUi(this);
}

Instructor::Instructor(QString i_id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Instructor)
{
    ui->setupUi(this);

    //database connection
    MYSQL *con = NULL;
    MYSQL_RES *res;
    MYSQL_ROW row = NULL;
    struct connection_details mysqlD;
    con = mysql_connection_setup(mysqlD);


    char inst_id[50];//current(logged in) instructor ID...
    QstringToCharArray(i_id, inst_id);
    std::ostringstream qry;

    // ======================================================== //
    //               Student Personal Details
    // ======================================================== //

    qry << "select * from instructor where ID = " << inst_id;
    res = mysql_execute_query(con, qry.str().c_str());
    row = mysql_fetch_row(res);

    //Inserting to the UI the perosnal data of instructor
    ui->label_3 ->setText(row[0]);
    ui->label_8->setText(row[1]);
    ui->label_4 ->setText(row[2]);
    mysql_free_result(res);


    // ======================================================== //
    //                      Assinged Courses
    // ======================================================== //




    //3 - queries, to fetch course_id, semester and the year in 3 separate queries
    // and store them in 3 differnet QStringList (container)
    //for converting from QStringList to QString later via a foreach (QString itm, QStringList obj)
    // they're stored as private data memebre in the .h file

    // query - 1 (course_id)
    qry.str("");
    qry.clear();
    qry << "select course_id from teaches where ID = \"" << inst_id << "\";";
    res = mysql_execute_query(con, qry.str().c_str());


    while((row = mysql_fetch_row(res)) != NULL){
        for(unsigned int i = 0; i < mysql_field_count(con); i++){
            for(unsigned int j = 0; j < mysql_num_rows(res); j++){
                course.insert(j, row[j]);
            }
        }
    }
    mysql_free_result(res);


    // query - 2 (semester)
    qry.str("");
    qry.clear();
    qry << "select semester from teaches where ID = \"" << inst_id << "\";";
    res = mysql_execute_query(con, qry.str().c_str());

    while((row = mysql_fetch_row(res)) != NULL){
        for(unsigned int i = 0; i < mysql_field_count(con); i++){
            for(unsigned int j = 0; j < mysql_num_rows(res); j++){
                semester.insert(j, row[j]);
            }
        }
    }
    mysql_free_result(res);


    // query - 3 (year)
    qry.str("");
    qry.clear();
    qry << "select year from teaches where ID = \"" << inst_id << "\";";
    res = mysql_execute_query(con, qry.str().c_str());

    while((row = mysql_fetch_row(res)) != NULL){
        for(unsigned int i = 0; i < mysql_field_count(con); i++){
            for(unsigned int j = 0; j < mysql_num_rows(res); j++){
                year.insert(j, row[j]);
            }
        }
    }
    mysql_free_result(res);


    //preparing the query
    std::ostringstream qry_2;
    qry_2.str() = "";
    qry.clear();
    qry_2 << "select course_id, sec_id, semester, year from teaches where ID = " << inst_id;
    res = mysql_execute_query(con, qry_2.str().c_str());

    while((row = mysql_fetch_row(res)) != NULL){
        QTableWidgetItem *item;

        //int row_num = mysql_num_rows(res);
        int col_num = mysql_field_count(con);

        int rowCount = 0, columnCount = 0;

        ui->courseAssignedTable->setColumnCount(col_num);
        ui->courseAssignedTable->insertRow(rowCount);

        //Adding the header of the table
        QStringList label;
        label << "Course Id" << "Group No" << "Semester" << "Year" << "Grade";
        ui->courseAssignedTable->setHorizontalHeaderLabels(label);
        //Dynamically allocating...
        for(unsigned int j = 0; j < mysql_field_count(con); j++){
            item = new QTableWidgetItem;

            //chagne table's cell to be read-only
            item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);

            //the acutall inserting for data into the table
            item->setText(row[j]);

            ui->courseAssignedTable->setItem(rowCount, columnCount, item);

            //Resize rows, columns, and the table to fit content
            ui->courseAssignedTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            ui->courseAssignedTable->resizeColumnsToContents();
            ui->courseAssignedTable->resizeRowsToContents();

            columnCount++;
        }
        rowCount++;
    }
    //mysql_free_result(res);




    // ======================================================== //
    //                      Courses Destails
    // ======================================================== //


    foreach(QString itm, course ){
        //for converting from QString to char*
        //since mysql_query() accepts only char*
        char temp_course[200];
        char temp_semester[200];
        char temp_year[200];

        QstringToCharArray(itm, temp_course);

        foreach(QString itm_2, semester)
            QstringToCharArray(itm_2, temp_semester);
        foreach(QString itm_3, year)
            QstringToCharArray(itm_3, temp_year);

        //preparing a query...
        std::ostringstream qry_3;
        qry_3 << "select student.name, student.ID, course_id, semester, year from takes, student "
              << "where student.ID = takes.ID and course_id = \"" << temp_course
              << "\" and semester = \"" << temp_semester << "\" and year = \"" << temp_year << "\";";

        res = mysql_execute_query(con, qry_3.str().c_str());

        while((row = mysql_fetch_row(res)) != NULL){
            //creating a table
            QTableWidgetItem *item;

            int col_num = mysql_field_count(con);
            int rowCount = 0, columnCount = 0;

            //assign number of rows and columns dynamically
            ui->courseInfoTable->setColumnCount(col_num);
            ui->courseInfoTable->insertRow(rowCount);

            //Adding the header of the table
            QStringList label_2;
            label_2 << "Name" << "Student No" << "Course Id" << "Semester" << "Year";
            ui->courseInfoTable->setHorizontalHeaderLabels(label_2);

            //inserting into the QTableWidget automatically...
            for(unsigned int j = 0; j < mysql_field_count(con); j++){
                item = new QTableWidgetItem;

                //chagne table's cell to be read-only
                item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);

                //the acutall inserting for data into the table
                item->setText(row[j]);
                ui->courseInfoTable->setItem(rowCount, columnCount, item);

                //Resize rows, columns, and the table to fit content
                ui->courseInfoTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
                ui->courseInfoTable->resizeColumnsToContents();
                ui->courseInfoTable->resizeRowsToContents();

                columnCount++;
            }
            rowCount++;
        }
    }
}

Instructor::~Instructor()
{
    delete ui;
}
