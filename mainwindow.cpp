#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <mysql/mysql.h>
#include <iostream>
#include <student.h>

struct connection_details{
  const char *server, *user, *password, *database;

};

MYSQL *mysql_connection_setup(struct connection_details mysql_details){
    std::cout<<"IN here!";
    MYSQL *connection;
    connection = mysql_init(NULL);

    if(!mysql_real_connect(connection, mysql_details.server, mysql_details.user,
                           mysql_details.password, mysql_details.database, 0, NULL, 0)){
        QMessageBox msgbox;
        msgbox.setText("Connection failed");
        std::cout<<"connection failed";
        msgbox.exec();
        exit(1);
    }
    QMessageBox msgbox;
    std::cout<<"Connection successful";
    msgbox.setText("Connection successful");
    msgbox.exec();
    return connection;
}

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
    mysqlD.server = "localhost";
    mysqlD.user = "root";
    mysqlD.password = " kasbeat2,";
    mysqlD.database = "universityDatabase";
    //QMessageBox msgbox;
    con = mysql_connection_setup(mysqlD);
    QString SId = ui->userIDLogin->text();
    //std::cout<<SId;
    QString password = ui->passwordLogin->text();
    mysql_query(con, "select ID from student");
    res = mysql_store_result(con);

    QMessageBox loginMessage;
    while((row = mysql_fetch_row(res)) != NULL){
        std::string r = row[0];
        QString qrow = QString::fromStdString(r);
       std::cout<<r<<std::endl;
       if(qrow == SId){
           loginMessage.setText("Login successful");
           this->hide();
           std = new Student(this, SId);
           std->show();
           break;
       }
        else
           loginMessage.setText("Login unsuccessful");
    }
    //loginMessage.exec();

    mysql_free_result(res);
    // mysql_close(con);
}

