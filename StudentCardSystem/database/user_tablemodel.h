#ifndef USER_TABLEMODEL_H
#define USER_TABLEMODEL_H

#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QString>
#include <QDebug>
/**************************************
 *作者: huhan_h@163.com
 *日期: 2020-09-20
 *描述: 用户信息表的model
***************************************/
class User_TableModel : public QSqlTableModel
{
    Q_OBJECT
private:
    QString tableName;//表名

    QStringList header;//表头

public:
    explicit User_TableModel(QObject *parent = 0);
    void createTable();//创建表
    void bindTable(void);//绑定表
    int findRecordById(const QString userId);//根据用户Id查询记录
    bool isActivated(const QString userId);//查询指定Id卡是否激活
    int activate(const QString userId);//激活未激活的卡
    int suspend(const QString userId);//挂失卡
    int balance(const QString userId);//查询余额
    int nopwdMoney(const QString userId);//查询免密金额
    bool checkPwd(const QString userId, QString pwd);//校验消费密码
    //插入记录
    bool insertRecords(QString userId,QString userName,QString telephone,QString balance,QString password,QString money);
    //删除记录
    bool deleteRecords(int row);
};

#endif // USER_TABLEMODEL_H
