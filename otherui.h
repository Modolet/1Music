#ifndef OTHERUI_H
#define OTHERUI_H

#include <QTableWidgetItem>
#include <QPushButton>

#include "models.h"

class SongQTableWidgetItem : public QTableWidgetItem
{
public:
    SongQTableWidgetItem(SongModel song,const QString &text,int type=Type);
    SongModel song;
};

class QPushButtonPause : public QPushButton
{
public:
    QPushButtonPause(QWidget* parrent);
    bool pause;
};

#endif // OTHERUI_H
