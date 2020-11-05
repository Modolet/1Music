#include "player.h"

Player::Player(QObject *parent)
    :QObject(parent)
{
    this->player = new QMediaPlayer(this);
    //转发信号
    connect(this->player,&QMediaPlayer::stateChanged,[=](QMediaPlayer::State m)
    {
        emit stateChanged(m);
    });
    connect(this->player,&QMediaPlayer::positionChanged,[=](qint64 p)
    {
        emit positionChanged(p);
    });
}

Player::Player(const Player &t)
{
    this->list = new ListModel(*t.list);
}

Player &Player::operator=(const Player &t)
{
    this->list = t.list;
    return *this;
}

Player::~Player()
{
    delete player;
    if(list)
        delete list;
}

void Player::loadSong(QString url, bool isVideo)
{
    this->player->setMedia(QUrl::fromLocalFile(url));
    if(!isVideo)
        this->play();
    else
    {

    }
}

void Player::play()
{
    player->play();
}

void Player::setList(ListModel* list)
{
    this->list = list;
}

void Player::setPosition(qint64 p)
{
    this->player->setPosition(p);
}
