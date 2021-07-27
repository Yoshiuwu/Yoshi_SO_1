#ifndef BATCHSEPARATOR_H
#define BATCHSEPARATOR_H

#include <QWidget>

namespace Ui {
class batchSeparator;
}

class batchSeparator : public QWidget
{
    Q_OBJECT

public:
    explicit batchSeparator(QWidget *parent = nullptr);
    ~batchSeparator();

private:
    Ui::batchSeparator *ui;
};

#endif // BATCHSEPARATOR_H
