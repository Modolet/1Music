#include "player.h"

Player::Player(QObject *parent)
    :QObject(parent)
{
    this->player = new QMediaPlayer(this);
    //监测文件读取状态
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
