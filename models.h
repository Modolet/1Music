#ifndef MODELS_H
#define MODELS_H

#include <QObject>
#include <QString>
#include <QDateTime>
#include <QVector>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QFile>
#include <QDebug>
#include <QMediaPlayer>

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

    SongModel(QString url,bool IsLocalSong = false);
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

    bool IsLocalList;//是否为本地歌单
    QString Url;//
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

};

#endif // MODELS_H
