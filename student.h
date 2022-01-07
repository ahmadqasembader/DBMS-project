#ifndef STUDENT_H
#define STUDENT_H
#include <QtCore>
#include <QtGui>
#include <QStringList>
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
    QStringList course;
    QStringList semester;
    QStringList year;

};

#endif // STUDENT_H
