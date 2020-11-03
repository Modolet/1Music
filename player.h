#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>

//播放器
class Player : public QObject
{
    Q_OBJECT
public:
    explicit Player(QObject *parent = nullptr);

signals:

};

#endif // PLAYER_H
