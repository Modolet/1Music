#ifndef OTHERUI_H
#define OTHERUI_H

#include <QTableWidgetItem>
#include <QPushButton>
#include <QDebug>
#include <QMediaPlaylist>
#include <QEvent>
#include <QLabel>
#include <QBitmap>
#include <QPainter>
#include <QTimer>

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

//圆形旋转的Label
class ImageLabel : public QLabel
{
    Q_OBJECT
public:
    ImageLabel(const QString &text,bool round = true, QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags())
        :QLabel(text,parent,f),round(round),m_TimerId(0),m_rotateAngle(0){};
    ImageLabel(bool round = true,QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags())
        :QLabel(parent,f),round(round),m_TimerId(0),m_rotateAngle(0){};
    void setPixmap(const QPixmap &);

protected:
    void timerEvent(QTimerEvent* event);

private:
    bool round;
    //记录定时器id.
    int m_TimerId;
    //保存label显示的图片.
    QPixmap m_pixmap;
    //保存图片尺寸
    QSize m_size;
    //记录旋转角度.
    qreal m_rotateAngle;
    //裁剪图片
    QPixmap PixmapToRound(const QPixmap &src,int radius);

public slots:
    void slot_pauseTimer();
    void slot_continueTimer();
};

//自动裁剪文字的PushButton
class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    MyPushButton(const QIcon &icon, const QString &text, QWidget *parent = nullptr)
        :QPushButton(icon,text,parent){};
    MyPushButton(const QString &text, QWidget *parent = nullptr)
        :QPushButton(text,parent){};
    MyPushButton(QWidget *parent = nullptr)
        :QPushButton(parent){};
    void setText(const QString &text,int len = 30);
};

#endif // OTHERUI_H
