#ifndef DIALOGLOCALFILE_H
#define DIALOGLOCALFILE_H

#include <QDialog>

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
};

#endif // DIALOGLOCALFILE_H
