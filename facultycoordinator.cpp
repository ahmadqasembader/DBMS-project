#include "facultycoordinator.h"
#include "ui_facultycoordinator.h"
#include <qmessagebox.h>
#include<QtGui>
#include <QDebug>
#include <iostream>
#include <cstring>
#include <sstream>
#include <string>
#include <iomanip>


facultyCoordinator::facultyCoordinator(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::facultyCoordinator)
{
    ui->setupUi(this);
}

facultyCoordinator::facultyCoordinator(QString f_id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::facultyCoordinator)
{

    ui->setupUi(this);

    //database connection
    MYSQL_RES *res;
    MYSQL_ROW row;
    struct connection_details mysqlD;
    con = mysql_connection_setup(mysqlD);

    id = f_id;

    //creating QstringList for department and course ID
    QStringList deptList;
    QStringList idList;
    QStringList facultyList;
    QStringList courseList;

    //query for all department; this information will be use for the department comboBox;
    mysql_query(con, "select dept_name from department");
    res = mysql_store_result(con);

    //filling up the department StringList with the result of the query
    while((row = mysql_fetch_row(res)) != NULL){
        deptList<<row[0];
    }
    mysql_free_result(res);

    //querying for the list of course_id and filling the course StringList with the result
    mysql_query(con, "select course_id from course");
    res = mysql_store_result(con);
    while((row = mysql_fetch_row(res)) != NULL){
        idList<<row[0];
    }
    mysql_free_result(res);

    //Querying for the list of faculty to be used to fill the faculty combo box;
    mysql_query(con, "select name from faculty");
    res = mysql_store_result(con);
    while((row = mysql_fetch_row(res)) != NULL){
        facultyList<<row[0];
    }
    mysql_free_result(res);

   //Querying for the list of courses to be used to fill the faculty combo box;
    mysql_query(con, "select course_id from course");
    res = mysql_store_result(con);
    while((row = mysql_fetch_row(res)) != NULL){
        courseList<<row[0];
    }

    //using the StringList to set the comboBox;
    ui->courseDept->addItems(deptList);
    ui->instructorDept->addItems(deptList);
    ui->studentDept->addItems(deptList);
    ui->courseFact->addItems(facultyList);
    ui->instructorFact->addItems(facultyList);
    ui->studentFact->addItems(facultyList);
    ui->courses->addItems(courseList);


    //setting the first of all comboBoxes to "choose item lable"
    ui->courseDept->insertItem(0, "choose...");
    ui->courseDept->setCurrentIndex(0);
    ui->instructorDept->insertItem(0, "choose...");
    ui->instructorDept->setCurrentIndex(0);
    ui->studentDept->insertItem(0, "choose...");
    ui->studentDept->setCurrentIndex(0);
    ui->courseFact->insertItem(0, "choose...");
    ui->courseFact->setCurrentIndex(0);
    ui->instructorFact->insertItem(0, "choose...");
    ui->instructorFact->setCurrentIndex(0);
    ui->studentFact->insertItem(0, "choose...");
    ui->studentFact->setCurrentIndex(0);
    ui->courses->insertItem(0, "choose...");
    ui->courses->setCurrentIndex(0);

    //free the MYSQL result structure
    mysql_free_result(res);
}

facultyCoordinator::~facultyCoordinator()
{
    delete ui;
    mysql_close(con);
}


