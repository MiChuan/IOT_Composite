#ifndef USER_TABLEMODEL_H
#define USER_TABLEMODEL_H

#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QString>
#include <QDebug>
/**************************************
 *作者: huhan_h@163.com
 *日期: 2020-09-20
 *描述: 用户信息表的model
***************************************/
class User_TableModel : public QSqlTableModel
{
    Q_OBJECT
private:
    QString tableName;//表名

    QStringList header;//表头

public:
    explicit User_TableModel(QObject *parent = 0);
    void createTable();//创建表
    void bindTable(void);//绑定表
    int findRecordById(const QString userId);//根据用户Id查询记录
    QSqlRecord findRecordByName(const QString userName);//根据用户名查询记录
    //插入记录
    bool insertRecords(QString userId,QString userName,QString telephone,QString activation,QString balance,QString password,QString money);
    //删除记录
    bool deleteRecords(int row);
};

#endif // USER_TABLEMODEL_H
