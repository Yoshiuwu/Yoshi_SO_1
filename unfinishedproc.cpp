#include "unfinishedproc.h"
#include "ui_unfinishedproc.h"

unfinishedProc::unfinishedProc(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::unfinishedProc)
{
    ui->setupUi(this);
}

unfinishedProc::~unfinishedProc()
{
    delete ui;
}

void unfinishedProc::setFormat(const QString &name, const int &time)
{
    ui->nameLB->setText(name);
    ui->timeLB->setNum(time);
}
