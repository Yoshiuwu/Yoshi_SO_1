#include "finishedproc.h"
#include "ui_finishedproc.h"

finishedProc::finishedProc(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::finishedProc)
{
    ui->setupUi(this);
}

finishedProc::~finishedProc()
{
    delete ui;
}

void finishedProc::setFormat(const int &id, const QString &oper, const int result)
{
    ui->idLB->setNum(id);
    ui->operatorLB->setText(oper);
    ui->resultLB->setNum(result);
}
