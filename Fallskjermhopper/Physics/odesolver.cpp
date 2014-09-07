#include "odesolver.h"
#include "ode.h"
#include <QDebug>

void ODESolver::rungeKutta4(ODE *ode, double ds)
{
    int numEqns = ode->getNumEqns();
    double s = ode->getS();
    double *q = ode->getAllQ();
    double *dq1 = new double[numEqns];
    double *dq2 = new double[numEqns];
    double *dq3 = new double[numEqns];
    double *dq4 = new double[numEqns];

    dq1 = ode->getRightHandSide(s, q, q, ds, 0.0);
    qDebug() << "dq01: " << *dq1;
    dq2 = ode->getRightHandSide(s+0.5*ds, q, dq1, ds, 0.5);
    qDebug() << "dq02: " << *dq2;
    dq3 = ode->getRightHandSide(s+0.5*ds, q, dq2, ds, 0.5);
    qDebug() << "dq03: " << *dq3;
    dq4 = ode->getRightHandSide(s+ds, q, dq3, ds, 1.0);
    qDebug() << "dq04: " << *dq4;

    // Update the dependent and independent variable values
    // at the new dependent variable location and store the
    // values in the ODE object arrays.
    ode->setS(s+ds);
    for (int j = 0; j < numEqns; ++j) {
        q[j] = q[j] + (dq1[j] + 2.0 * dq2[j] + 2.0*dq3[j] + dq4[j]) / 6.0;
        ode->setQ(q[j], j);
    }
}
