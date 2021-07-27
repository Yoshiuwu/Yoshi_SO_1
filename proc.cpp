#include "proc.h"

Proc::Proc()
{

}

QString Proc::getName() const
{
    return name;
}

void Proc::setName(const QString &value)
{
    name = value;
}

int Proc::getNum1() const
{
    return num1;
}

void Proc::setNum1(int value)
{
    num1 = value;
}

int Proc::getNum2() const
{
    return num2;
}

void Proc::setNum2(int value)
{
    num2 = value;
}

char Proc::getOperator() const
{
    return oper;
}

void Proc::setOperator(char value)
{
    oper = value;
}

int Proc::getId() const
{
    return id;
}

void Proc::setId(int value)
{
    id = value;
}

int Proc::getEstTime() const
{
    return estTime;
}

void Proc::setEstTime(int value)
{
    estTime = value;
}

int Proc::getResult() const
{
    return result;
}

void Proc::setResult(int value)
{
    result = value;
}
