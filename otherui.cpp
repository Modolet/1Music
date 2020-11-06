#include "otherui.h"

SongQTableWidgetItem::SongQTableWidgetItem(SongModel song,const QString &text,int type)
    :QTableWidgetItem(text,type), song(song)
{
}

QPushButtonPause::QPushButtonPause(QWidget *parrent)
    :QPushButton(parrent)
{
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
