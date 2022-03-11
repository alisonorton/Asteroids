#include "ship.h"
#include "flyingObject.h"
#include "uiDraw.h"
#include "velocity.h"
#include <cmath>
#include "math.h"

#include <iostream>

// Put your ship methods here

Ship::Ship(const Point &point) : FlyingObject(point, speed, angle)
{
    setPoint(random(-200, 200));
    setAlive(true);
    setIsThrust(false);
}



void Ship::draw()
{
    drawShip(point, angle, isThrust);
}


void Ship::applyThrust()
{
    float dy = 0.5 * (cos(3.14 / 180.0 * angle));
    float dx = 0.5 * (-sin(3.14 / 180.0 * angle));
    
    velocity.setDy(velocity.getDy() + dy);
    velocity.setDx(velocity.getDx() + dx);
    
    setIsThrust(true);
}

void Ship::moveLeft()
{
    angle += 6.0;
}

void Ship::moveRight()
{
    angle -= 6.0;
}







