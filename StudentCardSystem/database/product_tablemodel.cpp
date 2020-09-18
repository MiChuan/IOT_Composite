#include "product_tablemodel.h"
#include "database/database_api.h"
#include <QSqlRecord>
#include <QSqlField>
/**************************************
 *作者: huhan_h@163.com
 *日期: 2020-09-20
 *描述: 商品信息表的model
***************************************/
Product_TableModel::Product_TableModel(QObject *parent) : QSqlTableModel(parent)
{
    tableName = TABLE_NAME_PRODINFO;
    header<<QObject::trUtf8("商品编号")<<
            QObject::trUtf8("单价")<<
            QObject::trUtf8("单位");
}

/**
 * @brief Product_TableModel::createTable
 * @param tableName 数据块表名称
 * 用于创建商品信息表
 */
void Product_TableModel::createTable()
{
    QSqlQuery query;
    QString str;
    str  = tr("create table ") + tableName + tr(" ( ");
    str += header.at(0) + tr(" varchar not null, ");//商品编号
    str += header.at(1) + tr(" varchar, ");//单价
    str += header.at(2) + tr(" varchar) ");//单位

    qDebug()<<"Sql: " << str.toUtf8().data();
    bool ret = query.exec(str);
    if(ret == true){
        qDebug()<<tableName<<QObject::tr(" table create success");
    }
    else{
        qDebug()<<tableName<<QObject::tr(" table create failed");
    }
}

/**
 * @brief Product_TableModel::restore
 * 绑定表名
 */
void Product_TableModel::bindTable()
{
    setTable(tableName);
    select();
}

/**
 * @brief Product_TableModel::findRecord
 * @param productId 商品编号
 * @return QSqlRecord型记录集
 * 根据商品编号查找记录
 */
QSqlRecord Product_TableModel::findRecord(const QString &productId)
{
    setFilter(QObject::tr("商品编号= '%1'").arg(productId)); //根据商品编号进行筛选
    select();
    return record();
}

/**
 * @brief Product_TableModel::deleteByProductId
 * @param productId 商品编号
 * @return 如果成功返回true，否则false
 * 根据商品编号删除记录
 */
bool Product_TableModel::deleteByProductId(const QString &productId)
{
    for(int row=0; row<rowCount(); row++){
        if(data(index(row, 0)).toString() == productId)
            removeRow(row);
    }
    return submitAll();
}

/**
 * @brief Product_TableModel::addRecord
 * @param productId 商品编号
 * @param price 单价
 * @param unit 单位
 * @return 记录条数
 * 添加记录
 */
int Product_TableModel::addRecord(QString &productId, QString &price, QString &unit)
{
    QSqlRecord record;//也可以直接使用sql语句进行,但是sql语句更容易写错
    record.append(QSqlField(header.at(0), QVariant::String));
    record.append(QSqlField(header.at(1), QVariant::String));
    record.append(QSqlField(header.at(2), QVariant::String));
    record.setValue(0, QVariant(productId));
    record.setValue(1, QVariant(price));
    record.setValue(2, QVariant(unit));
    insertRecord(-1, record);//插入表末尾
    return rowCount();//返回记录条数
}



