#include "dragprojectile.h"
#include "odesolver.h"
#include <QDebug>
#include <QtMath>

DragProjectile::DragProjectile(QObject *parent) :
    SimpleProjectile(parent)
{
    this->mass = 0.0;
    this->area = 0.0;
    this->density = 0.0;
    this->Cd = 0.0;
}

void DragProjectile::initialize(double x0, double y0, double z0, double vx0, double vy0, double vz0, double time, double mass, double area, double density, double Cd)
{
    SimpleProjectile::initialize(x0, y0, z0, vx0, vy0, vz0, time);

    this->mass = mass;
    this->area = area;
    this->density = density;
    this->Cd = Cd;
}

void DragProjectile::updateLocationAndVelocity(double dt)
{
    ODESolver::rungeKutta4(this, dt);
}

// The getRightHandSide() method returns the right-hand sides of the six first-order
// projectile ODEs.
// q[0] = vx = dxdt
// q[1] = x
// q[2] = vy = dydt
// q[3] = y
// q[4] = vz = dzdt
// q[5] = z
double *DragProjectile::getRightHandSide(double s, double q[], double deltaQ[],
                                         double ds, double qScale)
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

    // compute the velocity magnitude. Add a small amount
    // (1.0e-8) to avoid div-by-zero errors if all velocity
    // components are zero
    double v = qSqrt(vx * vx + vy * vy + vz * vz) + 1.0e-8;


    // compute total drag force
//    qDebug() << "getDensityForAltitude(getZ()): " << getDensityForAltitude(getZ());
    qDebug() << "area: " << area;
    qDebug() << "v: " << v;
    qDebug() << "newQ[0]: " << newQ[0];
    qDebug() << "newQ[1]: " << newQ[1];
    qDebug() << "newQ[2]: " << newQ[2];
    qDebug() << "newQ[3]: " << newQ[3];
    qDebug() << "newQ[4]: " << newQ[4];
    qDebug() << "newQ[5]: " << newQ[5];
//    qDebug() << "ds: " << ds;
//    qDebug() << "x: " << ds * vx;
//    qDebug() << "z: " << ds * vz;
//    qDebug() << "vx: " << vx;
//    qDebug() << "vy: " << vy;
//    qDebug() << "vz: " << vz;
    double Fd = 0.5 * getDensityForAltitude(getZ()) * area * Cd * v * v;
    qDebug() << "Fd: " << Fd;

    // compute the right hand side of the six ODEs
    dQ[0] = -ds * Fd * vx/(mass * v);
    dQ[1] = ds * vx;
    dQ[2] = -ds * Fd * vy/(mass * v);
    dQ[3] = ds * vy;
    dQ[4] = ds * (G - Fd * vz/(mass * v));
    dQ[5] = ds * vz;

    return dQ;
}

void DragProjectile::setArea(double area)
{
    this->area = area;
}

void DragProjectile::setCd(double Cd)
{
    this->Cd = Cd;
}

double DragProjectile::getDensityForAltitude(double altitude)
{
    // used regression to find a formula for density for a given altitude
    // when density at sea-level is 1.225.
    // Range of input to regression: 0 to 3048m

    double res = 4.226958907191e-09 * (altitude * altitude) - 1.1786444511242e-04 * altitude + 1.2248168626609;
    //qDebug() << "density: " << res;
    return res;
}

