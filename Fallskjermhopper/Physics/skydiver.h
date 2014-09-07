#ifndef SKYDIVER_H
#define SKYDIVER_H

class Skydiver
{
public:
    Skydiver();
    double getSecondsElapsed() const;
    void setSecondsElapsed(double value);

    double getStartAltitude() const;
    double getStartX() const;
    double getRadius() const;
    double getWeight() const;
    double getCurrAltitude() const;
    double getCurrX() const;

private:
    double startAltitude;
    double startX;
    double radius;
    double weight;
    double currAltitude;
    double currX;
    double secondsElapsed;
};

#endif // SKYDIVER_H
