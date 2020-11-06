#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QString>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QStringList>
#include "models.h"

//播放器
class Player : public QMediaPlayer
{
    Q_OBJECT
public:
    QMediaPlaylist* playList;

    //有参构造
    Player(QObject *parent = nullptr, QMediaPlayer::Flags flags = Flags());
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
    //加载并播放指定歌曲
    void loadSong(SongModel song);
    //设置歌单模型
    void setList(ListModel *list);


private:
    //歌单模型
    ListModel* list;
    //Url列表
    QStringList* urlList;

signals:
    void currentSongChanged(SongModel song);

};

#endif // PLAYER_H
