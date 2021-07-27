#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>
#include <iostream>
#include <QRegExp>
#include <QMessageBox>
#include "proc.h"
#include "batchseparator.h"
#include "finishedproc.h"
#include "unfinishedproc.h"
#include <QKeyEvent>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_noProcLE_textChanged(const QString &arg1);

    void on_prograNameLE_textChanged(const QString &arg1);

    void on_num1LE_textChanged(const QString &arg1);

    void on_num2LE_textChanged(const QString &arg1);

    void on_estimatedTimeLE_textChanged(const QString &arg1);

    void on_idLE_textChanged(const QString &arg1);

    void on_noProcePB_clicked();

    void on_setProcPB_clicked();

    void on_startPB_clicked();

protected:

    void keyPressEvent( QKeyEvent *event);

private:
    Ui::MainWindow *ui;

    int contProc;
    int contBatch = 0;
    int contGlob = 0;
    bool ok = false;
    QList<Proc> procList;

    void setProce();
    void enableSetProcPB();
    bool srchID(const int &id);
    bool valProc();
    void startProc();
    void delay(const int &seg);
    int resolProc(const int &num1, const int &num2, const char op);


};
#endif // MAINWINDOW_H
