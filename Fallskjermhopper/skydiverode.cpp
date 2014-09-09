#include "skydiverode.h"
#include <QtMath>
#include <QDebug>

SkydiverODE::SkydiverODE()
{
    swingVx = 0.0;
}

double *SkydiverODE::getRightHandSide(double s, double q[], double deltaQ[], double ds, double qScale)
{
    Q_UNUSED(s);
    double *dQ = new double[6];
    double *newQ = new double[6];

    // compute the intermediate values of the dependent variables
    for (int i = 0; i < 6; ++i) {
        newQ[i] = q[i] + qScale * deltaQ[i];
    }

    double vx = newQ[0];
    double vy = newQ[2];
    double vz = newQ[4];

    // Compute the apparent velocities by subtracting the wind velocity
    // components from the projectile velocity components. We also subtract a velocity
    // if the player try to compensate for wind.
    double vax = vx - getWindVx() - swingVx;
    double vay = vy - getWindVy();
    double vaz = vz;

    // compute the velocity magnitude. Add a small amount
    // (1.0e-8) to avoid div-by-zero errors if all velocity
    // components are zero
    double va = qSqrt(vax * vax + vay * vay + vaz * vaz) + 1.0e-8;


    // compute total drag force
    double Fd = 0.5 * getDensityForAltitude(getZ()) * getArea() * getCd() * va * va;

    // compute the right hand side of the six ODEs
    dQ[0] = -ds * Fd * vax/(getMass() * va);
    dQ[1] = ds * vx;
    dQ[2] = -ds * Fd * vay/(getMass() * va);
    dQ[3] = ds * vy;
    dQ[4] = ds * (G - Fd * vaz/(getMass() * va));
    dQ[5] = ds * vz;

    return dQ;
}
double SkydiverODE::getSwingVx() const
{
    return swingVx;
}

void SkydiverODE::setSwingVx(double value)
{
    swingVx = value;
}


