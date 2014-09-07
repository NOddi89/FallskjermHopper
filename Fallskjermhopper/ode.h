#ifndef ODE_H
#define ODE_H

#include <QObject>

class ODE : public QObject
{
    Q_OBJECT
public:
    ODE(int numEqns = 1, QObject* parent = 0);
    int getNumEqns() const;
    double getS() const;
    double getQ(int index);
    double *getAllQ();
    void setS(double value);
    Q_INVOKABLE void setQ(double value, int index);
    virtual double *getRightHandSide(double s, double q[], double deltaQ[],
                                     double ds, double qScale) = 0;
private:
    int numEqns;    // number of equations to solve
    double s;       // independent variable
    double *q;     // array of dependent variables
};

#endif // ODE_H
