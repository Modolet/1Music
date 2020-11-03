#include "dialoglocalfile.h"
#include "ui_dialoglocalfile.h"

DialogLocalFile::DialogLocalFile(QWidget *parent,Library *library) :
    QDialog(parent),
    ui(new Ui::DialogLocalFile)
{
    this->library = library;
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
    if(Dirs.isEmpty())return;
    library->GetLocalAudio(Dirs);
}
