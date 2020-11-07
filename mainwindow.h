#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QVector>
#include <QDebug>

#include "otherui.h"
#include "models.h"
#include "library.h"
#include "dialoglocalfile.h"
#include "player.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    //歌单列表
    QVector<ListModel>* lists;
    //本地音乐列表
    ListModel* localList;
    //音乐库
    Library* library;
    //播放器
    Player* player;
    //音乐滑动条是否被按下
    bool isSliderPress = true;
    //UI
    //音量调节条
    MySlider* Slider_Volume;
    void initUI();
    void Connect();
    //窗口大小改变时间
    void resizeEvent(QResizeEvent* size);

public slots:
    //音源改变时
    void on_listWidget_MusicSource_itemChanged(QListWidgetItem* item);
    //设置音量
    void setVolume();

protected:


};
#endif // MAINWINDOW_H
