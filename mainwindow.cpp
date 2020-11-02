#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->initUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initUI()
{
    //设置下方左侧三个按钮的大小
    ui->pushButton_NextSong->setFixedSize(40,40);
    ui->pushButton_PauseSong->setFixedSize(45,45);
    ui->pushButton_PreviousSong->setFixedSize(40,40);
    ui->widget_bottom->setFixedHeight(50);
    //设置下方布局的高度
}

