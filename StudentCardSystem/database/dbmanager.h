#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>
#include "consume_tablemodel.h"
#include "database_api.h"
#include "dormitory_tablemodel.h"
#include "libary_tablemodel.h"
#include "merchant_tablemodel.h"
#include "product_tablemodel.h"
#include "rechargetablemodel.h"
#include "school_tablemodel.h"
#include "user_tablemodel.h"
/**************************************
 *作者: jianghj@up-tech.com
 *日期: 2016-09-20
 *描述: 数据库管理者
***************************************/
class DBManager : public QObject
{
    Q_OBJECT
public:
    explicit DBManager(QObject *parent = 0);

    void dbClose(); //关闭数据库

    QStringList getTableNames();//获取所有表的表名

private:
    QSqlDatabase db;//sqlite database

    //创建数据库
    bool createDB(const QString &dbName);

    //检测该表是否存在
    bool tableExist(const QString &tableName);

signals:

public slots:
};

#endif // DBMANAGER_H
