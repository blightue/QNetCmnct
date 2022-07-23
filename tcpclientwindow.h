#ifndef TCPCLIENTWINDOW_H
#define TCPCLIENTWINDOW_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>

namespace Ui {
class TCPClientWindow;
}

class TCPClientWindow : public QWidget
{
    Q_OBJECT

public:
    explicit TCPClientWindow(QWidget *parent = nullptr);
    ~TCPClientWindow();

private slots:
    void on_setListenButton_clicked();

    void on_sendButton_clicked();

private:
    Ui::TCPClientWindow *ui;
    QTcpServer * m_Server;
    QTcpSocket * m_Socket;
};

#endif // TCPCLIENTWINDOW_H
