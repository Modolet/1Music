#include "otherui.h"

SongQTableWidgetItem::SongQTableWidgetItem(SongModel song,const QString &text,int type)
    :QTableWidgetItem(text,type), song(song)
{
}

QPushButtonPause::QPushButtonPause(QWidget *parrent)
    :QPushButton(parrent)
{
    //设置默认模式
    this->state = QMediaPlayer::PausedState;
    this->setIcon(QIcon(":/icon/ICONS/暂停.svg"));
    //点击时改变模式并发送信号
    connect(this,&QPushButton::clicked,[=]()mutable{
        if(state == QMediaPlayer::PlayingState){
            state = QMediaPlayer::PausedState;
            this->setIcon(QIcon(":/icon/ICONS/暂停.svg"));
        }
        else{
            state = QMediaPlayer::PlayingState;
            this->setIcon(QIcon(":/icon/ICONS/开始.svg"));
        }
        emit stateChanged(state);
        return;
    });
}

void QPushButtonPause::slot_stateChanged(QMediaPlayer::State status)
{
    this->state = status;
    switch (status) {
    case QMediaPlayer::PlayingState:
        this->setIcon(QIcon(":/icon/ICONS/开始.svg"));
        break;
    case QMediaPlayer::PausedState:
        this->setIcon(QIcon(":/icon/ICONS/暂停.svg"));
        break;
    case QMediaPlayer::StoppedState:
        this->setIcon(QIcon(":/icon/ICONS/暂停.svg"));
        break;
    }
}

QPushButtonPlaybackMode::QPushButtonPlaybackMode(QWidget *parrent)
    :QPushButton(parrent)
{
    //设置默认模式
    this->playbackMode = QMediaPlaylist::PlaybackMode::Loop;
    this->setIcon(QIcon(":/icon/ICONS/列表循环.svg"));
    connect(this,&QPushButton::clicked,[=]()mutable{
        switch (playbackMode) {
        //顺序播放切列表循环
        case QMediaPlaylist::PlaybackMode::Sequential:
            this->playbackMode = QMediaPlaylist::PlaybackMode::Loop;
            this->setIcon(QIcon(":/icon/ICONS/列表循环.svg"));
            break;
        //列表循环切随机播放
        case QMediaPlaylist::PlaybackMode::Loop:
            this->playbackMode = QMediaPlaylist::PlaybackMode::Random;
            this->setIcon(QIcon(":/icon/ICONS/随机播放.svg"));
            break;
        //随机播放切单曲循环
        case QMediaPlaylist::PlaybackMode::Random:
            this->playbackMode = QMediaPlaylist::PlaybackMode::CurrentItemInLoop;
            this->setIcon(QIcon(":/icon/ICONS/单曲循环.svg"));
            break;
        //单曲循环切顺序播放
        case QMediaPlaylist::PlaybackMode::CurrentItemInLoop:
            this->playbackMode = QMediaPlaylist::PlaybackMode::Sequential;
            this->setIcon(QIcon(":/icon/ICONS/顺序播放.svg"));
            break;
        default:
            break;
        }
        //发送信号
        emit playbackModeChanged(this->playbackMode);
    });
}

void QPushButtonPlaybackMode::slot_playbackModeChanged(QMediaPlaylist::PlaybackMode)
{

}
