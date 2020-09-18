#include "consume_tablemodel.h"
#include "database/database_api.h"
#include <QSqlRecord>
#include <QSqlField>
/**************************************
 *作者: huhan_h@163.com
 *日期: 2020-09-20
 *描述: 用户信息表的model
***************************************/
Consume_TableModel::Consume_TableModel(QObject *parent) : QSqlTableModel(parent)
{
    tableName = TABLE_NAME_CONSUME;
    header<<QObject::trUtf8("卡号")<<
            QObject::trUtf8("姓名")<<
            QObject::trUtf8("商户编号")<<
            QObject::trUtf8("商品编号")<<
            QObject::trUtf8("购买时间")<<
            QObject::trUtf8("商品数量")<<
            QObject::trUtf8("扣款金额");
}

/**
 * @brief Consume_TableModel::createTable
 * @param tableName 数据块表名称
 * 用于创建消费记录表
 */
void Consume_TableModel::createTable()
{
    QSqlQuery query;
    QString str;
    str  = tr("create table ") + tableName + tr(" ( ");
    str += header.at(0) + tr(" varchar not null, ");//卡号
    str += header.at(1) + tr(" varchar, ");//姓名
    str += header.at(2) + tr(" varchar, ");//商户编号
    str += header.at(3) + tr(" varchar, ");//商品编号
    str += header.at(4) + tr(" varchar, ");//购买时间
    str += header.at(5) + tr(" varchar, ");//商品数量
    str += header.at(6) + tr(" varchar) ");//扣款金额
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
 * @brief Consume_TableModel::restore
 * 绑定表名
 */
void Consume_TableModel::bindTable()
{
    setTable(tableName);
    select();
}

/**
 * @brief Consume_TableModel::findRecord
 * @param tagId
 * @return QSqlRecord型记录集
 * 根据卡号查找记录
 */
QSqlRecord Consume_TableModel::findRecord(const QString &tagId)
{
    setFilter(QObject::tr("卡号= '%1'").arg(tagId)); //根据姓名进行筛选
    select();
    return record();
}

/**
 * @brief Consume_TableModel::deleteByTagId
 * @param tagId 卡号
 * @return 如果成功返回true，否则false
 * 根据卡号删除记录
 */
bool Consume_TableModel::deleteByTagId(const QString &tagId)
{
    for(int row=0; row<rowCount(); row++){
        if(data(index(row, 0)).toString() == tagId)
            removeRow(row);
    }
    return submitAll();
}

/**
 * @brief Consume_TableModel::addRecord
 * @param tagId 卡号
 * @param username 姓名
 * @param merchantId 商户编号
 * @param productId 商品编号
 * @param buyTime 购买时间
 * @param num 购买数量
 * @param payMoney 支付金额
 * @return 记录条数
 * 添加记录
 */
int Consume_TableModel::addRecord(QString &tagId, QString &username, QString &merchantId, QString &productId, QString &buyTime, QString num, QString payMoney)
{
    QSqlRecord record;//也可以直接使用sql语句进行,但是sql语句更容易写错
    record.append(QSqlField(header.at(0), QVariant::String));
    record.append(QSqlField(header.at(1), QVariant::String));
    record.append(QSqlField(header.at(2), QVariant::String));
    record.append(QSqlField(header.at(3), QVariant::String));
    record.append(QSqlField(header.at(4), QVariant::String));
    record.append(QSqlField(header.at(5), QVariant::String));
    record.append(QSqlField(header.at(6), QVariant::String));
    record.setValue(0, QVariant(tagId));
    record.setValue(1, QVariant(username));
    record.setValue(2, QVariant(merchantId));
    record.setValue(3, QVariant(productId));
    record.setValue(4, QVariant(buyTime));
    record.setValue(5, QVariant(num));
    record.setValue(6, QVariant(payMoney));
    insertRecord(-1, record);//插入表末尾
    return rowCount();//返回记录条数
}


