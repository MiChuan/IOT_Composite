#ifndef RECHARGETABLEMODEL_H
#define RECHARGETABLEMODEL_H
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
 *描述: 充值记录表的model
***************************************/
class RechargeTableModel : public QSqlTableModel
{
    Q_OBJECT
private:
    QString tableName; //表名

    QStringList header;//表头

public:

    explicit RechargeTableModel(QObject *parent = 0);

    void createTable();//创建表

    void bindTable(void);//绑定表

    //根据卡号查找记录,返回该记录
    QSqlRecord findRecord(const QString &tagId);

    //根据tagId删除记录
    bool deleteByTagId(const QString &tagId);

    //添加记录
    int addRecord(QString tagId, QString rechargeMoney, QString time,
                  QString addr, QString current_value);
};

#endif // RECHARGETABLEMODEL_H
