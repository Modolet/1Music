#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QVector>
#include <QDebug>

#include "models.h"
#include "library.h"
#include "dialoglocalfile.h"

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
    void initUI();
    void Connect();

public slots:
    void on_listWidget_MusicSource_itemChanged(QListWidgetItem* item);
};
#endif // MAINWINDOW_H
