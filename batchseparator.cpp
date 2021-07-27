#include "batchseparator.h"
#include "ui_batchseparator.h"

batchSeparator::batchSeparator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::batchSeparator)
{
    ui->setupUi(this);
}

batchSeparator::~batchSeparator()
{
    delete ui;
}
