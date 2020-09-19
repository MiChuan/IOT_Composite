#ifndef SCHOOL_TABLEMODEL_H
#define SCHOOL_TABLEMODEL_H
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QSqlField>
#include <QString>
#include <QDebug>
/**************************************
 *作者: huhan_h@163.com
 *日期: 2020-09-20
 *描述: 进出学校记录表的model
***************************************/

class School_TableModel : public QSqlTableModel
{
    Q_OBJECT
private:
    QString tableName; //表名

    QStringList header;//表头

public:
    explicit School_TableModel(QObject *parent = 0);

    void createTable();//创建表

    void bindTable(void);//绑定表

    //根据卡号查找记录,返回该记录
    QSqlRecord findRecord(const QString &tagId);

    //根据卡号查找最新记录,返回该记录索引
    int findNewRecord(const QString &tagId);

    //根据tagId删除记录
    bool deleteByTagId(const QString &tagId);

    //添加记录
    int addRecord(QString tagId, QString name, QString time,
                  QString status, QString duration);
};

#endif // SCHOOL_TABLEMODEL_H
