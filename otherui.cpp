#include "otherui.h"

SongQTableWidgetItem::SongQTableWidgetItem(SongModel song,const QString &text,int type)
    :QTableWidgetItem(text,type), song(song)
{
}

QPushButtonPause::QPushButtonPause(QWidget *parrent)
    :QPushButton(parrent)
{

}

void QPushButtonPause::slot_stateChanged(QMediaPlayer::State status)
{
    switch (status) {
    case QMediaPlayer::PlayingState:
        qDebug() << "播放";
        break;
    case QMediaPlayer::PausedState:
        qDebug() << "暂停";
        break;
    case QMediaPlayer::StoppedState:
        qDebug() << "停止";
        break;
    }
}
