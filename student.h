#ifndef STUDENT_H
#define STUDENT_H

#include <QtCore>
#include <QtGui>
#include <QDialog>
namespace Ui {
class Student;
}

class Student : public QDialog
{
    Q_OBJECT

public:
    explicit Student(QWidget *parent = nullptr);
    explicit Student(QWidget *parent, QString);
    ~Student();
    Ui::Student *ui;

private:
    //  QStringListModel *model;
};

#endif // STUDENT_H
