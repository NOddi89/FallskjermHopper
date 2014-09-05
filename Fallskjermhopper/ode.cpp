#include "ode.h"

ODE::ODE(int numEqns, QObject *parent)
//    :QObject(parent)
{
    Q_UNUSED(parent)
    this->numEqns = numEqns;
    this->q = new double[numEqns];
}
int ODE::getNumEqns() const
{
    return numEqns;
}
double ODE::getS() const
{
    return s;
}

double ODE::getQ(int index)
{
    return q[index];
}

double *ODE::getAllQ()
{
    return q;
}

void ODE::setS(double value)
{
    s = value;
}

void ODE::setQ(double value, int index)
{
    q[index] = value;
}