void facultyCoordinator::on_addNewCourse_clicked()
{
    char course_id[20];
    char title[30];
    char dept[40];
    int credit;
    char faculty[40];
    int count = 0;

    //The if checks makes sure that the ID field is not Empty
    if(ui->lineEdit->text() == NULL){
       QMessageBox::information(this, "ID not entered", "ID field cannot be empty");
    }
    else{
        QstringToCharArray(ui->lineEdit->text(), course_id);
        //checks to make sure the new course has at least two characters
        for(size_t i = 0; i < strlen(course_id); i++){
            if(isalpha(course_id[i]))
                count++;
        }
        if(count < 2){
           QMessageBox::information(this, "Invalid character length", "Course ID should have at least two characters");
        }
        else{
            //The length of the course Id must be at most 8 and less than 5
            if((strlen(course_id)) > 8){
                QMessageBox::information(this, "Invalid course ID lenght", "Course ID must be at most 8 characters");
            }
            else{
                if(strlen(course_id) < 5){
                    QMessageBox::information(this, "Invalid course ID lenght", "Course ID must be at least 5 characters");
                }

                //Title field cannot be left empty
                if(ui->lineEdit_4->text() == NULL){
                   QMessageBox::information(this, "Title not entered", "Title field cannot be empty");
               }
                else{
                    //A faculty must be selected. 1st Index of the course comboBox represents the "choose..." text
                    //Therefore index 0 is not a valid entry
                    if(ui->courseFact->currentIndex() == 0){
                        QMessageBox::information(this, "Faculty not entered", "Faculty field cannot be left unspecified");
                    }
                    else{
                        QstringToCharArray(ui->courseFact->currentText(), faculty);

                        //The department input will be defaulted to "unspecified if no entry is entered"
                        if(ui->courseDept->currentIndex() == 0){
                            strcpy(dept, "unspecified");
                        }
                        else{
                            QstringToCharArray(ui->courseDept->currentText(), dept);

                            //converting the Qstring input to appropriate char[] or int variable for use for query
                            QstringToCharArray(ui->lineEdit_4->text(), title);
                            credit = ui->lineEdit_6->text().toInt();

                            std::ostringstream str;
                            //preparing query
                            str<<"insert ignore into course values('" <<course_id <<"', '"
                              << title <<"', '" <<dept <<"', '" <<faculty <<"', " <<credit <<")";
                            std::string query = str.str();
                            int res = mysql_query(con, str.str().c_str());
                            std::cout<<str.str().c_str();

                            if(res == 0){
                                QMessageBox::information(this, "Success", "Course was successfully inserted");
                                std::cout<<query;
                            }
                            else{
                                std::cout<<query;
                                QMessageBox::information(this, "failed", "Failed to insert new course");
                            }
                        }
                    }
                }
            }
        }
    }
}

//The nested code method has been used to prevent multiple QmessageBox from popping up at once
//by ensuring that one entry is valid before moving on to next.

void facultyCoordinator::on_addNewTeacher_clicked()
{
    char i_id[10];
    char title[30];
    char dept[40];
    char faculty[40];
    double salary;

    if(ui->lineEdit_2->text() == NULL){
       QMessageBox::information(this, "ID not entered", "ID field cannot be empty");
    }

    //The instructor ID must be 6 characters long
    else{
        QstringToCharArray(ui->lineEdit_2->text(), i_id);

        if(strlen(i_id) != 6){
            QMessageBox::information(this, "Invalid ID length", "ID must be 6 characters long");
        }
        else{
            if(ui->lineEdit_7->text() == NULL){
                QMessageBox::information(this, "Name not entered", "Name field cannot be empty");

            }

            else{
                if(ui->instructorFact->currentIndex() == 0){
                    QMessageBox::information(this, "Faculty not entered", "Faculty field cannot be left unspecified");
                }
                else{
                    QstringToCharArray(ui->instructorFact->currentText(), faculty);
                    if(ui->instructorDept->currentIndex() == 0){
                        strcpy(dept, "unspecified");
                    }
                    else{
                        QstringToCharArray(ui->instructorDept->currentText(), dept);
                    }

                    QstringToCharArray(ui->lineEdit_2->text(), i_id);
                    QstringToCharArray(ui->lineEdit_7->text(), title);
                    salary = ui->lineEdit_9->text().toDouble();

                    std::ostringstream query;
                    query<<"insert into instructor values('" <<i_id <<"', '" <<title <<"', '" <<dept <<"', " <<salary <<", '" <<faculty <<"', '" <<i_id <<"')";
                    std::cout<<query.str().c_str();

                    int res = mysql_query(con, query.str().c_str());

                    if(res == 0){
                        QMessageBox::information(this, "Success", "Instructor was successfully inserted");
                    }
                    else{
                        QMessageBox::information(this, "failed", "Failed to insert new Instructor");
                    }
                }
            }
        }
     }
}


