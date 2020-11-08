#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //构造变量
    library = new Library;
    player = new Player;
    ui->setupUi(this);
    this->initUI();
    this->Connect();
    //设置音源
    ui->listWidget_MusicSource->setCurrentRow(4);
//    this->on_listWidget_MusicSource_itemChanged(ui->listWidget_MusicSource->currentItem());
}

MainWindow::~MainWindow()
{
    delete ui;
    delete player;
    delete Slider_Volume;
}

void MainWindow::initUI()
{
    //构造UI
    Slider_Volume = new MySlider(Qt::Vertical,this);

    //默认的堆叠窗口
    ui->stackedWidget_list->setCurrentWidget(ui->page_start);
    ui->stackedWidget_center->setCurrentWidget(ui->page_main);
    //默认隐藏
    Slider_Volume->hide();
    //初始化音量滑动条
    Slider_Volume->setMaximum(100);
    Slider_Volume->setMinimum(0);
    Slider_Volume->setValue(100);
    //设置音量条大小
    Slider_Volume->resize(20,100);
    //调整详情页图片的尺寸
    ui->label_SongLeftImage->setFixedSize(this->size().height()/5*2,this->size().height()/5*2);
    //设置详情页左侧间隔的高度
    ui->frame_SongLeft->setFixedHeight(20);
    //设置详情页左侧封面和顶部之间间隔的高度
    ui->frame_SongLeftUp->setFixedHeight(30);


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

    //LocalList设置
    //设置列数
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


}

