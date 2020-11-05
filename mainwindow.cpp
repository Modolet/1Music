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
    ui->pushButton_SongImage->setIconSize(QSize(60,60));
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

    //设置ListWidget的高度为行数*每行高度
    ui->listWidget_Mine->setFixedHeight(ui->listWidget_Mine->sizeHintForRow(0) * ui->listWidget_Mine->count());
    ui->listWidget_MusicSource->setFixedHeight(ui->listWidget_MusicSource->sizeHintForRow(0) * ui->listWidget_MusicSource->count());
}

void MainWindow::Connect()
{
    //点击本地音乐
    connect(ui->listWidget_MusicSource,&QListWidget::itemClicked,this,&MainWindow::on_listWidget_MusicSource_itemChanged);
    //点击本地音乐列表
    connect(ui->tableWidget_LocalList,&QTableWidget::itemDoubleClicked,[=](QTableWidgetItem* item)
    {
        //播放音乐
        player->loadSong(((SongQTableWidgetItem*)item)->song.Url);
        //获取音乐属性并设置ui
        ui->label_Singer->setText(((SongQTableWidgetItem*)item)->song.Singer);
        ui->label_SongName->setText(((SongQTableWidgetItem*)item)->song.Title);
        ui->pushButton_SongImage->setIcon(QIcon(QPixmap::fromImage(((SongQTableWidgetItem*)item)->song.getID3v2Image())));
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
        ui->tableWidget_LocalList->setColumnCount(1);
        //设置列宽
        ui->tableWidget_LocalList->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        //隐藏表头
        ui->tableWidget_LocalList->horizontalHeader()->hide();
        //设置为不可编辑
        ui->tableWidget_LocalList->setEditTriggers(QAbstractItemView::NoEditTriggers);
        for(SongModel song:localList->Songs)
        {
            ui->tableWidget_LocalList->setItem(i,0,static_cast<QTableWidgetItem*>(new SongQTableWidgetItem(song,song.Title)));
            i++;
        }
        //设置播放器歌单
        player->setList(localList);

    }
}

