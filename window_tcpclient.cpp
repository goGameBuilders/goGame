#include "window_tcpclient.h"
#include "ui_window_tcpclient.h"
#include "window_play.h"
#include "ui_window_play.h"

Window_TCPClient::Window_TCPClient(goGamePlatform* _gameplatform, int _gameType, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Window_TCPClient), gameplatform(_gameplatform)
{
    ui->setupUi(this);
    gameType = _gameType;
    tcpSocket = nullptr;
    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket, SIGNAL(connected()), this, SLOT(connected()));
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(tcpSocket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    setWindowTitle("客户端");

    ui->pushButton_Disconnect->setEnabled(false);
    ui->pushButton_Ready->setEnabled(false);

}

Window_TCPClient::~Window_TCPClient()
{
    tcpSocket->disconnectFromHost();
    tcpSocket->close();
    delete ui;
}

void Window_TCPClient::on_pushButton_Connect_clicked()
{
    //获取服务器IP和端口
    ip = ui->lineEdit_IP->text();
    port = ui->lineEdit_Port->text();
    qint16 _port = port.toInt();

    ui->pushButton_Disconnect->setEnabled(true);
    ui->pushButton_Connect->setEnabled(false);

    //主动和服务器建立连接
    tcpSocket->connectToHost(QHostAddress(ip),_port);
}       //TCPClient界面中Connect按钮


void Window_TCPClient::on_pushButton_Back_clicked()
{
    this->close();
}       //TCPClient界面中Back按钮

void Window_TCPClient::on_pushButton_Disconnect_clicked()
{
    if(tcpSocket == nullptr)return;
    //主动和对方断开连接
    tcpSocket->disconnectFromHost();
    tcpSocket->close();

    ui->pushButton_Connect->setEnabled(true);
    ui->pushButton_Disconnect->setEnabled(false);
    ui->pushButton_Ready->setEnabled(false);

}       //TCPClient界面中Disconnect按钮


void Window_TCPClient::connected()
{
    QString msg;
    msg.append("<b>Message: </b>Successfully connect to ");
    msg = msg + ip + " : " + port + "\n";
    ui->textEdit_Read->append(msg);
    ui->pushButton_Ready->setEnabled(true);

}       //SLOT"connected" connect with SIGNAL"connected"


void Window_TCPClient::disconnected()
{
    QString msg;
    msg.append("<b>Message: </b>Successfully disconnect from ");
    msg = msg + ip + " : " + port + "\n";
    ui->textEdit_Read->append(msg);
    tcpSocket->disconnectFromHost();
    tcpSocket->close();
    ui->pushButton_Connect->setEnabled(true);
    ui->pushButton_Disconnect->setEnabled(false);
    ui->pushButton_Ready->setEnabled(false);


}       //SLOT"disconnected" connect with SIGNAL"disconnected"

void Window_TCPClient::readyRead()
{
    QByteArray buf = tcpSocket->readAll();
    QString msg = QString(buf);
    ui->textEdit_Read->append(msg);
    if(msg.left(3) == "01#")
    {
        Window_Play* game = new Window_Play(gameplatform, gameplatform->getType());
        connect(game, SIGNAL(sendMouseData(QString,QString)), this, SLOT(receiveMouseData(QString,QString)), Qt::DirectConnection);
        connect(this, SIGNAL(sendNetData(int,int)), game, SLOT(receiveNetData(int,int)), Qt::DirectConnection);
        game->setAttribute(Qt::WA_DeleteOnClose); //关闭时自动删除
        game->setWindowFlags(game->windowFlags() | Qt::WindowStaysOnTopHint);
        game->setWindowModality(Qt::ApplicationModal);
        game->show();
        return;

    }       //接收服务器传来的开始游戏指令

    else if(msg.left(3) == "02#")
    {
        std::vector<int> pos;
        for(int i = 0; i < msg.size(); i++)
        {
            if(msg[i] == '#')
                pos.push_back(i);
        }
        int _x = msg.mid(pos[0] + 1, pos[1] - pos[0] - 1).toInt();
        int _y = msg.mid(pos[1] + 1, pos[2] - pos[1] - 1).toInt();
        emit sendNetData(_x, _y);
    }       //接受服务器传来的游戏内容


}       //SLOT"readyRead" connect with SIGNAL"readyRead"


void Window_TCPClient::on_pushButton_Ready_clicked()
{
    if(readyFlag == 0)
    {
        readyFlag = 1;
        QString msg;
        msg.append("<b>You are ready!</b>\n");
        ui->textEdit_Read->append(msg);
        ui->pushButton_Ready->setText("Cancel");
        QString tmp;                //用来向服务器传送数据
        tmp = "00#" + gameType;     //00#为传输内容是游戏类型的标识
        tcpSocket->write(tmp.toUtf8().data());
    }
    else
    {
        readyFlag = 0;
        QString msg;
        msg.append("<b>You are not ready!</b>\n");
        ui->textEdit_Read->append(msg);
        ui->pushButton_Ready->setText("Ready");
        QString tmp;
        tmp = "0F#";                //0F#表示未准备好
        tcpSocket->write(tmp.toUtf8().data());
    }
}       //TcpClient界面中Ready按钮



void Window_TCPClient::receiveMouseData(QString x, QString y)
{
    QString temp;                //用来向服务器传送数据
    temp = "03#" + x +"#" + y + "#";    //03#为客户端向服务器传输游戏内容
    tcpSocket->write(temp.toUtf8().data());
}
