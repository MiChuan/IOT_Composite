#include "merchant_tablemodel.h"
#include "database/database_api.h"
#include <QSqlRecord>
#include <QSqlField>
/**************************************
 *作者: huhan_h@163.com
 *日期: 2020-09-20
 *描述: 商户信息表的model
***************************************/

Merchant_TableModel::Merchant_TableModel(QObject *parent) : QSqlTableModel(parent)
{
    tableName = TABLE_NAME_MERINFO;
    header<<QObject::trUtf8("商户编号")<<
            QObject::trUtf8("商户名称");
}

/**
 * @brief Merchant_TableModel::createTable
 * @param tableName 数据块表名称
 * 用于创建商户信息表
 */
void Merchant_TableModel::createTable()
{
    QSqlQuery query;
    QString str;
    str  = tr("create table ") + tableName + tr(" ( ");
    str += header.at(0) + tr(" varchar not null, ");//商户编号
    str += header.at(1) + tr(" varchar) ");//商户名称

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
 * @brief Merchant_TableModel::restore
 * 绑定表名
 */
void Merchant_TableModel::bindTable()
{
    setTable(tableName);
    select();
}

/**
 * @brief Merchant_TableModel::findRecord
 * @param merchantId 商户编号
 * @return QSqlRecord型记录集
 * 根据商户编号查找记录
 */
QSqlRecord Merchant_TableModel::findRecord(const QString &merchantId)
{
    setFilter(QObject::tr("商户编号= '%1'").arg(merchantId)); //根据商品编号进行筛选
    select();
    return record();
}

/**
 * @brief Merchant_TableModel::deleteByProductId
 * @param merchantId 商户编号
 * @return 如果成功返回true，否则false
 * 根据商品编号删除记录
 */
bool Merchant_TableModel::deleteByProductId(const QString &merchantId)
{
    for(int row=0; row<rowCount(); row++){
        if(data(index(row, 0)).toString() == merchantId)
            removeRow(row);
    }
    return submitAll();
}

/**
 * @brief Merchant_TableModel::addRecord
 * @param merchantId 商户编号
 * @param name 商户名称
 * @return 记录条数
 * 添加记录
 */
int Merchant_TableModel::addRecord(QString &merchantId, QString &name)
{
    QSqlRecord record;//也可以直接使用sql语句进行,但是sql语句更容易写错
    record.append(QSqlField(header.at(0), QVariant::String));
    record.append(QSqlField(header.at(1), QVariant::String));
    record.setValue(0, QVariant(merchantId));
    record.setValue(1, QVariant(name));
    insertRecord(-1, record);//插入表末尾
    return rowCount();//返回记录条数
}

