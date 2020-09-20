#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include "database/database_api.h"
#include "pages/pages.h"
#include "serialThread/serialportthread.h"
#include "inc/m1356dll.h"
#include <QLabel>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void addWidgets(); //加载页面
    void handConnect();//信号插槽连接

private slots:
    void About(); //关于
    void Connect(); //连接
    void Disconnect(); //断开连接
    void onOperationError(QString msg); //串口发生错误时接收错误信息槽
    void onSendMessage(char *data, int frameLen);//串口消息发送槽
    void on_serialMsgreceived(QByteArray bytes);//串口消息接收槽
    void updateConnect(); //更新连接

signals:

    void sendAction(QAction *action);

    void sendCardId(QString tagID);

protected:
    void closeEvent(QCloseEvent *event); //窗口关闭时调用

private:
    Ui::MainWindow *ui;
    M1356Dll *m1356dll; //13.56M的库对象
    SerialPortThread *serialPortThread; //自定义串口处理线程
    QSerialPort *serialPort; //串口类对象
    SettingsDialog *settingsDialog; //串口配置对话框
    QString tagId;//卡号
};

#endif // MAINWINDOW_H
