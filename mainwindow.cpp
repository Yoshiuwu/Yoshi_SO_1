#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Slots
void MainWindow::on_noProcLE_textChanged(const QString &arg1)
{
    if(arg1.toInt() > 0){
        ui->noProcePB->setEnabled(true);
    }
    else {
        ui->noProcePB->setEnabled(false);
    }
}

void MainWindow::on_prograNameLE_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    enableSetProcPB();
}

void MainWindow::on_num1LE_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    enableSetProcPB();
}

void MainWindow::on_num2LE_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    enableSetProcPB();
}

void MainWindow::on_estimatedTimeLE_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    enableSetProcPB();
}

void MainWindow::on_idLE_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    enableSetProcPB();
}

void MainWindow::on_noProcePB_clicked()
{
    contProc = ui->noProcLE->text().toInt();
    ui->noProcLE->setText("");
    ui->prograNameLE->setEnabled(true);
    ui->num1LE->setEnabled(true);
    ui->num2LE->setEnabled(true);
    ui->estimatedTimeLE->setEnabled(true);
    ui->idLE->setEnabled(true);
    ui->operatoCB->setEnabled(true);
    ui->noProcLE->setEnabled(false);
}

void MainWindow::enableSetProcPB()
{
    if(ui->prograNameLE->text().length() > 0 && ui->num1LE->text().length() > 0 && ui->num2LE->text().length() > 0 &&
            ui->estimatedTimeLE->text().length() > 0 && ui->idLE->text().length() > 0){
        ui->setProcPB->setEnabled(true);
    }
    else {
        ui->setProcPB->setEnabled(false);
    }
}

void MainWindow::on_setProcPB_clicked()

{
    if(valProc()){
        --contProc;
        setProce();
        if(contProc == 0){
            ui->stackedWidget->setCurrentIndex(1);
            contBatch = (procList.size() / 5);
            if(procList.size() % 5 != 0){
                ++contBatch;
            }
        }
    }
}

void MainWindow::on_startPB_clicked()

{
    startProc();
    ui->startPB->setEnabled(false);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
   QString s = "P";
   if(char(event->key()) == s)
       ok = true;
}

//Functions
void MainWindow::setProce()
{
    Proc p;

    p.setName(ui->prograNameLE->text());
    p.setNum1(ui->num1LE->text().toInt());
    p.setNum2(ui->num2LE->text().toInt());
    p.setOperator(ui->operatoCB->currentText().toStdString()[0]);
    p.setEstTime(ui->estimatedTimeLE->text().toInt());
    p.setId(ui->idLE->text().toInt());

    procList.push_back(p);

    ui->prograNameLE->setText("");
    ui->num1LE->setText("");
    ui->num2LE->setText("");
    ui->operatoCB->setCurrentText("+");
    ui->estimatedTimeLE->setText("");
    ui->idLE->setText("");
}

bool MainWindow::srchID(const int &id)
{
    for(int i(0); i < procList.size(); ++i){
        if(id == procList.at(i).getId()){
            return true;
        }
    }
    return false;
}

bool MainWindow::valProc()
{
    QRegExp name("([A-Za-z]|\\s)+");
    QRegExp number("\\d+");
    QMessageBox msg;

    if(name.exactMatch(ui->prograNameLE->text()) == false){
        msg.setText("Nombre inválido");
        msg.exec();
        return false;
    }
    else{
        if(number.exactMatch(ui->num1LE->text()) == false || number.exactMatch(ui->num2LE->text()) == false){
            msg.setText("Un dígito de la opereción no es correcto");
            msg.exec();
            return false;
        }
        else {
            if(((ui->operatoCB->currentText() == "/") || (ui->operatoCB->currentText() == "%")) && (ui->num2LE->text().toInt() == 0)){
                msg.setText("Operación inválida");
                msg.exec();
                return false;
            }
            else{
                if(ui->estimatedTimeLE->text().toInt() <= 0 || ui->estimatedTimeLE->text().toInt() >= 10)
                {
                    msg.setText("El tiempo mínimo ó máximo es inválido");
                    msg.exec();
                    return false;
                }
                else {
                    if(number.exactMatch(ui->idLE->text()) == false){
                        msg.setText("Número del programa inválido");
                        msg.exec();
                        return false;
                    }
                    else {
                        if(srchID(ui->idLE->text().toInt())){
                            msg.setText("Número de programa existente");
                            msg.exec();
                            return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}

void MainWindow::startProc()
{
    int batchcount = 0;
    bool first = false;
    ui->globalCountLB->setText("Contador: " + QString::number(contGlob));
    for(int i(0); i < procList.size(); ++i){
        if(batchcount == 0){
            int aux = 0;
            for(int j(i); j < procList.size(); ++j){
                unfinishedProc* pendProc = new unfinishedProc();
                pendProc->setFormat(procList.at(j).getName(), procList.at(j).getEstTime());
                ui->pendingProcGL->addWidget(pendProc);
                ++aux;
                if(aux == 5){
                    break;
                }
            }
            batchcount = 5;
            if(contBatch > 0){
                --contBatch;
            }
            ui->unfinishedBatchLB->setText("Lotes pendientes: " + QString::number(contBatch));
            if(first){
                batchSeparator* bs = new batchSeparator;
                ui->finishedProcGL->addWidget(bs);
            }
            else {
                first = true;
            }
        }
        delay(1);
        QLayoutItem* child;
        child = ui->pendingProcGL->takeAt(0);
        delete child->widget();
        --batchcount;

        ui->onNameLB->setText(procList.at(i).getName());
        ui->onOperatorLB->setText(QString::number(procList.at(i).getNum1()) + procList.at(i).getOperator() + QString::number(procList.at(i).getNum2()));
        ui->onEstimatedTimeLB->setNum(procList.at(i).getEstTime());
        ui->onPassTimeLB->setNum(0);
        ui->onRestTimeB->setNum(procList.at(i).getEstTime());

        for (int n(0); n < procList.at(i).getEstTime(); ++n) {
            delay(1);
            ui->onPassTimeLB->setNum(ui->onPassTimeLB->text().toInt() + 1);
            ui->onRestTimeB->setNum(ui->onRestTimeB->text().toInt() - 1);
            ++contGlob;
            ui->globalCountLB->setText("Contador: " + QString::number(contGlob));
        }
        procList[i].setResult(resolProc(procList.at(i).getNum1(), procList.at(i).getNum2(), procList.at(i).getOperator()));

        ui->onNameLB->setText("");
        ui->onOperatorLB->setText("");
        ui->onEstimatedTimeLB->setText("");
        ui->onPassTimeLB->setText("");
        ui->onRestTimeB->setText("");

        finishedProc* finproc = new finishedProc();
        finproc->setFormat(procList.at(i).getId(), QString::number(procList.at(i).getNum1()) + procList.at(i).getOperator() + QString::number(procList.at(i).getNum2()),
                           procList.at(i).getResult());
        ui->finishedProcGL->addWidget(finproc);
    }
}

void MainWindow::delay(const int &seg)
{
    QTime betweenTime = QTime::currentTime().addSecs(seg);
    while (QTime::currentTime() < betweenTime) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

int MainWindow::resolProc(const int &num1, const int &num2, const char op)
{
    int result;
    switch (op) {
        case '+':
            result = num1 + num2;
        break;

        case '-':
            result = num1 - num2;
        break;

        case '*':
            result = num1 * num2;
        break;

        case '/':
            result = num1 / num2;
        break;

        case '%':
            result = num1 % num2;
        break;
    }
    return result;
}
