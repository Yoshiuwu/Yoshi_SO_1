#ifndef FINISHEDPROC_H
#define FINISHEDPROC_H

#include <QWidget>

namespace Ui {
class finishedProc;
}

class finishedProc : public QWidget
{
    Q_OBJECT

public:
    explicit finishedProc(QWidget *parent = nullptr);
    ~finishedProc();

    void setFormat(const int &id, const QString &oper, const int result);

private:
    Ui::finishedProc *ui;
};

#endif // FINISHEDPROC_H
