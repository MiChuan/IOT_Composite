#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tools/tools.h"
#include <QMessageBox>
#include <QHBoxLayout>
#include <QIcon>
/**************************************
 *作者: huhan_h@163.com
 *日期: 2020-09-20
 *描述: 应用程序主页面窗口,其他各个页面都通过此页面链接过去
***************************************/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->IsLogin = false; //设置未登录
    //serialPortThread = new SerialPortThread(this); //串口线程
    //serialPort = new QSerialPort(this);
    //m1356dll = new M1356Dll(); //协议库
    //settingsDialog = new SettingsDialog(this);

    ui->action_disconnect->setEnabled(false);
    this->setWindowTitle(CURRENT_VERSION);
    //ui->stackedWidget->setCurrentIndex(0);

    this->handConnect();
    //this->addWidgets();
}

MainWindow::~MainWindow()
{
    delete m1356dll;
    //delete settingsDialog;
    delete ui;
}

/**
 * @brief MainWindow::addWidgets
 * 添加子页面
 */
void MainWindow::addWidgets()
{

}

/**
 * @brief MainWindow::handConnect
 * 连接槽函数
 */
void MainWindow::handConnect()
{
    connect(ui->action_about,SIGNAL(triggered(bool)),this,SLOT(About()));
}

//窗口关闭响应事件
void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox message;
    message.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
    message.setWindowTitle(tr("温馨提示"));
    message.setIcon(QMessageBox::Warning);
    message.setText(tr("您确定要退出吗？"));
    if (message.exec()==QMessageBox::Yes)
    {
        //serialPortThread->stopThread();
        //DB_Close();
    }
    else
    {
        event->ignore();
    }
}

/**
 * @brief MainWindow::About
 * 关于按钮点击事件
 */
void MainWindow::About()
{
    QString text = tr("软件版本:%1\r\n作者:%2\r\n描述:%3")
            .arg(CURRENT_VERSION)
            .arg(tr("huhan_h@163.com"))
            .arg(tr("基于校园卡的电子钱包和学生信息管理系统"));
    QMessageBox::information(this,tr("帮助"),text,QMessageBox::Yes);
}
