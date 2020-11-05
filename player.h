#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QString>
#include <QMediaPlayer>
#include <QTimer>
#include <QEventLoop>
#include "models.h"

//播放器
class Player : public QObject
{
    Q_OBJECT
public:
    //有参构造
    Player(QObject *parent = nullptr);
    //拷贝构造
    Player(const Player &t);
    //赋值重载
    Player& operator=(const Player &t);
    //析构函数
    ~Player();
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
    void play();
    //暂停
    void pause();
    //停止
    void stop();
    //加载并播放指定歌曲
    void loadSong(QString song,bool isVideo = false);//url为网络链接或者本地文件，video为是否播放视频
    //设置歌单模型
    void setList(ListModel *list);
    //设置position
    void setPosition(qint64);


private:
    //歌单模型
    ListModel* list;
    //播放器
    QMediaPlayer* player;

signals:
    void stateChanged(QMediaPlayer::State);
    void positionChanged(qint64 position);



signals:

};

#endif // PLAYER_H
