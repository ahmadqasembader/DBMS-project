#ifndef STUDENT_H
#define STUDENT_H

#include <QDialog>
#include "mainwindow.h"
namespace Ui {
class Student;
}

class Student : public QDialog
{
    Q_OBJECT

public:
    explicit Student(QWidget *parent = nullptr);
    explicit Student(QWidget *parent, QString ID);
    ~Student();
    Ui::Student *ui;

private:
    MainWindow *main;
    QString Id;

private slots:
    void on_pushButton_clicked();
    //void on_label_3_windowIconTextChanged(const QString &iconText);
    void receiveData(QString);
};

#endif // STUDENT_H
