#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->topViewWidget->setViewTop();
    ui->sideViewWidget->setViewSide();
    ui->frontViewWidget->setViewFront();
}

MainWindow::~MainWindow()
{
    delete ui;
}
