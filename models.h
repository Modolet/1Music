#ifndef MODELS_H
#define MODELS_H

#include <QObject>

//音乐资源模型
class Models : public QObject
{
    Q_OBJECT
public:
    explicit Models(QObject *parent = nullptr);

signals:

};

#endif // MODELS_H
