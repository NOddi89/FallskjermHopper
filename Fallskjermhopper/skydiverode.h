#ifndef SKYDIVERODE_H
#define SKYDIVERODE_H

#include "Physics/windprojectile.h"

class SkydiverODE : public WindProjectile
{
    Q_OBJECT
public:
    SkydiverODE(QObject *parent = 0);

    Q_INVOKABLE virtual double *getRightHandSide(double s, double q[], double deltaQ[],
                             double ds, double qScale) override;

    double getSwingForce() const;
    void setSwingForce(double value);
    //Work around off qobject issues
    void emitAtGround();

signals:
    void zPosChanged(int);
    void vzChanged(int);
    void atGround();

private:
    double swingForce;

};

#endif // SKYDIVERODE_H
