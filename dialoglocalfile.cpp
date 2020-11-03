#include "dialoglocalfile.h"
#include "ui_dialoglocalfile.h"

DialogLocalFile::DialogLocalFile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogLocalFile)
{
    List = new ListModel(QString("./lists/locallist.json"),true);

    ui->setupUi(this);
    this->setWindowTitle("添加本地文件夹");

    connect(ui->pushButton_Add,&QPushButton::clicked,this,&DialogLocalFile::on_PushButton_addClicked);
    connect(ui->pushButton_OK,&QPushButton::clicked,this,&DialogLocalFile::on_PushButton_OK_Clicked);
}

DialogLocalFile::~DialogLocalFile()
{
    delete ui;
    delete List;
}

void DialogLocalFile::_FindFiles(QString startDir)
{
    //递归查找歌曲
    QDir dir(startDir);
    for(QString subdir : dir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot))
        _FindFiles(startDir + "/" + subdir);
    //查找本文件夹的歌曲
    for(QString file : dir.entryList(Filters,QDir::Files))
    {
        SongModel song(startDir + "/" + file,true);

    }
}

void DialogLocalFile::on_PushButton_addClicked()
{
    QString Dir = QFileDialog::getExistingDirectory(this,"请选择音乐文件夹","/");
    //判断用户是否选择了一个文件夹
    if(Dir == "")return;
    this->Dirs.append(Dir);
    ui->listWidget->addItem(new QListWidgetItem(Dir));
}

void DialogLocalFile::on_PushButton_OK_Clicked()
{
    //设置过滤器
    Filters << "*.mp3" << "*.wav" << "*.ape" << "*.flac" << "*.aac" << "*.ogg";
    if(Dirs.isEmpty())return;

    for(QString n : Dirs)
    {
        this->_FindFiles(n);
    }
}
