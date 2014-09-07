#ifndef ODESOLVER_H
#define ODESOLVER_H

#include "ode.h"

class ODESolver
{
public:
    static void rungeKutta4(ODE *ode, double ds);
};

#endif // ODESOLVER_H
