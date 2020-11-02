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
    //设置底部部分
    //设置下方左侧三个按钮的大小
    ui->pushButton_NextSong->setFixedSize(40,40);
    ui->pushButton_PauseSong->setFixedSize(45,45);
    ui->pushButton_PreviousSong->setFixedSize(40,40);
    //设置按钮左右的间隙
    ui->frame_0->setFixedWidth(15);
    ui->frame_3->setFixedWidth(15);
    //设置按钮之间的间隙
    ui->frame_1->setFixedWidth(12);
    ui->frame_2->setFixedWidth(12);
    //设置底部widget高度
    ui->widget_Bottom->setFixedHeight(50);

    //设置歌曲信息部分
    //封面大小
    ui->pushButton_SongImage->setFixedSize(60,60);
    //收藏及喜欢按钮的大小
    ui->pushButton_Love->setFixedSize(28,28);
    ui->pushButton_Favorite->setFixedSize(28,28);

    //widget高度
    ui->widget_Song->setFixedHeight(65);

    //设置左边部分
    ui->widget_Left->setFixedWidth(200);

    //设置右边部分
    //封面大小
    ui->label_ListImage->setFixedSize(220,220);
}

