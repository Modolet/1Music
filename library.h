#ifndef LIBRARY_H
#define LIBRARY_H

#include <QObject>

//音乐库
class Library : public QObject
{
    Q_OBJECT
public:
    explicit Library(QObject *parent = nullptr);

signals:

};

#endif // LIBRARY_H
