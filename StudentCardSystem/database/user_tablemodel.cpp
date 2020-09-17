#include "user_tablemodel.h"
#include "database/database_api.h"
#include <QSqlRecord>
#include <QSqlField>
/**************************************
 *作者: huhan_h@163.com
 *日期: 2020-09-20
 *描述: 用户信息表的model
***************************************/
User_TableModel::User_TableModel(QObject *parent) : QSqlTableModel(parent)
{
    tableName = TABLE_NAME_USERINFO;
    header<<QObject::trUtf8("卡号")<<QObject::trUtf8("姓名")<<
            QObject::trUtf8("手机")<< QObject::trUtf8("是否激活")<<
            QObject::trUtf8("余额")<<QObject::trUtf8("消费密码")<<
            QObject::trUtf8("消费限额");
}

/**
 * @brief User_TableModel::createTable
 * @param tableName 数据块表名称
 * 用于创建user表
 */
void User_TableModel::createTable()
{
    QSqlQuery query;
    QString str;
    str  = tr("create table ") + tableName + tr(" ( ");
    str += header.at(0) + tr(" varchar PRIMARY KEY not null, ");//卡号
    str += header.at(1) + tr(" varchar, ");//姓名
    str += header.at(2) + tr(" varchar, ");//手机
    str += header.at(3) + tr(" varchar, ");//激活
    str += header.at(4) + tr(" varchar, ");//余额
    str += header.at(5) + tr(" varchar, ");//消费密码
    str += header.at(6) + tr(" varchar) ");//免密金额
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
 * @brief User_TableModel::bindTable
 * 绑定表名
 */
void User_TableModel::bindTable(void)
{
    setTable(tableName);
    select();
}

/**
 * @brief User_TableModel::findRecordById
 * @param userId 人员编号
 * @return 索引
 * 根据卡号查找记录
 */
int User_TableModel::findRecordById(const QString userId)
{
    int count = rowCount();
    for(int row=0; row < count; row++){
        if(data(index(row, 0)).toString() == userId)
            return row;
    }
    return -1;
}
