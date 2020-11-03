#ifndef DIALOGLOCALFILE_H
#define DIALOGLOCALFILE_H

#include <QDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <QString>
#include <QStringList>

#include "models.h"

namespace Ui {
class DialogLocalFile;
}

class DialogLocalFile : public QDialog
{
    Q_OBJECT

public:
    explicit DialogLocalFile(QWidget *parent = nullptr);
    ~DialogLocalFile();

private:
    Ui::DialogLocalFile *ui;
    QStringList Dirs;
    ListModel *List;

    void on_PushButton_addClicked();
    void on_PushButton_OK_Clicked();
};

#endif // DIALOGLOCALFILE_H