//add a new studetn...
void facultyCoordinator::on_addNewStudent_clicked()
{
    char studentId[10];
    char name[30];
    char dept[40];
    char faculty[40];
    int tot_cred = 0;

    if(ui->studentID_2->text() == NULL){
       QMessageBox::information(this, "ID not entered", "ID field cannot be empty");
    }
    else{
        QstringToCharArray(ui->studentID_2->text(), studentId);
        if(strlen(studentId)!= 6){
            QMessageBox::information(this, "Invalid ID length", "ID must be 6 characters long");
        }
        else{
            if(ui->studentName->text() == NULL){
                QMessageBox::information(this, "Name not entered", "Name field cannot be empty");
            }
            else{
                if(ui->studentFact->currentIndex() == 0){
                    QMessageBox::information(this, "Faculty not entered", "Faculty field cannot be left unspecified");
                }
                else{
                    QstringToCharArray(ui->studentFact->currentText(), faculty);
                    if(ui->studentDept->currentIndex() == 0){
                        strcpy(dept, "unspecified");
                    }
                    else{
                        QstringToCharArray(ui->studentDept->currentText(), dept);
                    }


                    QstringToCharArray(ui->studentName->text(), name);
                    tot_cred = ui->lineEdit_12->text().toInt();

                    std::ostringstream str;
                    str<<"insert ignore into student values('" <<studentId <<"', '"
                      << name <<"', '" <<dept <<"', '" <<faculty <<"', " <<tot_cred <<", " <<0.00 <<", '" <<studentId <<"')";

                    int res = mysql_query(con, str.str().c_str());
                    std::cout<<str.str().c_str();

                    if(res == 0){
                        QMessageBox::information(this, "Success", "Student was successfully inserted");
                    }
                    else{
                        QMessageBox::information(this, "failed", "Failed to insert new Student");
                    }
                }
            }
        }
    }
}

void facultyCoordinator::on_assignCourse_clicked()
{
    char i_id[10];
    char course_id[10];
    int sec;
    char semester[6];
    char year[9];
    int flag = 0;
    MYSQL_RES *res;
    MYSQL_ROW row;

    std::ostringstream query;
    if(ui->instructor_id->text() == NULL){
       QMessageBox::information(this, "Instructor ID not entered", "Instructor ID field cannot be empty");
    }
    else{
        //Checks to ensure that ID entered is a valid ID in database. Displays a message to notify the user if not.
        QstringToCharArray(ui->instructor_id->text(), i_id);
        mysql_query(con, "select ID from instructor");
        res = mysql_store_result(con);
        while((row = mysql_fetch_row(res))){
            if((strcmp(row[0], i_id)) == 0){
                flag = 1;
                break;
            }
        }
        mysql_free_result(res);
        if(flag == 0){
            QMessageBox::information(this, "Not a valid instructor", "Instructor ID entered has no entry in database");
        }
        else{
            flag = 0;
            if(ui->courses->currentIndex() == 0){
                QMessageBox::information(this, "Select course", "There must be a course entry");
            }
            else{
                QstringToCharArray(ui->courses->currentText(), course_id);
                char instructor_fac[60];

                query.str("");
                query.clear();

                query<< "select faculty from instructor where ID = " <<i_id;
                mysql_query(con, query.str().c_str());
                res = mysql_store_result(con);
                while((row = mysql_fetch_row(res)) != NULL){
                    strcpy(instructor_fac, row[0]);
                }
                mysql_free_result(res);
                query.str("");
                query.clear();
                query<<"select course_id from course where faculty = '" <<instructor_fac <<"'";
                mysql_query(con, query.str().c_str());
                res = mysql_store_result(con);

                while((row = mysql_fetch_row(res)) != NULL){
                    //using the previous query, it checks if the
                    //course being assigned to the instructor is a course of the faculty.
                    //For example, the condition will not pass if the instructor(from the Faculty of Engineering
                    //is being assigned a course from pharmacy department.
                    char holdRow[10];
                    QstringToCharArray(row[0], holdRow);
                    std::cout<<"holdRow: " <<holdRow <<std::endl;;
                    if((strcmp(holdRow, course_id)) == 0){
                        flag = 1;
                        break;
                    }
                }
                if(flag != 1){
                    QMessageBox::information(this, "Invalid course selection", "Instructor cannot be assigned to course from another faculty");
                }
                else{
                    QstringToCharArray(ui->courses->currentText(), course_id);
                    sec = ui->lineEdit_39->text().toInt();
                    QstringToCharArray(ui->comboBox_4->currentText(), semester);
                    QstringToCharArray(ui->comboBox_5->currentText(), year);

                    query.str("");
                    query.clear();
                    query<<"insert ignore into section(course_id, sec_id, semester, year) values('"<<course_id <<"', " <<sec <<", '"
                               <<semester <<"', '" <<year <<"')";
                   mysql_query(con, query.str().c_str());

                   query.str("");
                   query.clear();
                    query<<"insert ignore into teaches(ID, course_id, sec_id, semester, year) values('" << i_id <<"', '"
                      << course_id <<"', " <<sec <<", '" <<semester <<"', '" <<year <<"')";
                    int res = mysql_query(con, query.str().c_str());

                    if(res == 0){
                        QMessageBox::information(this, "Success", "Course has been assigned to instructor");
                        std::cout<<mysql_error(con);
                    }
                    else{
                        QMessageBox::information(this, "failed", "Check input");
                    }
                }

            }
        }

    }
}

