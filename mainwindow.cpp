#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <mysql/mysql.h>
#include <iostream>
#include <string.h>
//#include <algorithm>

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
    QString sId = ui->userIDLogin->text();
    QString password = ui->passwordLogin->text();
    //char table[20] = "student";
    QString role = ui->RolecomboBox->currentText();
    const QByteArray comboBoxSelect = role.toUtf8();
    int size = comboBoxSelect.size();
    std::cout<<size;
    //comboSelect[7];
    char table[20];
    table[qMin(19, comboBoxSelect.size())] = '\0';
    std::copy(comboBoxSelect.constBegin(),
              comboBoxSelect.constBegin() + qMin(19, comboBoxSelect.size()), table);
    char query[50] = "select ID from ";
    strcat(query, table);
    //std::string que = "select name from student";
    mysql_query(con, query);
    res = mysql_store_result(con);

    QMessageBox loginMessage;
    while((row = mysql_fetch_row(res)) != NULL){
        //std::cout<<row[0];
        std::string r = row[0];
        QString qrow = QString::fromStdString(r);
       std::cout<<r<<std::endl;
       if(qrow == sId){
           if(role == "student"){
               this->hide();
               std = new Student(this, sId);
               std->show();
           }
           else if(role == "instructor"){
               this ->hide();
               instr = new Instructor(sId, this);
               instr->show();
           }

           else if(role == "faculty coordination"){
               this ->hide();
               factCord = new facultyCoordinator(sId, this);
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
    // mysql_close(con);
}

