#ifndef SKYDIVERODE_H
#define SKYDIVERODE_H

#include "Physics/windprojectile.h"

class SkydiverODE : public WindProjectile
{
public:
    SkydiverODE();

    Q_INVOKABLE virtual double *getRightHandSide(double s, double q[], double deltaQ[],
                             double ds, double qScale) override;


//    double getSwingVx() const;


    double getSwingForce() const;
    void setSwingForce(double value);

private:
    //    double swingVx;
    double swingForce;

    //public slots:
//    void setSwingVx(double value);
};

#endif // SKYDIVERODE_H
