#ifndef INSTRUCTOR_H
#define INSTRUCTOR_H

#include <QDialog>
#include "databaseconnection.h"
#include <QSignalSpy>
#include "ui_instructor.h"

namespace Ui {
class Instructor;
}

class Instructor : public QDialog
{
    Q_OBJECT

public:
    explicit Instructor(QWidget *parent = nullptr);
     explicit Instructor(QString i_id, QWidget *parent = nullptr);
    ~Instructor();


private slots:

    void on_registerButton_clicked();

private:
    MYSQL *con;
    Ui::Instructor *ui;
    QStringList courseList;
    QString id;
};

#endif // INSTRUCTOR_H
