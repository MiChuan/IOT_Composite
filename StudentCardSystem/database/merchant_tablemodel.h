#ifndef MERCHANT_TABLEMODEL_H
#define MERCHANT_TABLEMODEL_H

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
 *描述: 商户信息表的model
***************************************/
class Merchant_TableModel : public QSqlTableModel
{
    Q_OBJECT
private:
    QString tableName; //表名

    QStringList header;//表头

public:
    explicit Merchant_TableModel(QObject *parent = 0);

    void createTable();//创建表

    void bindTable(void);//绑定表

    //根据商户编号查找记录,返回该记录
    QSqlRecord findRecord(const QString &merchantId);

    //根据merchantId删除记录
    bool deleteByProductId(const QString &merchantId);

    //添加记录
    int addRecord(QString &merchantId,QString &name);
};

#endif // MERCHANT_TABLEMODEL_H