void facultyCoordinator::on_assignInstructorButton_clicked()
{
    char s_id[10];
    char i_id[10];
    int flag = 0;
    char temp[10];
    int status;
    std::ostringstream query;

    QstringToCharArray(ui->studentID->text(), s_id);
    QstringToCharArray(ui->lineEdit_38->text(), i_id);

    MYSQL_RES *res;
    MYSQL_ROW row;

    mysql_query(con, "select ID from student");
    res = mysql_store_result(con);

    //Loop through all ID in student and checks
    //if the ID entered is found in the Student Database
    while((row = mysql_fetch_row(res)) != NULL){
         QstringToCharArray(row[0], temp);
         if(strcmp(s_id, temp) == 0){
             flag = 1;
             break;
         }
    }
    if(flag == 0){
        QMessageBox::information(this, "Check entry", "Student not in database");
    }
    else{
        flag = 0;
        mysql_query(con, "select ID from instructor");
        res = mysql_store_result(con);

        //Ensures the instructor is in the database
        while((row = mysql_fetch_row(res)) != NULL){
             QstringToCharArray(row[0], temp);
             if(strcmp(i_id, temp) == 0){
                 flag = 1;
                 break;
             }
        }
        if(flag == 0){
            QMessageBox::information(this, "Check entry", "Instructor not in database");
        }
        else{
            char instructorFact[100];
            query.str("");
            query.clear();
            query<<"select faculty from instructor where ID = "<<i_id;
            mysql_query(con, query.str().c_str());
            res = mysql_use_result(con);
            while((row = mysql_fetch_row(res)) != NULL){
                QstringToCharArray(row[0], instructorFact);
            }

            char holdStudentFaculty[100];
            query.str("");
            query.clear();
            query<<"select faculty from student where ID = " <<s_id;
            mysql_query(con, query.str().c_str());
            res = mysql_use_result(con);
            while((row = mysql_fetch_row(res)) != NULL){
                QstringToCharArray(row[0], holdStudentFaculty);
            }
            if(strcmp(holdStudentFaculty, instructorFact) != 0){
                QMessageBox::information(this, "Invalid",
                                         "Instructor to be assigned to student should be from the same faculty");
            }
            else{
                query.str("");
                query.clear();
                query<<"insert ignore into advisor(s_id, i_id) values('" <<s_id <<"', '" <<i_id <<"')";
                status = mysql_query(con, query.str().c_str());
                if(status == 0){
                    QMessageBox::information(this, "Success", "Successful entry!");
                }
                else{
                    QMessageBox::information(this, "Insert error", "There was a problem inserting the data to database");

                }

            }
        }
    }
    mysql_free_result(res);
}




