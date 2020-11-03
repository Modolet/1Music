#include "otherui.h"


SongQTableWidgetItem::SongQTableWidgetItem(SongModel song,const QString &text,int type)
    :QTableWidgetItem(text,type)
{
    this->Album = song.Album;
    this->FileName = song.FileName;
    this->Singer = song.Singer;
    this->Source = song.Source;
    this->Title = song.Title;
    this->Url = song.Url;
}
