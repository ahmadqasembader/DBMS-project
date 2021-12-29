#ifndef STUDENT_H
#define STUDENT_H

#include <QDialog>

namespace Ui {
class Student;
}

class Student : public QDialog
{
    Q_OBJECT
signals:
    //void sendMessage(const QString &msg);
public:
    explicit Student(QWidget *parent = nullptr);
    //explicit Student(QWidget *parent = nullptr, QString Id);
    ~Student();

public slots:
    //void buttonClicked();

private:
    Ui::Student *ui;
};

#endif // STUDENT_H
