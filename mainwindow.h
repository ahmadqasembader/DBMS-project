#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include <mysql/mysql.h>

class Student;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Ui::MainWindow *ui;
    //Student *std;

private:
    Student *std;

private slots:
    void on_pushButton_clicked();

};

struct connection_details;
MYSQL *mysql_connection_setup(struct connection_details mysql_details);

#endif // MAINWINDOW_H
