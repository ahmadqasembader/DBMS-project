#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "databaseconnection.h"
#include <iostream>
#include <sstream>
#include <cstring>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}
//QMessageBox msgbox;
MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::on_pushButton_clicked()
{
    //Mysql connection...
    MYSQL *con = NULL;
    MYSQL_RES *res;
    MYSQL_ROW row = NULL;
    struct connection_details mysqlD;
    con = mysql_connection_setup(mysqlD);

    //fetching the enterd ID, password and type of user...
    QString roleId = ui->userIDLogin->text();
    QString password = ui->passwordLogin->text();
    QString role = ui->RolecomboBox->currentText();


    char table[20];
    QstringToCharArray(role, table);

    std::ostringstream str;
    str <<"Select ID from " << table;
    std::string query = str.str();

    mysql_query(con, query.c_str());
    res = mysql_store_result(con);

    QMessageBox loginMessage;
    while((row = mysql_fetch_row(res)) != NULL){
        std::string r = row[0];
        QString qrow = QString::fromStdString(r);

       if(qrow == roleId){
           if(role == "student"){
               this->hide();
               std = new Student(this, roleId);
               std->show();
           }
           else if(role == "instructor"){
               this ->hide();
               instr = new Instructor(roleId, this);
               instr->show();
           }

           else if(role == "faculty_coordinator"){
               this ->hide();
               factCord = new facultyCoordinator(roleId, this);
               factCord->show();
           }

           loginMessage.setText("Login successful");
           break;
       }
        else
           loginMessage.setText("Login unsuccessful");
    }

    mysql_free_result(res);
    mysql_close(con);
}

