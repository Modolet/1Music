#include "library.h"

Library::Library(QObject *parent) : QObject(parent)
{

}

Library::~Library()
{
    if(localList)
        delete localList;
}

void Library::Register(SOURCE id)
{
    this->source = id;
}

ListModel *Library::GetList(QString ListName)
{
    if(ListName == "local")
        return new ListModel("./lists/locallist.json",true);
    return nullptr;
}

void Library::GetLocalAudio(QStringList dirs)
{
    //设置过滤器
    Filters << "*.mp3" << "*.wav" << "*.ape" << "*.flac" << "*.aac" << "*.ogg";
    //因为mainwindow的library可以看作是全局变量，所以每次获取本地音乐的时候要检测localList是不是空指针，防止内存泄漏
    //创建本地歌单文件
    if(localList != nullptr)
        delete localList;
    localList = new ListModel("./lists/locallist.json",true);
    for(QString dir : dirs)
        _FindFiles(dir);
    //搜索完成时，保存文件并发送信号
    localList->saveJson();
    emit Signal_SearchFinish();
}

void Library::_FindFiles(QString startDir)
{
    //递归查找歌曲
    QDir dir(startDir);
    for(QString subdir : dir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot))
        _FindFiles(startDir + "/" + subdir);
    //查找本文件夹的歌曲
    for(QString file : dir.entryList(Filters,QDir::Files))
    {
        //实例化歌曲，并插入到歌单
        SongModel song(startDir + "/" + file,true);
        localList->insertSong(song);
    }
}
