#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

#include <mysql/mysql.h>
#include <QString>

struct connection_details{
  const char *server = "localhost",
  *user="root",
  *password = " kasbeat2,",
  *database = "ahmadDatabase";
};

MYSQL *mysql_connection_setup(struct connection_details mysql_details);
void QstringToCharArray(QString, char[]);
MYSQL_RES* mysql_execute_query(MYSQL* connection, const char *sql_query);
#endif // DATABASECONNECTION_H
