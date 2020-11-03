#ifndef OTHERUI_H
#define OTHERUI_H

#include <QTableWidgetItem>
#include "models.h"

class SongQTableWidgetItem : public QTableWidgetItem
{
public:
    SongQTableWidgetItem(SongModel song,const QString &text,int type=Type);

    QString Source;//音源
    QString Url;//
    QString Title;//歌名
    QString Singer;//歌手
    QString Album;//专辑
    QString FileName;//文件名
};



#endif // OTHERUI_H
