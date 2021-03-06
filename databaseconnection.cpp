#include "databaseconnection.h"
#include <QMessageBox>
#include <cstring>
#include <string.h>
#include <mysql/mysql.h>

MYSQL *mysql_connection_setup(struct connection_details mysql_details){
    MYSQL *connection;
    connection = mysql_init(NULL);

    if(!mysql_real_connect(connection, mysql_details.server, mysql_details.user,
                           mysql_details.password, mysql_details.database, 0, NULL, 0)){
        QMessageBox msgbox;
        msgbox.setText("Connection failed");
        msgbox.exec();
        exit(1);
    }
    return connection;
}

void QstringToCharArray(QString stringToConvert, char newString[]){
    //int size = strlen(newString);
    const QByteArray temp = stringToConvert.toUtf8();
    newString[qMin(99, temp.size())] = '\0';
    std::copy(temp.constBegin(),
              temp.constBegin() + qMin(99, temp.size()), newString);
}

MYSQL_RES* mysql_execute_query(MYSQL* connection, const char *sql_query){
     if(mysql_query(connection, sql_query)){
         std::cout << "MySQL Error: " << mysql_error(connection) << std::endl;
         exit(1);
     }
     return mysql_use_result(connection);
}
int QStringToInt(QString str, int)
{
    return str.toInt();
}
