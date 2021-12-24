#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <mysql/mysql.h>
#include <iostream>

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
    /*ui->comboBox->addItem("Student");
    ui->comboBox->addItem("Instructor");
    ui->comboBox->addItem("Faculty coordinator");*/
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
    mysqlD.password = " kasbeat2,";
    mysqlD.database = "universityDatabase";
    //QMessageBox msgbox;
    con = mysql_connection_setup(mysqlD);
    QMessageBox msgbox;
    /*if(con != NULL){
        msgbox.setText("Successful");
        msgbox.exec();
    }
    else
        msgbox.setText("Failed");*/

}
