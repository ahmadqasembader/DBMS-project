#include "instructor.h"
#include "ui_instructor.h"
#include "databaseconnection.h"
#include <iostream>
#include <sstream>
#include <string>
#include<QtGui>

/*Things to implement if we have some extra time on our hand:
    1. Add a "load button to the list view so that the list refreshes when we click it"
*/
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

    char inst_id[50];
    QstringToCharArray(i_id, inst_id);
    char qry[200];



    MYSQL *con = NULL;
    MYSQL_RES *res;
    MYSQL_ROW row = NULL;
    struct connection_details mysqlD;
    con = mysql_connection_setup(mysqlD);



    // ======================================================== //
    //               Student Personal Details
    // ======================================================== //

    strcpy(qry, "select * from instructor where ID = ");
    strcat(qry, inst_id);

    mysql_query(con,  qry);
    res = mysql_store_result(con);

    mysql_query(con, qry);
    res = mysql_store_result(con);
    row = mysql_fetch_row(res);

    //Inserting to the UI the perosnal data of instructor
    ui->label_3 ->setText(row[0]);
    ui->label_8->setText(row[1]);
    ui->label_4 ->setText(row[2]);


    // ======================================================== //
    //                      Assinged Courses
    // ======================================================== //

    //preparing the query
    strcpy(qry, "select course_id, sec_id, semester, year from teaches where ID = ");
    strcat(qry, inst_id);

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
}

Instructor::~Instructor()
{
    delete ui;
}
