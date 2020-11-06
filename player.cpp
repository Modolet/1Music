#include "player.h"

Player::Player(QObject *parent, QMediaPlayer::Flags flags)
    :QMediaPlayer(parent,flags)
{
    playList = new QMediaPlaylist;
    urlList = new QStringList;

    connect(this->playList,&QMediaPlaylist::currentIndexChanged,[=](int p){
        emit currentSongChanged(list->Songs.at(p));
    });
}

Player::Player(const Player &t)
{
    this->list = new ListModel(*t.list);
    this->playList = new QMediaPlaylist(t.playList);
}

Player &Player::operator=(const Player &t)
{
    this->list = t.list;
    this->playList = t.playList;
    return *this;
}

Player::~Player()
{
    if(list)
        delete list;
    delete playList;
}

void Player::loadSong(SongModel song)
{
    int index = urlList->indexOf(song.Url);
    if(index == -1)
    {
        playList->load(QUrl::fromLocalFile(song.Url));
        list->insertSong(song);
    }
    else
        playList->setCurrentIndex(index);
    this->play();
}

void Player::setList(ListModel* l)
{
    urlList->clear();
    delete list;
    list = l;
    for(auto song:list->Songs)
    {
        urlList->append(song.Url);
        playList->addMedia(QUrl::fromLocalFile(song.Url));
    }
    this->setPlaylist(playList);
}
