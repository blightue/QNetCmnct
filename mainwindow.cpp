#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_TabWidget = new QTabWidget(this);

    TCPClientWindow * clientWindow = new TCPClientWindow();

    m_TabWidget->addTab(clientWindow, "Client");

    this->setCentralWidget(m_TabWidget);
    this->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