void MainWindow::Connect()
{
    //按下滑动条
    connect(ui->horizontalSlider_Song,&QSlider::sliderPressed,[=]()mutable{
        isSliderPress = true;
    });
    //点击本地音乐
    connect(ui->listWidget_MusicSource,&QListWidget::itemClicked,this,&MainWindow::on_listWidget_MusicSource_itemChanged);
    //点击音量键
    connect(ui->pushButton_Volume,&QPushButton::clicked,this,&MainWindow::setVolume);
    //点击封面键
    connect(ui->pushButton_SongImage,&QPushButton::clicked,[=](){
        ui->stackedWidget_center->setCurrentIndex(1);
    });
    //关闭详情页
    connect(ui->pushButton_SongRightClose,&QPushButton::clicked,[=](){
        ui->stackedWidget_center->setCurrentIndex(0);
    });
    //点击表格项
    connect(ui->tableWidget_LocalList,&QTableWidget::cellDoubleClicked,[=](int row, int column)
    {
        QString temp;
        switch (column) {
        case 1:
            player->loadSong(((SongQTableWidgetItem*)ui->tableWidget_LocalList->item(row,column))->song.Url);
            break;
        case 3:
            temp = ((SongQTableWidgetItem*)ui->tableWidget_LocalList->item(row,column))->song.Singer;
            for(int i = 0;i < ui->tableWidget_LocalList->rowCount();i++)
            {
                if(((SongQTableWidgetItem*)ui->tableWidget_LocalList->item(i,column))->song.Singer == temp)
                    ui->tableWidget_LocalList->showRow(i);
                else
                    ui->tableWidget_LocalList->hideRow(i);
            }
            break;
        case 4:
            temp = ((SongQTableWidgetItem*)ui->tableWidget_LocalList->item(row,column))->song.Album;
            for(int i = 0;i < ui->tableWidget_LocalList->rowCount();i++)
            {
                if(((SongQTableWidgetItem*)ui->tableWidget_LocalList->item(i,column))->song.Album == temp)
                    ui->tableWidget_LocalList->showRow(i);
                else
                    ui->tableWidget_LocalList->hideRow(i);
            }
            break;
        }
        //滑动条没有被按下
        isSliderPress = false;
    });
    //当前歌曲变更时，要设置对应的ui
    connect(player,&Player::currentSongChanged,[=](SongModel song){
        //获取音乐属性并设置ui
        //设置左下角WidgetUI
        ui->label_Singer->setText(song.Singer);//设置歌手
        ui->label_SongName->setText(song.Title);//设置标题
        ui->pushButton_SongImage->setIcon(QIcon(QPixmap::fromImage(song.getID3v2Image())));//设置封面图片
        ui->label_FinishTime->setText(QString("%1:%2").
                                      arg(song.minutes).
                                      arg(song.seconds,2,10,QLatin1Char('0')));//设置歌曲时长标签

        //设置歌曲详情页UI
        ui->label_SongRightTitle->setText(song.Title);//设置标题
        ui->pushButton_SongRightSinger->setText(song.Singer);//设置歌手
        ui->pushButton_SongRightAlbum->setText(song.Album);//设置专辑
        ui->pushButton_SongRightSource->setText(song.Source);//设置来源
        ui->label_SongLeftImage->setPixmap(QPixmap::fromImage(song.getID3v2Image()));//设置封面图片

        //设置滑动条
        ui->horizontalSlider_Song->setMaximum(song.times);//设置滑动条最大值
        ui->horizontalSlider_Song->setValue(0);//设置滑动条当前值
    });
    //播放器状态改变时发送信号给暂停键
    connect(this->player,&Player::stateChanged,ui->pushButton_PauseSong,&QPushButtonPause::slot_stateChanged);
    //播放器状态改变时控制详情页封面的旋转
    connect(this->player,&Player::stateChanged,[=](QMediaPlayer::State newState){
        switch (newState) {
        case QMediaPlayer::State::PlayingState:
            ui->label_SongLeftImage->slot_continueTimer();
            break;
        default:
            ui->label_SongLeftImage->slot_pauseTimer();
            break;
        }

    });
    //播放模式改变时发送信号给模式健
    connect(this->player->playList,&QMediaPlaylist::playbackModeChanged,ui->pushButton_Mode,&QPushButtonPlaybackMode::slot_playbackModeChanged);
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
        if(player->playlist())
            player->playlist()->next();
    });
    //上一首
    connect(ui->pushButton_PreviousSong,&QPushButton::clicked,[=](){
        if(player->playlist())
            player->playlist()->previous();
    });
    //开始 暂停
    connect(ui->pushButton_PauseSong,&QPushButtonPause::stateChanged,[=](QMediaPlayer::State state){
        if(!player->currentMedia().isNull())
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
    //播放模式
    connect(ui->pushButton_Mode,&QPushButtonPlaybackMode::playbackModeChanged,[=](QMediaPlaylist::PlaybackMode playbackMode){
        if(player->playlist())
            this->player->playlist()->setPlaybackMode(playbackMode);
    });
    //本地音乐的搜索
    connect(ui->lineEdit_localSearch,&QLineEdit::textChanged,[=](QString text){
        //如果长度为0,则显示所有项
       if(text.length() == 0)
           for(int i = 0;i < ui->tableWidget_LocalList->rowCount();i++)
               ui->tableWidget_LocalList->showRow(i);
       QList<QTableWidgetItem*> itemList = ui->tableWidget_LocalList->findItems(text,Qt::MatchContains);
       //隐藏所有项
       for(int i = 0;i< ui->tableWidget_LocalList->rowCount();i++)
           ui->tableWidget_LocalList->hideRow(i);
       //如果搜索项不为空，则显示搜索项
       if(!itemList.isEmpty())
           for(int i = 0;i < itemList.count();i++)
               //排除第一列（音源）和第二列（时间）
               switch(itemList.at(i)->column())
               {
               case 0:
               case 2:
                   break;
               default:
                   ui->tableWidget_LocalList->showRow(itemList.at(i)->row());
                   break;
               }
    });
    //音量改变
    connect(this->Slider_Volume,&QSlider::valueChanged,this->player,&QMediaPlayer::setVolume);
}

//需要重新设置部分UI的位置
void MainWindow::resizeEvent(QResizeEvent *size)
{
    //调整详情页图片的尺寸
    ui->label_SongLeftImage->setFixedSize(this->size().height()/5*2,this->size().height()/5*2);
    //音量条位置
    Slider_Volume->move(ui->pushButton_Volume->geometry().x() + ui->pushButton_Volume->width()/2 - 10,
                        this->size().height() - 105 - ui->widget_Bottom->size().height()/2 - ui->pushButton_Volume->size().height()/2);
    return QMainWindow::resizeEvent(size);
}

void MainWindow::on_listWidget_MusicSource_itemChanged(QListWidgetItem *item)
{
    /*
     * 注意：切换不同的平台时，要记得回收旧平台的ListModel
     */

    //点击不同的按钮
    if(item->text() == "本地音乐")
    {
        //注册播放器
        library->Register(SOURCE::local);
        //获取歌单
        localList = library->GetList("local");
        //如果未获取歌单则重新获取歌单
        if(localList->Songs.size() == 0)
            localList = library->GetList("local");
        //切换页面
        ui->stackedWidget_list->setCurrentWidget(ui->page_local);
        //不存在就弹出对话框，扫描
        if(!localList->isExist())
        {
            DialogLocalFile w(nullptr,library);
            w.exec();
            localList = library->GetList("local");
        }
        //扫描完成，或者歌单存在
        //如果LocalList的行数为0
        if(!ui->tableWidget_LocalList->rowCount())
        {
            //添加进TableWidget
            int i = 0;
            //设置行数
            ui->tableWidget_LocalList->setRowCount(localList->Songs.size());
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
        }
        //设置播放器歌单
        player->setList(localList);
        //显示全部项
        for(int i = 0;i < ui->tableWidget_LocalList->rowCount();i++)
            ui->tableWidget_LocalList->showRow(i);

    }
}

void MainWindow::setVolume()
{
    //设置滑动条位置
    Slider_Volume->move(ui->pushButton_Volume->geometry().x() + ui->pushButton_Volume->width()/2 - 10,
                        this->size().height() - 105 - ui->widget_Bottom->size().height()/2 - ui->pushButton_Volume->size().height()/2);
    //控制显示隐藏
    if(Slider_Volume->isHidden())
        Slider_Volume->show();
    else
        Slider_Volume->hide();
}

