#ifndef LIBRARY_H
#define LIBRARY_H

#include <QObject>

enum SOURCE {local,netease,qq,kugou,xiami};

//音乐库
class Library : public QObject
{
    Q_OBJECT
public:
    explicit Library(QObject *parent = nullptr);
    void Register(SOURCE);

private:
    SOURCE source = local;

signals:

};

#endif // LIBRARY_H
