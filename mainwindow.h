#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
//#include <mysql/mysql.h>
#include "student.h"
#include "instructor.h"
#include "facultycoordinator.h"

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
    Instructor *instr;
    facultyCoordinator *factCord;


private slots:
    void on_pushButton_clicked();

};


#endif // MAINWINDOW_H
