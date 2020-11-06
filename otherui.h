#ifndef OTHERUI_H
#define OTHERUI_H

#include <QTableWidgetItem>
#include <QPushButton>
#include <QDebug>

#include "models.h"

class SongQTableWidgetItem : public QTableWidgetItem
{
public:
    SongQTableWidgetItem(SongModel song,const QString &text,int type=Type);
    SongModel song;
};

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

#endif // OTHERUI_H
