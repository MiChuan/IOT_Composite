#ifndef CONSUME_TABLEMODEL_H
#define CONSUME_TABLEMODEL_H

#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QSqlField>
#include <QString>
#include <QDebug>

class Consume_TableModel : public QSqlTableModel
{
    Q_OBJECT
private:
    QString tableName; //表名

    QStringList header;//表头

public:
    explicit Consume_TableModel(QObject *parent = 0);
    void createTable();//创建表

    void bindTable(void);//绑定表

    //根据卡号查找记录,返回该记录
    QSqlRecord findRecord(const QString &tagId);

    //根据tagId删除记录
    bool deleteByTagId(const QString &tagId);

    //添加记录
    int addRecord(QString &tagId,QString &username,QString &merchantId,QString &productId,QString &buyTime,QString num,QString payMoney);
};

#endif // CONSUME_TABLEMODEL_H
