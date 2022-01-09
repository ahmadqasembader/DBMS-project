#include "instructor.h"
#include "ui_instructor.h"
#include "databaseconnection.h"
#include <iostream>
#include <sstream>
#include <string>
#include<QtGui>
#include<QMessageBox>
#include <QString>
#include <QDebug>

/*Things to implement if we have some extra time on our hand:
    1. Add a "load button to the list view so that the list refreshes when we click it"
*/
Instructor::Instructor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Instructor)
{
    ui->setupUi(this);
}

Instructor::Instructor(QString i_id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Instructor)
{
    ui->setupUi(this);
    id = i_id;
    char inst_id[50];
    QstringToCharArray(i_id, inst_id);
    //char qry[200];
    std::ostringstream qry;

    //Database connection
    MYSQL_RES *res;
    MYSQL_ROW row = NULL;
    struct connection_details mysqlD;
    con = mysql_connection_setup(mysqlD);

    //Setting the courses comboBox in registration section
    std::ostringstream query;
    query<<"select distinct(course_id) from teaches where ID = " <<inst_id;
    res = mysql_execute_query(con, query.str().c_str());
    while((row = mysql_fetch_row(res)) != NULL){
        courseList<<row[0];
    }

    ui->courseIDBox->addItems(courseList);
    ui->courseIDBox->insertItem(0, "choose...");
    ui->courseIDBox->setCurrentIndex(0);
    mysql_free_result(res);

    // ======================================================== //
    //               Instructor Personal Details
    // ======================================================== //

    qry << "select * from instructor where ID = " << inst_id;
    res = mysql_execute_query(con, qry.str().c_str());
    row = mysql_fetch_row(res);

    //Inserting to the UI the perosnal data of instructor
    ui->label_3 ->setText(row[0]);
    ui->label_8->setText(row[1]);
    ui->label_4 ->setText(row[2]);
    mysql_free_result(res);


    // ======================================================== //
    //                      Assinged Courses
    // ======================================================== //

    //preparing the query
    std::ostringstream qry_2;
    qry_2.str("");
    qry_2 << "select course_id, sec_id, semester, year from teaches where ID = " << inst_id;
    mysql_query(con, qry_2.str().c_str());
    res = mysql_use_result(con);

    while((row = mysql_fetch_row(res)) != NULL){
        QTableWidgetItem *item;

        int col_num = mysql_field_count(con);

        int rowCount = 0, columnCount = 0;

        ui->tableWidget->setColumnCount(col_num);
        ui->tableWidget->insertRow(rowCount);

        //Adding the header of the table
        QStringList label;
        label << "Course Id" << "Group No" << "Semester" << "Year" << "Grade";
        ui->tableWidget->setHorizontalHeaderLabels(label);
        //Dynamically allocating...
        for(unsigned int j = 0; j < mysql_field_count(con); j++){
            item = new QTableWidgetItem;
            item->setText(row[j]);
            ui->tableWidget->setItem(rowCount, columnCount, item);

            //Resize rows, columns, and the table to fit content
            ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            ui->tableWidget->resizeColumnsToContents();
            ui->tableWidget->resizeRowsToContents();

            columnCount++;
        }
        rowCount++;
    }
    mysql_free_result(res);
}

Instructor::~Instructor()
{
    delete ui;
    mysql_close(con);
}

void Instructor::on_registerButton_clicked()
{
    MYSQL_RES *res;
    MYSQL_ROW row;
    char s_id[10];
    char i_id[10];
    char studentFaculty[50];
    char instrFaculty[50];
    int flag = 0;
    std::ostringstream query;

    if(ui->courseIDBox->currentIndex() == 0){
        QMessageBox::information(this, "Select course_id", "No course ID was selected");
    }
    //QString temp = ui->studentID->text();
    QstringToCharArray(ui->studentID->text(), s_id);
    QstringToCharArray(id, i_id);

    //Querying for faculty for both instructor and student to ensure that
    //the instructor can only register student in the same faculty

     query<<"select faculty from student where ID = '" <<s_id <<"'";
    res = mysql_execute_query(con, query.str().c_str());
    while((row = mysql_fetch_row(res)) != NULL){
        strcpy(studentFaculty, row[0]);
    }
    mysql_free_result(res);

    query.str("");
    query.clear();
    query<<"select faculty from instructor where ID = " <<i_id;
    res = mysql_execute_query(con, query.str().c_str());
    while((row = mysql_fetch_row(res)) != NULL){
        strcpy(instrFaculty, row[0]);
    }

    //check to ensure student and instructor are in the same faculty;
    if((strcmp(studentFaculty, instrFaculty)) == 0){
        QStringList groupList, semesterList, yearList;

            char course_id[10];
            QstringToCharArray(ui->courseIDBox->currentText(), course_id);
            std::ostringstream query;

            query.str("");
            query.clear();

            query<<"select sec_id, semester, year "
                   "from teaches where ID = '" <<i_id <<"' and course_id ='" <<course_id <<"'";

            res = mysql_execute_query(con, query.str().c_str());

            while((row = mysql_fetch_row(res)) != NULL){
                groupList<<row[0];
                semesterList<<row[1];
                yearList<<row[2];
            }

            if(ui->groupLineEdit->text() != NULL){
                for(auto &i : groupList){
                    if(i == ui->groupLineEdit->text()){
                        flag = 1;
                        break;
                    }
                }
                if(flag == 0){
                    QMessageBox::information(this, "Invalid group entry", "Check course assigned tab "
                                                                        "for valid group entry");
                }
                else{
                    flag = 0;
                    if(ui->semesterLineEdit->text() != NULL){
                        for(auto &i : semesterList){
                            if(i == ui->semesterLineEdit->text()){
                                flag = 1;
                                std::cout<<"found";
                                break;
                            }
                        }
                        if(flag == 0){
                            QMessageBox::information(this, "Invalid semester entry", "Check course assigned tab "
                                                                                "for valid Semester entry");
                        }
                        else{
                            flag = 0;
                            if(ui->yearLineEdit->text() != NULL){
                                for(auto &i : yearList){
                                    if(i == ui->yearLineEdit->text()){
                                        flag = 1;
                                        break;
                                    }
                                }
                                if(flag == 0){
                                    QMessageBox::information(this, "Invalid year entry", "Check course assigned tab "
                                                                                        "for valid year entry");
                                }
                                else{
                                    char semester[8], year[10];
                                    int group;
                                    QstringToCharArray(ui->semesterLineEdit->text(), semester);
                                    QstringToCharArray(ui->yearLineEdit->text(), year);
                                    group = ui->groupLineEdit->text().toInt();

                                    query.str("");
                                    query.clear();
                                    query<<"insert ignore into takes(ID, course_id, sec_id, semester, year, grade)"
                                           "values('"<<s_id <<"', '"<<course_id<<"', '" <<group <<"', '" <<semester
                                        <<"', '" <<year <<"', '" <<0 <<"')";

                                   int status = mysql_query(con, query.str().c_str());
                                   if(status == 0){
                                       QMessageBox::information(this, "Success", "Registration successful");
                                   }
                                   else{
                                       QMessageBox::information(this, "Unsuccessful", "Make sure the entries are valid");
                                   }
                                }
                            }
                        }
                    }
                }
            }
    }
    else {
        QMessageBox::information(this, "Not valid", "Cannot register student from another faculty");
    }
    mysql_free_result(res);
}

