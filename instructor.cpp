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
    id = i_id;
    MYSQL *con;
     struct connection_details mysqlD;
    con = mysql_connection_setup(mysqlD);
    ui->label_3->setText(id);
    //select * from instructor where ID = id;
    char instructorID[7];
    QstringToCharArray(id, instructorID);
    std::ostringstream str;
    str<<"select * from instructor where ID = '" <<instructorID <<"'";
    std::string query = str.str();
   // char query[100] = "select * from instructor where ID = "" + instructorID """;
    //strcat(query,instructorID);

    mysql_query(con, query.c_str());
    MYSQL_RES *res;
    res = mysql_store_result(con);
    MYSQL_ROW row = NULL;
    row = mysql_fetch_row(res);
    ui->label_8->setText(row[1]);
    ui->label_4 ->setText(row[2]);

    QStringListModel *model;
    QStringList list;
    //list <<

}

Instructor::~Instructor()
{
    delete ui;
}
