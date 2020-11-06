#ifndef OTHERUI_H
#define OTHERUI_H

#include <QTableWidgetItem>
#include <QPushButton>
#include <QDebug>
#include <QMediaPlaylist>
#include <QEvent>

#include "models.h"

//歌曲TableWidgetItem
class SongQTableWidgetItem : public QTableWidgetItem
{
public:
    SongQTableWidgetItem(SongModel song,const QString &text,int type=Type);
    SongModel song;
};

//播放暂停键
class QPushButtonPause : public QPushButton
{
    Q_OBJECT
public:
    QPushButtonPause(QWidget* parrent);
    QMediaPlayer::State state;
public slots:
    void slot_stateChanged(QMediaPlayer::State status);

signals:
    void stateChanged(QMediaPlayer::State);
};

//播放模式健
class QPushButtonPlaybackMode : public QPushButton
{
    Q_OBJECT
public:
    QPushButtonPlaybackMode(QWidget* parrent);
    QMediaPlaylist::PlaybackMode playbackMode;
public slots:
    void slot_playbackModeChanged(QMediaPlaylist::PlaybackMode);

signals:
    void playbackModeChanged(QMediaPlaylist::PlaybackMode);
};

//失去焦点就自动隐藏的滑动条
class MySlider : public QSlider
{
    Q_OBJECT
public:
    MySlider(Qt::Orientation orientation,QWidget* parent):QSlider(orientation,parent){};


};

#endif // OTHERUI_H
