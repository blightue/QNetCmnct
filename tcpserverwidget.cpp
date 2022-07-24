#include "tcpserverwidget.h"
#include "ui_tcpserverwidget.h"

TCPServerWidget::TCPServerWidget(int defaultPort, QWidget *parent):
    QWidget(parent),
    ui(new Ui::TCPServerWidget)
{
    ui->setupUi(this);

    ui->portInput->setText(QString::number(defaultPort));

    initWindow();
}

TCPServerWidget::TCPServerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TCPServerWidget)
{
    ui->setupUi(this);

    ui->portInput->setText("78900");

    initWindow();
}

void TCPServerWidget::initWindow()
{
    m_Server = new QTcpServer(this);

    ui->sendButton->setEnabled(false);
    ui->stopLisBtn->setEnabled(false);

    connect(
        m_Server, &QTcpServer::newConnection, this, [=]() {
            m_Socket = m_Server->nextPendingConnection();
            ui->statusLable->setText("Status: Connected");
            ui->historyMsg->append("Client connected");
            ui->sendButton->setEnabled(true);

            connect(m_Socket, &QTcpSocket::readyRead, this, [=]() {
                QByteArray data = m_Socket->readAll();
                ui->historyMsg->append("From client: " + data);
            });

            connect(m_Socket, &QTcpSocket::disconnected, this, [=]() {
                m_Socket->close();
                m_Socket->deleteLater();
                ui->statusLable->setText("Status: Disconnected");
                ui->historyMsg->append("Client disconnected");
                ui->sendButton->setEnabled(false);
            });
        });
}

TCPServerWidget::~TCPServerWidget()
{
    delete ui;
}

void TCPServerWidget::on_setListenButton_clicked()
{
    unsigned short port = ui->portInput->text().toUShort();
    m_Server->listen(QHostAddress::Any,port);
    ui->setListenButton->setEnabled(false);
    ui->stopLisBtn->setEnabled(true);
    ui->historyMsg->append("Start listen at port : " + ui->portInput->text());
}


void TCPServerWidget::on_sendButton_clicked()
{
    QString msg = ui->sendMsg->toPlainText();
    m_Socket->write(msg.toUtf8());
    ui->historyMsg->append("From server: " + msg);
    ui->sendMsg->clear();
}

void TCPServerWidget::on_stopLisBtn_clicked()
{
    m_Socket->close();
    m_Server->close();
    ui->historyMsg->append("Stop listen at port: "+ ui->portInput->text());
    ui->setListenButton->setEnabled(true);
    ui->stopLisBtn->setEnabled(false);
}

