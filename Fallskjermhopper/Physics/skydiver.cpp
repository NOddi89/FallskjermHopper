#include "skydiver.h"

Skydiver::Skydiver()
{
    startAltitude = 4000.0;
    startX = 0.0;
    radius = 0.5;
    weight = 75.0;
    currAltitude = 4000.0;
    currX = 0.0;
    secondsElapsed = 0.0;
}
double Skydiver::getSecondsElapsed() const
{
    return secondsElapsed;
}

void Skydiver::setSecondsElapsed(double value)
{
    secondsElapsed = value;
}
double Skydiver::getStartAltitude() const
{
    return startAltitude;
}

double Skydiver::getStartX() const
{
    return startX;
}

double Skydiver::getRadius() const
{
    return radius;
}

double Skydiver::getWeight() const
{
    return weight;
}

double Skydiver::getCurrAltitude() const
{
    return currAltitude;
}

double Skydiver::getCurrX() const
{
    return currX;
}







