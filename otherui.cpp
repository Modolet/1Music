#include "otherui.h"

SongQTableWidgetItem::SongQTableWidgetItem(SongModel song,const QString &text,int type)
    :QTableWidgetItem(text,type), song(song)
{
}

QPushButtonPause::QPushButtonPause(QWidget *parrent)
    :QPushButton(parrent)
{

}
