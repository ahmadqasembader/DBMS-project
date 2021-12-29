#ifndef FACULTYCOORDINATOR_H
#define FACULTYCOORDINATOR_H

#include <QDialog>

namespace Ui {
class facultyCoordinator;
}

class facultyCoordinator : public QDialog
{
    Q_OBJECT

public:
    explicit facultyCoordinator(QWidget *parent = nullptr);
    ~facultyCoordinator();

private slots:

private:
    Ui::facultyCoordinator *ui;
};

#endif // FACULTYCOORDINATOR_H
