#include "dialoglocalfile.h"
#include "ui_dialoglocalfile.h"

DialogLocalFile::DialogLocalFile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogLocalFile)
{
    ui->setupUi(this);
}

DialogLocalFile::~DialogLocalFile()
{
    delete ui;
}
