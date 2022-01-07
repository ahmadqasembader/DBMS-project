#include "student.h"
#include "ui_student.h"
#include "databaseconnection.h"
#include <iostream>
#include <sstream>
#include <cstring>
#include <QString>
#include <QLabel>
#include <QDialog>
#include <QAbstractItemModel>
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
    //set up MySQL connection...
    MYSQL *con = NULL;
    MYSQL_RES *res;
    MYSQL_ROW row = NULL;
    struct connection_details mysqlD;
    con = mysql_connection_setup(mysqlD);

    ui->setupUi(this);
    std::ostringstream qry;
    char std_id[50];//current(logged in) student ID...
    QstringToCharArray(s_id, std_id);

    // ======================================================== //
    //               Student Personal Details
    // ======================================================== //


    //preparing the query

    qry << "select * from student where ID = \"" << std_id << "\"";

    res = mysql_execute_query(con, qry.str().c_str());

    while((row = mysql_fetch_row(res)) != NULL){
        for(unsigned int i = 0; i < mysql_field_count(con); i++){
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
    qry.str("");
    qry << "select course_id, sec_id, semester, year, grade from takes where ID = \"" << std_id << "\";";

    res = mysql_execute_query(con, qry.str().c_str());


    while((row = mysql_fetch_row(res)) != NULL){

        //int row_num = mysql_num_rows(res);
        int col_num = mysql_field_count(con);

        int rowCount = 0, columnCount = 0;

        //Creating a table
        QTableWidgetItem *item;

        ui->tableWidget->setColumnCount(col_num);
        ui->tableWidget->insertRow(rowCount);

        //Adding the header of the table
        QStringList label;
        label << "Course Id" << "Group No" << "Semester" << "Year" << "Grade";
        ui->tableWidget->setHorizontalHeaderLabels(label);

        //Dynamically allocating...
        for(unsigned int j = 0; j < mysql_field_count(con); j++){
            item = new QTableWidgetItem;

            //chagne table's cell to be read-only
            item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
            //the acutall inserting for data into the table
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


    //3 - queries, to fetch course_id, semester and the year in 3 separate queries
    // and store them in 3 differnet QStringList (container)
    //for converting from QStringList to QString later via a foreach (QString itm, QStringList obj)
    // they're stored as private data memebre in the .h file

    // query - 1 (course_id)
    qry.str("");
    qry << "select course_id from takes where ID = \"" << std_id << "\";";
    res = mysql_execute_query(con, qry.str().c_str());


    while((row = mysql_fetch_row(res)) != NULL){
        for(unsigned int i = 0; i < mysql_field_count(con); i++){
            for(unsigned int j = 0; j < mysql_num_rows(res); j++){
                course.insert(j, row[j]);
            }
        }
        std::cout << std::endl;
    }
    mysql_free_result(res);


    // query - 2 (semester)
    qry.str("");
    qry << "select semester from takes where ID = \"" << std_id << "\";";
    res = mysql_execute_query(con, qry.str().c_str());

    while((row = mysql_fetch_row(res)) != NULL){
        for(unsigned int i = 0; i < mysql_field_count(con); i++){
            for(unsigned int j = 0; j < mysql_num_rows(res); j++){
                semester.insert(j, row[j]);
            }
        }
        std::cout << std::endl;
    }
    mysql_free_result(res);


    // query - 3 (year)
    qry.str("");
    qry << "select year from takes where ID = \"" << std_id << "\";";
    res = mysql_execute_query(con, qry.str().c_str());

    while((row = mysql_fetch_row(res)) != NULL){
        for(unsigned int i = 0; i < mysql_field_count(con); i++){
            for(unsigned int j = 0; j < mysql_num_rows(res); j++){
                year.insert(j, row[j]);
            }
        }
    }
    mysql_free_result(res);


    foreach(QString itm,  course){
        //for converting from QString to char*
        //since mysql_query() accepts only char*
        char temp_course[200];
        char temp_semester[200];
        char temp_year[200];

        QstringToCharArray(itm, temp_course);

        for(QString itm_2 : semester)
            QstringToCharArray(itm_2, temp_semester);
        for(QString itm_3 : year)
            QstringToCharArray(itm_3, temp_year);

        //preparing the query...
        qry.str("");
        qry << "select student.name, takes.ID, course_id, semester, year from student, takes " <<
               "where student.ID = takes.ID and course_id = \"" << temp_course << "\""<<
               " and student.ID != \"" << std_id << "\""
               " and semester = \"" << temp_semester << "\""
               " and year = \"" << temp_year << "\";";

        //query start...
        res = mysql_execute_query(con, qry.str().c_str());

        while((row = mysql_fetch_row(res)) != NULL){
            //creating a table
            QTableWidgetItem *item;

            int col_num = mysql_field_count(con);//to set the number of columns

            int rowCount = 0, columnCount = 0;

            ui->tableWidget_2->setColumnCount(col_num);
            ui->tableWidget_2->insertRow(rowCount);

            //Adding the header of the table
            QStringList label_2;
            label_2 << "Name" << "Student No" << "Course Id" << "Semester" << "Year";
            ui->tableWidget_2->setHorizontalHeaderLabels(label_2);

            for(unsigned int j = 0; j < mysql_field_count(con); j++){
                item = new QTableWidgetItem;

                //chagne table's cell to be read-only
                item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
                //the acutall inserting for data into the table
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
