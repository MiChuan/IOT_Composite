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
            QObject::trUtf8("免密金额");
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
 * @param userId 卡号
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

/**
 * @brief User_TableModel::isActivated
 * @param userId 卡号
 * @return 是否激活
 * 查询指定卡号的卡是否激活
 */
bool User_TableModel::isActivated(const QString userId)
{
    int count = rowCount();
    for(int row=0; row < count; row++){
        if(data(index(row, 0)).toString() == userId)
            return data(index(row, 3)).toString() == "Y";
    }
    return false;
}

/**
 * @brief User_TableModel::activate
 * @param userId 卡号
 * @return 激活卡的索引
 * 激活指定卡号的卡
 */
int User_TableModel::activate(const QString userId)
{
    int count = rowCount();
    for(int row=0; row < count; row++){
        if(data(index(row, 0)).toString() == userId){
            QSqlQuery query;
            QString str;
            str  = tr("update ") + tableName + tr(" set ");
            str += header.at(3) + tr(" = 'Y' ");
            str += tr(" where ") + header.at(0) + tr(" = ") + userId + tr(";");
            qDebug()<<"Sql: " << str.toUtf8().data();
            bool ret = query.exec(str);
            if(ret == true){
                qDebug()<<tableName<<QObject::tr(" table update success");
                return row;
            }
            else{
                qDebug()<<tableName<<QObject::tr(" table update failed");
                return -1;
            }
        }
    }
    return -1;
}

/**
 * @brief User_TableModel::suspend
 * @param userId 卡号
 * @return 挂失卡的索引
 * 挂失指定卡号的卡
 */
int User_TableModel::suspend(const QString userId)
{
    int count = rowCount();
    for(int row=0; row < count; row++){
        if(data(index(row, 0)).toString() == userId){
            QSqlQuery query;
            QString str;
            str  = tr("update ") + tableName + tr(" set ");
            str += header.at(3) + tr(" = 'N' ");
            str += tr(" where ") + header.at(0) + tr(" = ") + userId + tr(";");
            qDebug()<<"Sql: " << str.toUtf8().data();
            bool ret = query.exec(str);
            if(ret == true){
                qDebug()<<tableName<<QObject::tr(" table update success");
                return row;
            }
            else{
                qDebug()<<tableName<<QObject::tr(" table update failed");
                return -1;
            }
        }
    }
    return -1;
}

/**
 * @brief User_TableModel::balance
 * @param userId 卡号
 * @return 余额
 * 查询卡内余额
 */
int User_TableModel::balance(const QString userId)
{
    int count = rowCount();
    for(int row=0; row < count; row++){
        if(data(index(row, 0)).toString() == userId)
            return data(index(row, 4)).toInt();
    }
    return -1;
}

/**
 * @brief User_TableModel::nopwdMoney
 * @param userId 卡号
 * @return 免密金额
 * 查询免密金额
 */
int User_TableModel::nopwdMoney(const QString userId)
{
    int count = rowCount();
    for(int row=0; row < count; row++){
        if(data(index(row, 0)).toString() == userId)
            return data(index(row, 6)).toInt();
    }
    return -1;
}

/**
 * @brief User_TableModel::checkPwd
 * @param userId 卡号, pwd 密码
 * @return 成功返回true，失败返回false
 * 校验消费密码
 */
bool User_TableModel::checkPwd(const QString userId, QString pwd)
{
    int count = rowCount();
    for(int row=0; row < count; row++){
        if(data(index(row, 0)).toString() == userId)
            return data(index(row, 5)).toString() == pwd;
    }
    return false;
}

/**
 * @brief User_TableModel::insertRecords
 * @param userId 卡号, userNmae 用户名
 * @param telephone 电话, balance 余额
 * @param password 消费密码, money 免密金额
 * @return 成功返回true，失败返回false
 * 插入记录
 */
bool User_TableModel::insertRecords(QString userId, QString userName, QString telephone, QString balance, QString password, QString money)
{
    QSqlQuery query;
    QString str;
    str  = tr("insert into ") + tableName + tr(" values( \"%1\" , \"%2\" , \"%3\" , \"%4\" , \"%5\" , \"%6\" , \"%7\" ) ")
           .arg(userId).arg(userName).arg(telephone).arg("Y").arg(balance).arg(password).arg(money);
    qDebug()<<"Sql: " << str.toUtf8().data();
    return query.exec(str);
}

/**
 * @brief PersonTableModel::deleteRecords
 * @param row 待删除的行
 * @return  如果删除成功返回true，否则false
 * 删除一行记录
 */
bool User_TableModel::deleteRecords(int row)
{
    return removeRow(row);
}


