#include "library.h"

Library::Library(QObject *parent) : QObject(parent)
{

}

void Library::Register(SOURCE id)
{
    this->source = id;
}

ListModel *Library::GetList(QString ListName)
{
    if(ListName == "local")
        return localList;
}

void Library::GetLocalAudio(QStringList dirs)
{
    //设置过滤器
    Filters << "*.mp3" << "*.wav" << "*.ape" << "*.flac" << "*.aac" << "*.ogg";

    //创建本地歌单文件
    localList = new ListModel("./lists/locallist.json",true);
    for(QString dir : dirs)
        _FindFiles(dir);
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
