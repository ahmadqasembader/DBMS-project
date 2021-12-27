#include "ui_mainwindow.h"
#include <mysql/mysql.h>
#include <iostream>
#include <QString>
#include <QMessageBox>
#include "mainwindow.h"
#include "student.h"


struct connection_details{
  const char *server, *user, *password, *database;

};

MYSQL *mysql_connection_setup(struct connection_details mysql_details){
    std::cout<<"IN here!" << std::endl;
    MYSQL *connection;
    connection = mysql_init(NULL);

    if(!mysql_real_connect(connection, mysql_details.server, mysql_details.user,
                           mysql_details.password, mysql_details.database, 0, NULL, 0)){
        QMessageBox msgbox;
        msgbox.setText("Connection failed");
        std::cout<<"connection failed" << std::endl;
        msgbox.exec();
        exit(1);
    }
    std::cout << "Database connection is successful" << std::endl;
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
    struct connection_details mysqlD;
    mysqlD.server = "localhost";
    mysqlD.user = "root";
    mysqlD.password = "9889";
    mysqlD.database = "university";
    con = mysql_connection_setup(mysqlD);

    QString username = ui->username->text();
    QString password = ui->password->text();

    if(username == "user" && password == "9889"){
        QMessageBox::information(this, "Login", "login successful");
        hide();
        std = new Student(this);
        std->show();
    }else{
        QMessageBox::warning(this, "Login", "login not successful");
    }


}
