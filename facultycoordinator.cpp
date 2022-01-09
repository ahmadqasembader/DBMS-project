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
    MYSQL_RES *deptRes, *idRes;
    MYSQL_ROW deptRow = NULL, idRow = NULL;
    struct connection_details mysqlD;
    con = mysql_connection_setup(mysqlD);

    //creating QstringList and model for department and course ID
    id = f_id;
    QStringListModel *deptModel;
    QStringListModel *idModel;
    deptModel = new QStringListModel(this);
    idModel = new QStringListModel(this);
    QStringList deptList;
    QStringList idList;

    //query for all department; this information will be use for the department comboBox;
    mysql_query(con, "select dept_name from department");
    deptRes = mysql_store_result(con);

    //filling up the department StringList with the result of the query
    while((deptRow = mysql_fetch_row(deptRes)) != NULL){
        deptList<<deptRow[0];
    }

    //querying for the list of course_id and filling the course StringList with the result
    mysql_query(con, "select course_id from course");
    idRes = mysql_store_result(con);
    while((idRow = mysql_fetch_row(idRes)) != NULL){
        idList<<idRow[0];
    }

    //Setting the department and course model
    deptModel->setStringList(deptList);
    idModel->setStringList(idList);

    //using the model to set the comboBox;
    ui->comboBox->setModel(deptModel);
    ui->comboBox->insertItem(0, "choose...");
    ui->comboBox->setCurrentIndex(0);
     ui->comboBox_2->setModel(deptModel);
     ui->comboBox_3->setModel(deptModel);
    ui->comboBox_6->setModel(idModel);

    //free the MYSQL result structure
    mysql_free_result(deptRes);
    mysql_free_result(idRes);
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

    //The if checks makes sure that the ID field of add
    if(ui->lineEdit->text() == NULL){
       QMessageBox::information(this, "ID not entered", "ID field cannot be empty");
    }
    else if(ui->lineEdit_4->text() == NULL){
        QMessageBox::information(this, "Title not entered", "Title field cannot be empty");

    }
    if(ui->comboBox->currentIndex() == 0){
        strcpy(dept, "");
    }
    else{
        QstringToCharArray(ui->comboBox->currentText(), dept);
    }

    QstringToCharArray(ui->lineEdit->text(), course_id);
    //std::cout<<course_id;
    QstringToCharArray(ui->lineEdit_4->text(), title);


    //qDebug()<<ui->comboBox->currentText();
    //std::cout<<"The department entered is "<<dept <<std::endl;
    credit = ui->lineEdit_6->text().toInt();

    std::ostringstream str;
    str<<"insert ignore into course values('" <<course_id <<"', '"
      << title <<"', '" <<dept <<"', " <<credit <<")";
    std::string query = str.str();
    //std::string query = "insert into course values('Eco222', 'Economics', 'History', 4)";
    //char query[] = "insert into course values('Eco222', 'Economics', 'History', 4)";
    //std::cout<<query;
    int res = mysql_query(con, query.c_str());

    if(res == 0){
        QMessageBox::information(this, "Success", "Course was successfully inserted");
        std::cout<<query;
    }
    else{
        std::cout<<query;
        QMessageBox::information(this, "failed", "Failed to insert new course");
    }
}


void facultyCoordinator::on_pushButton_3_clicked()
{
    char course_id[10];
    char title[30];
    char dept[40];
    double salary;
    if(ui->lineEdit_2->text() == NULL){
       QMessageBox::information(this, "ID not entered", "ID field cannot be empty");
    }
    else if(ui->lineEdit_7->text() == NULL){
        QMessageBox::information(this, "Name not entered", "Name field cannot be empty");

    }

    if(ui->comboBox_2->currentIndex() == 0){
        strcpy(dept, "");
    }
    else{
        QstringToCharArray(ui->comboBox_2->currentText(), dept);
    }
    QstringToCharArray(ui->lineEdit_2->text(), course_id);
    QstringToCharArray(ui->lineEdit_7->text(), title);
    salary = ui->lineEdit_9->text().toDouble();

    std::ostringstream str;
    str<<"insert ignore into instructor values('" <<course_id <<"', '"
      << title <<"', '" <<dept <<"', " <<salary <<")";
    std::string query = str.str();

    int res = mysql_query(con, query.c_str());

    if(res == 0){
        QMessageBox::information(this, "Success", "Instructor was successfully inserted");
        std::cout<<query;
    }
    else{
        std::cout<<query;
        QMessageBox::information(this, "failed", "Failed to insert new Instructor");
    }
}

