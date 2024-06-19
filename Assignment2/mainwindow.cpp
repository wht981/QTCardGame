#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "maingame.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_StartButton_clicked()
{
    MainGame *mainGameWindow = new MainGame();

    mainGameWindow->show();

    this->close();
}

