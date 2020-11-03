#include "models.h"

Models::Models(QObject *parent) : QObject(parent)
{

}

ListModel::ListModel(QString url, bool isLocalList)
{
    this->Url = url;
    this->IsLocalList = isLocalList;
}

void ListModel::setName(const QString &name)
{
    this->Name = name;
}

void ListModel::setCreateTime(const QDateTime &time)
{
    this->CreateTime = time;
}

void ListModel::insertSong(const SongModel &song)
{
    this->Songs.append(song);
}

void ListModel::deleteSong(const SongModel &song)
{
    this->Songs.removeOne(song);
}

void ListModel::setInfo(const QString &info)
{
    this->Info = info;
}

SongModel::SongModel(QString url,bool IsLocalSong)
{
    this->Url = url;
    this->IsLocalSong = IsLocalSong;
    if(IsLocalSong)
    {
        FileName = url.split("/").last();
        FileName = FileName.mid(0,FileName.lastIndexOf("."));
        Title = FileName.mid(0,FileName.lastIndexOf("."));
        qDebug() << FileName << Title;
    }
}

bool SongModel::operator==(const SongModel &obj)
{
    if(this->Url == obj.Url)
        return true;
    return false;
}