void facultyCoordinator::on_pushButton_4_clicked()
{
    char course_id[10];
    char title[30];
    char dept[40];
    int tot_cred = 0;
    double cgpa = 0;
    if(ui->lineEdit_3->text() == NULL){
       QMessageBox::information(this, "ID not entered", "ID field cannot be empty");
    }
    else if(ui->lineEdit_10->text() == NULL){
        QMessageBox::information(this, "Name not entered", "Name field cannot be empty");
    }

    if(ui->comboBox_4->currentIndex() == 0){
        strcpy(dept, "");
    }
    else{
        QstringToCharArray(ui->comboBox_4->currentText(), dept);
    }
    QstringToCharArray(ui->lineEdit_3->text(), course_id);
    QstringToCharArray(ui->lineEdit_10->text(), title);
    tot_cred = ui->lineEdit_12->text().toInt();
    cgpa = ui->lineEdit_13->text().toDouble();

    std::ostringstream str;
    str<<"insert ignore into student values('" <<course_id <<"', '"
      << title <<"', '" <<dept <<"', " <<tot_cred <<", " <<cgpa <<")";
    std::string query = str.str();

    int res = mysql_query(con, query.c_str());

    if(res == 0){
        QMessageBox::information(this, "Success", "Student was successfully inserted");
        //std::cout<<query;
    }
    else{
        std::cout<<query;
        QMessageBox::information(this, "failed", "Failed to insert new Student");
    }
}

void facultyCoordinator::on_pushButton_2_clicked()
{
    char i_id[6] = "";
    char course_id[10];
    int sec;
    char semester[6];
    char year[9];
    int err;
    int flag = 0;
    if(ui->instructor_id->text() == NULL){
       QMessageBox::information(this, "Instructor ID not entered", "Instructor ID field cannot be empty");
    }
    char temp[6];
    QstringToCharArray(ui->instructor_id->text(), i_id);
    strcpy(temp, i_id);
    strcpy(i_id, temp);
    //std::cout<<"Value of temp: " <<temp <<std::endl;
    //std::cout<<"Id entered: " <<i_id <<std::endl;

    if(ui->comboBox_6->currentIndex() == 0){
        strcpy(course_id, "");
    }
    else{
        //std::cout<<"ID in else column: " <<i_id <<std::endl;
        MYSQL_RES *facultyResult, *res;
        MYSQL_ROW row;
        QstringToCharArray(ui->comboBox_6->currentText(), course_id);
        //std::cout<<"Id after stringtochar course_id: " <<i_id <<std::endl;
        char instructor_fac[60];
        //std::cout<<"The ID = " <<i_id <<std::endl;
        char queryFac[200] = "select faculty from instructor where ID = ";
        strcat(queryFac, i_id);
        mysql_query(con, queryFac);
        facultyResult = mysql_store_result(con);
        while((row = mysql_fetch_row(facultyResult)) != NULL){
            strcpy(instructor_fac, row[0]);
        }
        char query[300];
        strcpy(query, "select course_id from course where faculty = '");
        strcat(query, instructor_fac);
        strcat(query, "'");
        std::cout<<query;
        err = mysql_query(con, query);

        if(err != 0){
            std::cout<<"Error in querying for course_id";
        }

        res = mysql_store_result(con);
        while((row = mysql_fetch_row(res)) != NULL){
            std::cout<<std::setw(10)<<row[0] <<std::endl;;
            std::cout<<"The = Id being searched for: " <<course_id <<std::endl;
            char holdRow[10];
            QstringToCharArray(row[0], holdRow);
            std::cout<<"holdRow: " <<holdRow <<std::endl;;
            if((strcmp(holdRow, course_id)) == 0){
                std::cout<<"Found course_id";
                std::cout<<course_id <<"->" <<row[0] <<std::endl;
                flag = 1;
                break;
            }
        }
    }

    if(flag != 1){
        QMessageBox::information(this, "Invalid course selection", "Instructor cannot be assigned to course from another faculty");
    }
    else{
        QstringToCharArray(ui->comboBox_6->currentText(), course_id);
        sec = ui->lineEdit_39->text().toInt();
        QstringToCharArray(ui->comboBox_4->currentText(), semester);
        QstringToCharArray(ui->comboBox_5->currentText(), year);

        std::ostringstream sessionquery;
        sessionquery<<"insert ignore into section(course_id, sec_id, semester, year) values('"<<course_id <<"', " <<sec <<", '"
                   <<semester <<"', '" <<year <<"')";
       std::string insertToSession;
       insertToSession = sessionquery.str();
       std::cout<<"insertTosession query: " <<insertToSession <<std::endl;
       err = mysql_query(con, insertToSession.c_str());

       if(err != 0){
            std::cout<<"Failed to insert into section";
       }

        std::ostringstream str;
        //std::cout<<"i_id at this point" <<i_id;
        str<<"insert ignore into teaches(ID, course_id, sec_id, semester, year) values('" << i_id <<"', '"
          << course_id <<"', " <<sec <<", '" <<semester <<"', '" <<year <<"')";
        std::string query = str.str();
        std::cout<<query<<std::endl;
        int res = mysql_query(con, query.c_str());

        if(res == 0){
            QMessageBox::information(this, "Success", "Course has been assigned to instructor");
            std::cout<<mysql_error(con);
            //std::cout<<query;
        }
        else{
            std::cout<<query;
            QMessageBox::information(this, "failed", "Check input");
        }
    }
}

