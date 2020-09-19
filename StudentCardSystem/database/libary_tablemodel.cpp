#include "libary_tablemodel.h"
#include "database/database_api.h"
/**************************************
 *作者: huhan_h@163.com
 *日期: 2020-09-20
 *描述: 进出图书馆记录表的model
***************************************/

Libary_TableModel::Libary_TableModel(QObject *parent) : QSqlTableModel(parent)
{
    tableName = TABLE_NAME_LIBREG;
    header<<QObject::trUtf8("卡号")<<
            QObject::trUtf8("姓名")<<
            QObject::trUtf8("时间")<<
            QObject::trUtf8("状态")<<
            QObject::trUtf8("停留时间");
}

/**
 * @brief Libary_TableModel::createTable
 * @param tableName 数据块表名称
 * 用于创建进出图书馆记录表
 */
void Libary_TableModel::createTable()
{
    QSqlQuery query;
    QString str;
    str  = tr("create table ") + tableName + tr(" ( ");
    str += header.at(0) + tr(" varchar not null, ");//卡号
    str += header.at(1) + tr(" varchar, ");//姓名
    str += header.at(2) + tr(" varchar, ");//时间
    str += header.at(3) + tr(" varchar, ");//状态
    str += header.at(4) + tr(" varchar) ");//停留时间

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
 * @brief Libary_TableModel::restore
 * 绑定表名
 */
void Libary_TableModel::bindTable()
{
    setTable(tableName);
    select();
}

/**
 * @brief Libary_TableModel::findRecord
 * @param tagId 卡号
 * @return QSqlRecord型记录集
 * 根据卡号查找记录
 */
QSqlRecord Libary_TableModel::findRecord(const QString &tagId)
{
    for(int row=0; row<rowCount(); row++){
        if(data(index(row, 0)).toString() == tagId)
            return record(row);
    }
    return QSqlRecord();
}

/**
 * @brief Libary_TableModel::findNewRecord
 * @param tagId 卡号
 * @return 记录索引
 * 根据卡号查找最新记录
 */
int Libary_TableModel::findNewRecord(const QString &tagId)
{
    int count = rowCount();
    for(int row=count-1; 0 <= row; row--){//从表尾开始查找
        if(data(index(row, 0)).toString() == tagId)
            return row;
    }
    return -1;
}

/**
 * @brief Libary_TableModel::deleteByTagId
 * @param tagId 卡号
 * @return 如果成功返回true，否则false
 * 根据卡号删除记录
 */
bool Libary_TableModel::deleteByTagId(const QString &tagId)
{
    for(int row=0; row<rowCount(); row++){
        if(data(index(row, 0)).toString() == tagId)
            removeRow(row);
    }
    return submitAll();
}

/**
 * @brief Libary_TableModel::addRecord
 * @param tagId 卡号
 * @param name 姓名
 * @param time 时间
 * @param status 进出状态
 * @param duration 停留时间
 * @return 记录条数
 * 添加记录
 */
int Libary_TableModel::addRecord(QString tagId, QString name, QString time, QString status, QString duration)
{
    QSqlRecord record;//也可以直接使用sql语句进行,但是sql语句更容易写错
    record.append(QSqlField(header.at(0), QVariant::String));
    record.append(QSqlField(header.at(1), QVariant::String));
    record.append(QSqlField(header.at(2), QVariant::String));
    record.append(QSqlField(header.at(3), QVariant::String));
    record.append(QSqlField(header.at(4), QVariant::String));
    record.setValue(0, QVariant(tagId));
    record.setValue(1, QVariant(name));
    record.setValue(2, QVariant(time));
    record.setValue(3, QVariant(status));
    record.setValue(4, QVariant(duration));
    insertRecord(-1, record);
    return rowCount();
}

