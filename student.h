#ifndef STUDENT_H
#define STUDENT_H

#include <QDialog>
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
    QString Id;
};

#endif // STUDENT_H
