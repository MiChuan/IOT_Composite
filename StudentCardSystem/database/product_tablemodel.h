#ifndef PRODUCT_TABLEMODEL_H
#define PRODUCT_TABLEMODEL_H

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
 *描述: 商品信息表的model
***************************************/
class Product_TableModel : public QSqlTableModel
{
    Q_OBJECT
private:
    QString tableName; //表名

    QStringList header;//表头

public:
    explicit Product_TableModel(QObject *parent = 0);

    void createTable();//创建表

    void bindTable(void);//绑定表

    //根据商品编号查找记录,返回该记录
    QSqlRecord findRecord(const QString &productId);

    //根据productId删除记录
    bool deleteByProductId(const QString &productId);

    //添加记录
    int addRecord(QString &productId,QString &price,QString &unit);

};

#endif // PRODUCT_TABLEMODEL_H
