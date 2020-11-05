#include "player.h"

Player::Player(QObject *parent)
    :QObject(parent)
{
    this->player = new QMediaPlayer(this);
    //监测文件读取状态
    connect(this->player,&QMediaPlayer::mediaStatusChanged,[=](QMediaPlayer::MediaStatus status)
    {
        if(status == QMediaPlayer::LoadedMedia)
            this->isLoadFinish = true;
        else
            this->isLoadFinish = false;
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

QVariant Player::GetMetaData(const QString &key)
{
    //需要等待加载完毕才能获取
    while(isLoadFinish);
    qDebug() << player->isMetaDataAvailable();
    return player->metaData(key);
}
