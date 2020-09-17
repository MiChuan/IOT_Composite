#ifndef DATABASE_API_H
#define DATABASE_API_H
#include <QtSql/QSqlTableModel>
//***************表名,数据库名****************//
#define DATABASE_NAME   "db_StudentCardSystem.db"
#define TABLE_NAME_USERINFO   "table_user"
#define TABLE_NAME_CONSUME "table_consume"
#define TABLE_NAME_PRODINFO "table_prodinfo"
#define TABLE_NAME_MERINFO   "table_merinfo"
#define TABLE_NAME_RECHARGE "table_Recharge"
#define TABLE_NAME_DORREG "table_dorreg"
#define TABLE_NAME_LIBREG "table_libreg"
#define TABLE_NAME_SCHREG "table_schreg"

//***************外部API接口*****************//
extern void DB_Init();//DB初始化
extern void DB_Close();//DB关闭
extern QStringList getTableNames();//获取当前DB所有表的表名

#endif // DATABASE_API_H
