#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    library = new Library;
    player = new Player;
    ui->setupUi(this);
    this->initUI();
    this->Connect();
    //设置音源
    ui->listWidget_MusicSource->setCurrentRow(4);
    this->on_listWidget_MusicSource_itemChanged(ui->listWidget_MusicSource->currentItem());
}

MainWindow::~MainWindow()
{
    delete ui;
    delete player;
}

void MainWindow::initUI()
{
    //设置窗口标题
    this->setWindowTitle("1Music");
    //设置底部部分
    //设置下方左侧三个按钮的大小
//    ui->pushButton_NextSong->setFixedSize(40,40);
//    ui->pushButton_PauseSong->setFixedSize(45,45);
//    ui->pushButton_PreviousSong->setFixedSize(40,40);
    //设置按钮左右的间隙
    ui->frame_0->setFixedWidth(15);
    ui->frame_3->setFixedWidth(15);
    //设置按钮之间的间隙
    ui->frame_1->setFixedWidth(12);
    ui->frame_2->setFixedWidth(12);
    //设置底部widget高度
//    ui->widget_Bottom->setFixedHeight(50);
    //设置进度滑动条最小值
    ui->horizontalSlider_Song->setMinimum(0);

    //设置歌曲信息部分
    //封面大小
    ui->pushButton_SongImage->setFixedSize(60,60);
    ui->pushButton_SongImage->setIconSize(QSize(60,60));
    //收藏及喜欢按钮的大小
    ui->pushButton_Love->setFixedSize(28,28);
    ui->pushButton_Star->setFixedSize(28,28);

    //widget高度
    ui->widget_Song->setFixedHeight(65);

    //设置左边部分
    ui->widget_Left->setFixedWidth(200);

    //设置右边部分
    //封面大小
    ui->label_ListImage->setFixedSize(220,220);

    //设置ListWidget的高度为行数*每行高度
    ui->listWidget_Mine->setFixedHeight(ui->listWidget_Mine->sizeHintForRow(0) * ui->listWidget_Mine->count());
    ui->listWidget_MusicSource->setFixedHeight(ui->listWidget_MusicSource->sizeHintForRow(0) * ui->listWidget_MusicSource->count());
}

void MainWindow::Connect()
{
    connect(ui->horizontalSlider_Song,&QSlider::sliderPressed,[=]()mutable{
        isSliderPress = true;
    });
    //点击本地音乐
    connect(ui->listWidget_MusicSource,&QListWidget::itemClicked,this,&MainWindow::on_listWidget_MusicSource_itemChanged);
    //点击本地音乐列表
    connect(ui->tableWidget_LocalList,&QTableWidget::itemDoubleClicked,[=](QTableWidgetItem* item)
    {
        //播放音乐
        player->loadSong(((SongQTableWidgetItem*)item)->song.Url);
        //滑动条没有被按下
        isSliderPress = false;
    });
    //当前歌曲变更时，要设置对应的ui
    connect(player,&Player::currentSongChanged,[=](SongModel song){
        //获取音乐属性并设置ui
        ui->label_Singer->setText(song.Singer);
        ui->label_SongName->setText(song.Title);
        ui->pushButton_SongImage->setIcon(QIcon(QPixmap::fromImage(song.getID3v2Image())));
        ui->label_FinishTime->setText(QString("%1:%2").
                                      arg(song.minutes).
                                      arg(song.seconds,2,10,QLatin1Char('0')));
        //设置滑动条最大值
        ui->horizontalSlider_Song->setMaximum(song.times);
        //设置滑动条当前值
        ui->horizontalSlider_Song->setValue(0);
    });
    //播放器状态改变时发送信号给暂停键
    connect(this->player,&Player::stateChanged,ui->pushButton_PauseSong,&QPushButtonPause::slot_stateChanged);
    //当前时间
    connect(this->player,&Player::positionChanged,[=](qint64 p){
        p /= 1000;
        int seconds = p % 60;
        int minutes = (p - seconds) / 60;
        //改变label的值
        ui->label_CurrentTime->setText(QString("%1:%2").arg(minutes).arg(seconds,2,10,QLatin1Char('0')));
        //改变滑动条的值
        if(!isSliderPress)
            ui->horizontalSlider_Song->setValue(p);
    });
    //通过滚动条修改进度
    connect(ui->horizontalSlider_Song,&QSlider::sliderReleased,[=]()mutable{
        player->setPosition(ui->horizontalSlider_Song->value() * 1000);
        isSliderPress = false;
    });
    //切换 暂停
    //下一首
    connect(ui->pushButton_NextSong,&QPushButton::clicked,[=](){
        player->playlist()->next();
    });
    //上一首
    connect(ui->pushButton_PreviousSong,&QPushButton::clicked,[=](){
        player->playlist()->previous();
    });
    //开始 暂停
    connect(ui->pushButton_PauseSong,&QPushButtonPause::stateChanged,[=](QMediaPlayer::State state){
        switch (state) {
        case QMediaPlayer::PausedState:
            player->pause();
            break;
        case QMediaPlayer::StoppedState:
            player->stop();
            break;
        case QMediaPlayer::PlayingState:
            player->play();
            break;
        }
    });
}

