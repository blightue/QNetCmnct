#include "tcpclientwindow.h"
#include "ui_tcpclientwindow.h"

TCPClientWindow::TCPClientWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TCPClientWindow)
{
    ui->setupUi(this);

    ui->portInput->setText("17890");

    m_Server = new QTcpServer(this);

    connect(m_Server, &QTcpServer::newConnection, this, [=]() {
      m_Socket = m_Server->nextPendingConnection();
      ui->statusLable->setText("Status: Connected");

      connect(m_Socket, &QTcpSocket::readyRead, this, [=]() {
        QByteArray data = m_Socket->readAll();
        ui->historyMsg->append("From client: " + data);
      });

      connect(m_Socket, &QTcpSocket::disconnected, this, [=]() {
        m_Socket->close();
        m_Socket->deleteLater();
        ui->statusLable->setText("Status: Disconnected");
      });
    });
}

TCPClientWindow::~TCPClientWindow()
{
    delete ui;
}

void TCPClientWindow::on_setListenButton_clicked()
{
    unsigned short port = ui->portInput->text().toUShort();
    m_Server->listen(QHostAddress::Any,port);
    ui->setListenButton->setEnabled(false);
    ui->historyMsg->append("Start listen at port : " + ui->portInput->text());
}


void TCPClientWindow::on_sendButton_clicked()
{
    QString msg = ui->sendMsg->toPlainText();
    m_Socket->write(msg.toUtf8());
    ui->historyMsg->append("From server: " + msg);
}
