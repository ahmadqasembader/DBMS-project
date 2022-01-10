#ifndef FACULTYCOORDINATOR_H
#define FACULTYCOORDINATOR_H

#include <QDialog>
#include "databaseconnection.h"

namespace Ui {
class facultyCoordinator;
}

class facultyCoordinator : public QDialog
{
    Q_OBJECT

public:
    explicit facultyCoordinator(QWidget *parent = nullptr);
    explicit facultyCoordinator(QString, QWidget *parent = nullptr);
    ~facultyCoordinator();

private slots:

    void on_assignCourse_clicked();

    void on_assignInstructorButton_clicked();

    void on_addNewCourse_clicked();

    void on_addNewTeacher_clicked();

    void on_addNewStudent_clicked();

private:
    Ui::facultyCoordinator *ui;
    QString id;
    MYSQL *con;
};

#endif // FACULTYCOORDINATOR_H