void MainWindow::on_listWidget_MusicSource_itemChanged(QListWidgetItem *item)
{
    /*
     * 注意：切换不同的平台时，要记得回收旧平台的ListModel
     */

    //点击不同的按钮
    if(item->text() == "本地音乐")
    {
        //获取歌单
        localList = library->GetList("local");
        //切换页面
        ui->stackedWidget_list->setCurrentWidget(ui->page_local);
        //不存在就弹出对话框，扫描
        library->Register(SOURCE::local);
        if(!library->GetList("local")->isExist())
        {
            DialogLocalFile w(nullptr,library);
            w.exec();
        }
        //扫描完成，或者歌单存在
        //获取歌单
        //添加进TableWidget
        int i = 0;
        //设置行数列数
        ui->tableWidget_LocalList->setRowCount(localList->Songs.size());
        ui->tableWidget_LocalList->setColumnCount(5);
        //设置列宽
        ui->tableWidget_LocalList->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->tableWidget_LocalList->horizontalHeader()->setSectionResizeMode(0,QHeaderView::ResizeToContents);
        ui->tableWidget_LocalList->horizontalHeader()->setSectionResizeMode(2,QHeaderView::ResizeToContents);
        //隐藏表头
        ui->tableWidget_LocalList->horizontalHeader()->hide();
        //隐藏列标
        ui->tableWidget_LocalList->verticalHeader()->hide();
        //隐藏分割线
        ui->tableWidget_LocalList->setShowGrid(false);
        //设置为不可编辑
        ui->tableWidget_LocalList->setEditTriggers(QAbstractItemView::NoEditTriggers);
        for(SongModel song:localList->Songs)
        {
            //音源
            QTableWidgetItem* sourceItem = static_cast<QTableWidgetItem*>(new SongQTableWidgetItem(song,song.Source));
            sourceItem->setFlags(Qt::ItemIsSelectable);
            ui->tableWidget_LocalList->setItem(i,0,sourceItem);
            //标题
            QTableWidgetItem* titleItem = static_cast<QTableWidgetItem*>(new SongQTableWidgetItem(song,song.Title));
            ui->tableWidget_LocalList->setItem(i,1,titleItem);
            //时长
            QTableWidgetItem* timeItem = new QTableWidgetItem(QString("%1:%2").arg(song.minutes).arg(song.seconds,2,10,QLatin1Char('0')));
            timeItem->setFlags(Qt::ItemIsSelectable);
            ui->tableWidget_LocalList->setItem(i,2,timeItem);
            //歌手
            QTableWidgetItem* singerItem = static_cast<QTableWidgetItem*>(new SongQTableWidgetItem(song,song.Singer));
            ui->tableWidget_LocalList->setItem(i,3,singerItem);
            //专辑
            QTableWidgetItem* AlbumItem = static_cast<QTableWidgetItem*>(new SongQTableWidgetItem(song,song.Album));
            ui->tableWidget_LocalList->setItem(i,4,AlbumItem);
            i++;
        }
        //设置播放器歌单
        player->setList(localList);

    }
}

