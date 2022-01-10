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
    std::ostringstream str;
    str<<"Select ID from " <<table;
    std::string query = str.str();
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


/*#include "mainwindow.h"
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


    char tableName[20], ID[20];
    QstringToCharArray(role, tableName);
    QstringToCharArray(roleId, ID);

    std::ostringstream qry;
    qry << "select ID from " << tableName << " where ID = " << ID;
    //mysql_query(con, qry.str().c_str());
    res = mysql_execute_query(con, qry.str().c_str());
    //res = mysql_store_result(con);
    std::cout << qry.str() << std::endl;

    while((row = mysql_fetch_row(res)) != NULL){
        std::string userId = row[0];
        std::string userPass = row[1];

        std::cout  << "user id: "<< userId << std::endl;
        std::cout  << "user pass: " << userPass << std::endl;

        QString qrow_1 = QString::fromStdString(userId);
        QString qrow_2 = QString::fromStdString(userPass);
        if(qrow_1 == roleId){
            if(role == "student"){
                this->hide();
                std = new Student(this, roleId);
                std->show();
            }
            else if(role == "instructor"){
                this ->hide();
                instr = new Instructor(roleId, this);
                std::cout  << "Here" << std::endl;
                instr->show();
            }

            else if(role == "faculty_coordinator"){
                this ->hide();
                factCord = new facultyCoordinator(roleId, this);
                factCord->show();
            }
        }else {
            std::cout << "validation error" << std::endl;
        }
    }

    mysql_free_result(res);

}

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "databaseconnection.h"
#include <iostream>
#include <sstream>
#include <cstring>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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

    //converting from QString to char array...
    char tableName[20], ID[20];
    QstringToCharArray(role, tableName);
    QstringToCharArray(roleId, ID);

    //starting query...
    std::ostringstream qry;
    qry << "select ID from " << tableName << " where ID = " << ID;
    res = mysql_execute_query(con, qry.str().c_str());


    while((row = mysql_fetch_row(res)) != NULL){
        std::string userId = row[0];
        std::string userPass = row[1];

        //converting from std::string to QString from comparison compatibility
        QString qrow_1 = QString::fromStdString(userId);
        //QString qrow_2 = QString::fromStdString(userPass);

        //validate the user id and password...
        if(qrow_1 == roleId){
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
        }else{
            //in case incorrect user id or password was typed in...
            QMessageBox err;
            err.setText("Wrong inputs");
            err.exec();
        }
    }
    mysql_free_result(res);
}

MainWindow::~MainWindow()
{
    //mysql_close(con);
    delete ui;
}
*/
