#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QtSql>
#include <QDialog>
#include <QSqlDatabase>
#include <QMessageBox>
#include <mysql/mysql.h>
#include "student.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void on_pushButton_clicked();


private:
    Ui::MainWindow *ui;
    Student *std;
};

struct connection_details;
MYSQL *mysql_connection_setup(struct connection_details mysql_details);

#endif // MAINWINDOW_H
