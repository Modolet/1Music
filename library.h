#ifndef LIBRARY_H
#define LIBRARY_H

#include <QObject>
#include <QVector>
#include <QDir>
#include "models.h"

enum SOURCE {local,netease,qq,kugou,xiami};

//音乐库
class Library : public QObject
{
    Q_OBJECT
public:
    explicit Library(QObject *parent = nullptr);
    //注册平台
    void Register(SOURCE);
    //获取歌单列表
    QStringList* GetListNames();
    //获取歌单
    ListModel* GetList(QString ListName);
    //获取本地音乐
    void GetLocalAudio(QStringList dirs);
private:
    SOURCE source = local;
    QStringList Filters;

    ListModel* localList = nullptr;

    //搜索本地文件并加入到歌单
    void _FindFiles(QString startDir);

signals:
    void Signal_SearchFinish();
};

#endif // LIBRARY_H
