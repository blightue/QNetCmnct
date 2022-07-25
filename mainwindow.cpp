#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "tcpclientwidget.h"

#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), defaultPort(12340),
      clientCount(0) {
  ui->setupUi(this);

  m_TabWidget = new QTabWidget(this);

  TCPServerWidget *serverWidget = new TCPServerWidget(defaultPort++);

  m_TabWidget->addTab(serverWidget, "Server " + QString::number(clientCount++));

  this->setCentralWidget(m_TabWidget);
  this->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionClient_triggered()
{
    TCPClientWidget * clientWidget = new TCPClientWidget();

    m_TabWidget->addTab(clientWidget, "Client" + QString::number(clientCount ++));

    m_TabWidget->setCurrentWidget(clientWidget);
}


void MainWindow::on_actionServer_triggered()
{
    TCPServerWidget * serverWidget = new TCPServerWidget(defaultPort ++);

    m_TabWidget->addTab(serverWidget, "Server " + QString::number(clientCount ++));

    m_TabWidget->setCurrentWidget(serverWidget);
}

