// Put your velocity methods here

#include <iostream>
#include <cmath>
#include "velocity.h"
#include "math.h"

using namespace std;

Velocity::Velocity()
{
    setDx(0);
    setDy(0);
}

Velocity::Velocity(const float Dx, const float Dy)
{
    setDx(Dx);
    setDx(Dy);
}

void Velocity::calcVelocity(const int angle, const float speed)

{
    setDx(speed * (-sin(M_PI / 180 * angle)));
    setDy(speed * (cos(M_PI / 180 * angle)));
}
