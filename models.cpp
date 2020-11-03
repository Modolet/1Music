#include "models.h"

Models::Models(QObject *parent) : QObject(parent)
{

}

ListModel::ListModel(QString url, bool isLocalList)
{
    this->Url = url;
    this->IsLocalList = isLocalList;
}

void ListModel::setName(QString name)
{
    this->Name = name;
}

void ListModel::setCreateTime(QDateTime time)
{
    this->CreateTime = time;
}

void ListModel::insertSong(SongModel song)
{
    this->Songs.append(song);
}

void ListModel::deleteSong(SongModel song)
{
    this->Songs.removeOne(song);
}

void ListModel::setInfo(QString info)
{
    this->Info = info;
}
