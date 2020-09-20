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
    serialPortThread = new SerialPortThread(this); //串口线程
    serialPort = new QSerialPort(this);
    m1356dll = new M1356Dll(); //协议库
    settingsDialog = new SettingsDialog(this);

    ui->action_disconnect->setEnabled(false);
    this->setWindowTitle(CURRENT_VERSION);
    ui->stackedWidget->setCurrentIndex(0);

    this->handConnect();
    this->addWidgets();
}

MainWindow::~MainWindow()
{
    delete m1356dll;
    delete settingsDialog;
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
    connect(settingsDialog,SIGNAL(applySettings()),this,SLOT(updateConnect()));
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
        serialPortThread->stopThread();
        DB_Close();
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

/**
 * @brief MainWindow::Connect
 * 连接菜单点击事件
 */
void MainWindow::Connect()
{
    settingsDialog->setWindowTitle("读卡器连接配置");
    settingsDialog->exec();
}

/**
 * @brief MainWindow::updateConnect
 * 更新串口参数
 */
void MainWindow::updateConnect()
{
    serialPort->setPortName(settingsDialog->settings().name);
    serialPort->setBaudRate(settingsDialog->settings().baudRate);
    serialPort->setDataBits(settingsDialog->settings().dataBits);
    serialPort->setParity(settingsDialog->settings().parity);
    serialPort->setStopBits(settingsDialog->settings().stopBits);
    serialPort->setFlowControl(settingsDialog->settings().flowControl);
    if(serialPort->isOpen())
    {
        serialPort->close();
    }
    if(serialPort->open(QIODevice::ReadWrite))
    {
        ui->action_connect->setEnabled(false);
        ui->action_disconnect->setEnabled(true);
        serialPortThread->setSerialPort(serialPort);
        serialPortThread->setRetryTimes(RETRY_20);
        serialPortThread->start();
        uint16 frameLen;
        uint8 data[1];
        uint8 *p;
        data[0] = RC632_WORK_MODEL_1443A;
        p = m1356dll->RC632_SendCmdReq(RC632_CMD_CONFIG_ISOTYPE,data,1);
        frameLen = BUILD_UINT16(p[0], p[1]);
        serialPortThread->writeData((char *)(p + 2 ),frameLen);
        ui->statusBar->showMessage(tr("Connected to %1 : %2, %3, %4, %5, %6 success").arg(
                                       settingsDialog->settings().name).arg(
                                       settingsDialog->settings().baudRate).arg(
                                       settingsDialog->settings().dataBits).arg(
                                       settingsDialog->settings().parity).arg(
                                       settingsDialog->settings().stopBits).arg(
                                       settingsDialog->settings().flowControl));
    }else{
        QMessageBox::critical(this, tr("Error"), serialPort->errorString());
        ui->statusBar->showMessage(tr("Open error"));
    }
}

/**
 * @brief MainWindow::Disconnect
 * 与读卡器断开连接，关闭串口，停止读写线程
 */
void MainWindow::Disconnect()
{
    if(serialPort->isOpen())
    {
        serialPort->close();
        ui->action_connect->setEnabled(true);
        ui->action_disconnect->setEnabled(false);
        ui->statusBar->showMessage(tr("Close Success"));
    }
}

/**
 * @brief MainWindow::onOperationError
 * @param msg 发送的命令
 * 当串口写入数据无响应时调用该方法
 */
void MainWindow::onOperationError(QString msg)
{
     QMessageBox::warning(this,tr("温馨提示"),msg,QMessageBox::Yes);
}

//显示发送消息
void MainWindow::onSendMessage(char *data, int frameLen)
{
    Q_UNUSED(data);
    Q_UNUSED(frameLen);
    //这里没用到,这里就是提供一个接口,方便您在学习后使用
}

/**
 * @brief MainWindow::on_serialMsgreceived
 * @param bytes 接收到的数据字节数组
 * 串口接收消息后的处理槽函数
 */
void MainWindow::on_serialMsgreceived(QByteArray bytes){
        M1356_RspFrame_t frame = m1356dll->M1356_RspFrameConstructor(bytes);
         if(frame.status.left(2) == "00")
         {
            if(frame.cmd.remove(" ") == "0102")//寻卡
            {
                uint16 frameLen;
                quint8 buffer[1];
                uint8 *p;
                memset(buffer, 0, 1);
                buffer[0] = 0x04;
                p = m1356dll->RC632_SendCmdReq(RC632_CMD_ANTICOLL, buffer, 1);
                frameLen = BUILD_UINT16(p[0], p[1]);
                serialPortThread->writeData((char *)(p + 2 ),frameLen);
            }
            else if(frame.cmd.remove(" ") == "0202")//寻卡结果
            {
                uint16 frameLen;
                quint8 buffer[4];
                uint8 *p;
                memset(buffer, 0, 4);
                QSTRING_TO_HEX(frame.vdata.remove(" "),buffer,4); // 卡号
                p = m1356dll->RC632_SendCmdReq(RC632_CMD_SELECT,buffer,4);
                frameLen = BUILD_UINT16(p[0], p[1]);
                serialPortThread->writeData((char *)(p + 2 ),frameLen);
                tagId = frame.vdata.remove(" ");
            }
            else if(frame.cmd.remove(" ") == "0302")
            {
                emit sendCardId(tagId);
            }
         }
        else
         {
             if(frame.cmd.remove(" ") == "0102")//寻卡
             {
                 QMessageBox::warning(this,tr("温馨提示"),tr("寻卡失败，请调整卡与读卡器的距离后再试！"),QMessageBox::Yes);
             }
             else if(frame.cmd.remove(" ") == "0202")//寻卡结果
             {
                 QMessageBox::warning(this,tr("温馨提示"),tr("A卡防冲撞失败，请调整卡与读卡器的距离后再试！"),QMessageBox::Yes);
             }
         }
}
