#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "databaseconnection.h"
#include <iostream>
#include<sstream>


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
    MYSQL *con = NULL;
    MYSQL_RES *res;
    MYSQL_ROW row = NULL;
    struct connection_details mysqlD;
    //details removed
    con = mysql_connection_setup(mysqlD);
    QString roleId = ui->userIDLogin->text();
    QString password = ui->passwordLogin->text();
    //char table[20] = "student";
    QString role = ui->RolecomboBox->currentText();
    char table[20];
    QstringToCharArray(role, table);
    //char query[50] = "select ID from ";
    std::ostringstream str;
    str<<"Select ID from " <<table;
    std::string query = str.str();
    //std::cout<<query;
    //strcat(query, table);
    mysql_query(con, query.c_str());
    res = mysql_store_result(con);

    QMessageBox loginMessage;
    while((row = mysql_fetch_row(res)) != NULL){
        //std::cout<<row[0];
        std::string r = row[0];
        QString qrow = QString::fromStdString(r);
       //std::cout<<r<<std::endl;
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
    //loginMessage.exec();

    mysql_free_result(res);
    mysql_close(con);
}

