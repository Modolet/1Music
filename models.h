#ifndef MODELS_H
#define MODELS_H

#include <QObject>
#include <QString>
#include <QDateTime>
#include <QVector>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QDebug>
#include <QMediaPlayer>
#include <QImage>
//taglib
#include <taglib/tag.h>
#include <taglib/fileref.h>
#include <taglib/mpegfile.h>
#include <taglib/id3v2frame.h>
#include <taglib/id3v2tag.h>
#include <taglib/attachedpictureframe.h>

//音乐资源模型
class Models : public QObject
{
    Q_OBJECT
    //歌曲模型
public:
    explicit Models(QObject *parent = nullptr);

signals:

};

class SongModel
{
public:
    bool IsLocalSong;//是否为本地文件
    int Id;//Id值。本地文件不需要id
    QString Source;//音源
    QString Url;//
    QString Title;//歌名
    QString Singer;//歌手
    QString Album;//专辑
    QString FileName;//文件名
    int minutes;//分钟数
    int seconds;//秒钟数
    int times;//总数

    SongModel(QString url,bool IsLocalSong = false,bool = false);
    ~SongModel();
    //获取封面
    QImage getID3v2Image();
    bool operator==(const SongModel &obj);
};

class ListModel
{
private:

    void _setName();
    void _setCreateTime();
    void _setInfo();
    void _updateFile();

public:
    ListModel(QString url,bool isLocalList);
    ~ListModel();


    QString Url;//URL
    QString Name;//歌单名
    QString Info;//歌单简介/信息
    QDateTime CreateTime;//创建时间
    QString Author;//创建者
    QVector<SongModel> Songs;//歌曲列表

    //设置值
    void setName(const QString &name);
    void setCreateTime(const QDateTime &time);
    //插入/删除歌曲
    void insertSong(const SongModel &song);
    void deleteSong(const SongModel &song);
    void setInfo(const QString &info);
    //保存歌单到本地
    void saveJson();
    //读取json
    void ReadJson();
    //查询本地文件是否存在
    bool isExist();
private:
    bool IsExist;
    bool IsLocalList;//是否为本地歌单

};

#endif // MODELS_H