void facultyCoordinator::on_pushButton_5_clicked()
{
    char s_id[10] = "";
    char i_id[10] = "";
    int flag = 0;
    char temp[10];
    int status;
//    ui->lineEdit_37->text().toStdString().c_str();
   // QString hold = ui->lineEdit_37->text(),
    //QstringToCharArray(hold, temp);
    //QString hold = ui->lineEdit_37->text();
    QstringToCharArray(ui->studentID->text(), s_id);
    std::cout<<"s_id first entry: " <<s_id <<std::endl;
    strcpy(temp, s_id);
    strcpy(s_id, " ");
    strcpy(s_id, temp);
    //std::cout<<"INputed s_id: " <<s_id <<std::endl;
    QstringToCharArray(ui->lineEdit_38->text(), i_id);

    std::cout<<"s_id over here: " <<s_id <<std::endl;
    std::cout<<"s_id after converted: " <<s_id <<std::endl;
    std::cout<<"i_id: " <<i_id <<std::endl;

    MYSQL_RES *res;
    MYSQL_ROW row;

    mysql_query(con, "select ID from student");
    res = mysql_store_result(con);

    std::cout<<"Before while loop: " <<s_id <<std::endl;
    char holdId[10];
    strcpy(holdId, s_id);
    strcpy(s_id, holdId);
    while((row = mysql_fetch_row(res)) != NULL){
         QstringToCharArray(row[0], temp);
         std::cout<<s_id;
         std::cout<<"Searching through database: "<<s_id <<"-> " <<temp <<std::endl;
         if(strcmp(s_id, temp) == 0){
             flag = 1;
             std::cout<<"True";
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
            std::ostringstream tempStr;
            char query[200] = "select faculty from instructor where ID = ";
            strcat(query, i_id);
            status = mysql_query(con, query);
            if(status != 0){
                std::cout<<query;
                std::cout<<"There was a problem getting faculty from student table";
            }
            else if(status == 0){
                res = mysql_use_result(con);
                while((row = mysql_fetch_row(res)) != NULL){
                    QstringToCharArray(row[0], instructorFact);
                }

                char holdStudentFaculty[100];
                tempStr.str("");
                tempStr.clear();
                tempStr<<"select faculty from student where ID = " <<s_id;
                std::string holdQuery = tempStr.str();
                status = mysql_query(con, holdQuery.c_str());
                if(status != 0){
                    std::cout<<"There was a problem getting faculty from student table";
                }
                else if(status == 0){
                    res = mysql_use_result(con);
                    while((row = mysql_fetch_row(res)) != NULL){
                        QstringToCharArray(row[0], holdStudentFaculty);
                    }
                    if(strcmp(holdStudentFaculty, instructorFact) != 0){
                        std::cout<<"holdStudentFaculty: " <<holdStudentFaculty <<"-> instructorFaculty: " <<instructorFact <<std::endl;
                        QMessageBox::information(this, "Invalid",
                                                 "Instructor to be assigned to student should be from the same faculty");
                    }
                    else{
                        tempStr.str("");
                        tempStr.clear();
                        tempStr<<"insert ignore into advisor(s_id, i_id) values('" <<s_id <<"', '" <<i_id <<"')";
                        std::string query = tempStr.str();
                        std::cout<<query;
                        status = mysql_query(con, query.c_str());
                        if(status == 0){
                            QMessageBox::information(this, "Success", "Successful entry!");
                        }
                        else{
                            QMessageBox::information(this, "Insert error", "There was a problem inserting the data to database");

                        }

                    }
                }
            }


        }

    }

    mysql_free_result(res);

}
