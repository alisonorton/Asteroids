#include "flyingObject.h"
#include "math.h"

// Put your FlyingObject method bodies here

using namespace std;

FlyingObject::FlyingObject()
{
    //I've decided to overload and use my non-default constructor
}

FlyingObject::FlyingObject(const Point point, const int speed, const float angle)
{
    setPoint(point);
    setAngle(angle);
    setAlive(true);
    setSpeed(speed);
    setRadius(radius);
}


void FlyingObject::kill()
{
    setAlive(false);
}

void FlyingObject::advance()
{
    //If the object is alive...
    if(isAlive())
    {
        //make sure it's able to move
        point.setX(point.getX() + velocity.getDx());
        point.setY(point.getY() + velocity.getDy());
        
        //Wrapping for the X coordinate
        if(point.getX() > 200 || point.getX() < -200)
        {
            point.setX(point.getX() * -1);
        }
        
        //Wrapping around for the Y coordinate
        if(point.getY() > 200 || point.getY() < -200)
        {
            point.setY(point.getY() * -1);
        }
    }
}










