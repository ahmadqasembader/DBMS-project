#ifndef INSTRUCTOR_H
#define INSTRUCTOR_H

#include <QDialog>

namespace Ui {
class Instructor;
}

class Instructor : public QDialog
{
    Q_OBJECT

public:
    explicit Instructor(QWidget *parent = nullptr);
     explicit Instructor(QString id, QWidget *parent = nullptr);
    ~Instructor();

private slots:

private:
    Ui::Instructor *ui;
    QString sId;
};

#endif // INSTRUCTOR_H
