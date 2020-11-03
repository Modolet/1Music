#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QString>
#include "models.h"

//播放器
class Player : public QObject
{
    Q_OBJECT
public:
    //无参构造
    explicit Player(QObject *parent = nullptr);
    //有参构造
    Player(QObject *parent = nullptr,ListModel *list = nullptr);
    //获取播放器信息
    //获取当前歌曲
    QString getCurrentSong();
    //获取歌单信息
    QString getCurrentList();
    //获取音量
    int getVolume();
    //设置音量
    int setVolume(int value);
    //播放
    void play(QString url,bool video = false);//url为网络链接或者本地文件，video为是否播放视频
    //暂停
    void pause();
    //停止
    void stop();
    //加载并播放指定歌曲
    void loadSong(SongModel song);



signals:

};

#endif // PLAYER_H
