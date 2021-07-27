#ifndef UNFINISHEDPROC_H
#define UNFINISHEDPROC_H

#include <QWidget>

namespace Ui {
class unfinishedProc;
}

class unfinishedProc : public QWidget
{
    Q_OBJECT

public:
    explicit unfinishedProc(QWidget *parent = nullptr);
    ~unfinishedProc();

    void setFormat(const QString &name, const int &time);

private:
    Ui::unfinishedProc *ui;
};

#endif // UNFINISHEDPROC_H
